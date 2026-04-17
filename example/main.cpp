#include <webframe.hpp>

#include <archive.hpp>

#include <yyjson.h>

#include <thread>

static std::string get_archive_path()
{
    std::string result(ARCHIVE_DIRECTORY);
#ifdef _WIN32
    std::replace(result.begin(), result.end(), '/', '\\');
    result += "\\";
#else
    result += "/";
#endif
    result += "hyperpage.db";
    return result;
}

class archive_handler : public webframe::handler
{
public:
    void open(const std::string& archive_path)
    {
        _archive.reset(new hyperpage::reader(archive_path));
    }
protected:
    void handle_get(const webframe::request* req, webframe::response* res) override
    {
        std::string page_path = req->get_path();
        if(page_path.empty() || page_path == "/") {
            page_path = "/index.html";
        }
        auto page = _archive->load(page_path);
        if (page) {
            res->set_status(200);
            res->set_header("Content-Type", page->get_mime_type());
            res->set_body(page->get_content(), page->get_length());
        }
        else {
            res->set_status(404);
            res->set_header("Content-Type", "text/plain");
            const std::string not_found_msg = "Not Found";
            res->set_body(reinterpret_cast<const uint8_t*>(not_found_msg.data()), not_found_msg.size());
        }
    }
private:
    std::unique_ptr<hyperpage::reader> _archive;
};

class greeting_ipc_handler : public webframe::handler
{
protected:
    void handle_post(const webframe::request* req, webframe::response* res) override
    {
        std::unique_ptr<yyjson_doc, decltype(&yyjson_doc_free)> request_body(nullptr, &yyjson_doc_free);
        std::unique_ptr<yyjson_mut_doc, decltype(&yyjson_mut_doc_free)> response_body(nullptr, &yyjson_mut_doc_free);
        request_body.reset(yyjson_read(reinterpret_cast<const char*>(req->get_body().first), req->get_body().second, 0));
        if (!request_body || !yyjson_is_obj(request_body->root)) {
            throw webframe::exception::bad_request;
        }
        yyjson_val* name_val = yyjson_obj_get(request_body->root, "name");
        if (!name_val || !yyjson_is_str(name_val)) {
            throw webframe::exception::bad_request;
        }
        const char* name = yyjson_get_str(name_val);

        response_body.reset(yyjson_mut_doc_new(nullptr));
        yyjson_mut_val* root = yyjson_mut_obj(response_body.get());
        const std::string greeting = "Hello, " + std::string(name) + "!";
        yyjson_mut_obj_add_strcpy(response_body.get(), root, "greeting", greeting.c_str());
        yyjson_mut_doc_set_root(response_body.get(), root);

        size_t response_len;
        const char *response_data = yyjson_mut_write(response_body.get(), 0, &response_len);
        res->set_status(200);
        res->set_header("Content-Type", "application/json");
        res->set_body(reinterpret_cast<const uint8_t*>(response_data), response_len);
        free(const_cast<char *>(response_data));
    }
};

class window_listener : public webframe::window_listener
{
public:
    void on_close(webframe::window *source) override
    {
        source->set_title("Goodbye!");
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
};

class example_application : public webframe::application
{
public:
    void configure_router(webframe::router *router) override
    {
        _archive_handler.open(get_archive_path());
        router->set_default(&_archive_handler);    
        router->add_route("/greetingIPC", &_greeting_ipc_handler);
    }

    void launch_desktop(webframe::desktop_context *context)
    {
        webframe::window *win = context->create_window(nullptr, 800, 600);
        win->set_title("WebFrame Example");
        win->load_path("index.html");
        win->add_listener(&_window_listener);
    }
private:
    window_listener _window_listener;
    archive_handler _archive_handler;
    greeting_ipc_handler _greeting_ipc_handler;
};


WEBFRAME_MAIN(example_application)
