#include <webframe.hpp>

class archive_handler : public webframe::handler
{
protected:
    void handle_get(const webframe::request* req, webframe::response* res) override
    {
        res->set_status(200);
        res->set_header("Content-Type", "text/plain");
        const std::string message = "Hello, World!";
        res->set_body(reinterpret_cast<const uint8_t *>(message.data()), message.size());
    }
};

class example_application : public webframe::application
{
public:
    void configure_router(webframe::router *ctrl) override
    {
        ctrl->add_route("/archive", new archive_handler());
    }
};

WEBFRAME_MAIN(example_application)