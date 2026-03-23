#include <webframe.hpp>

#include <archive.hpp>

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
    archive_handler() = default;
    ~archive_handler() = default;
    void open(const std::string& archive_path)
    {
        _archive.reset(new hyperpage::reader(archive_path));
    }
protected:
    void handle_get(const webframe::request* req, webframe::response* res) override
    {
        std::string page_path = req->get_path();
        auto page = _archive->load(page_path);
        if (page) {
            res->set_status(200);
            res->set_header("Content-Type", page->get_mime_type());
            res->set_body(page->get_content(), page->get_length());
        }
        else {
            res->set_status(404);
            res->set_header("Content-Type", "text/plain");
            const std::string not_found_msg = "404 Not Found";
            res->set_body(reinterpret_cast<const uint8_t*>(not_found_msg.data()), not_found_msg.size());
        }
    }
private:
    std::unique_ptr<hyperpage::reader> _archive;
};


class example_application : public webframe::application
{
public:
    void configure_router(webframe::router *router) override
    {
        _archive_handler.open(get_archive_path());
        router->set_default(&_archive_handler);    
    }
private:
    archive_handler _archive_handler;
};


WEBFRAME_MAIN(example_application)
