#include <webframe.hpp>

#include <hyperpage.hpp>

class archive_handler : public webframe::handler
{
public:
    archive_handler(const std::string& archive_path) 
    {
        _archive = std::make_unique<hyperpage::reader>(archive_path);
    }
protected:
    void handle_get(const webframe::request* req, webframe::response* res) override
    {
        std::string path = req->get_path();
        auto page = _archive->load(path);
        if (page) {
            res->set_status(200);
            res->set_header("Content-Type", page->get_mime_type());
            res->set_body(page->get_content(), page->get_length());
        } 
        else 
        {
            throw webframe::exception::not_found;
        }
    }
private:
    std::unique_ptr<hyperpage::reader> _archive;
};

class greeting_handler : public webframe::handler
{
protected:
    void handle_post(const webframe::request* req, webframe::response* res) override
    {
        
    }
};

class example_application : public webframe::application
{
public:
    void configure_router(webframe::router* router) override
    {
        _archive_handler = std::make_unique<archive_handler>("path/to/archive");
        router->set_default(_archive_handler.get());
    }
private:
    std::unique_ptr<archive_handler> _archive_handler;
};

WEBFRAME_MAIN(example_application)