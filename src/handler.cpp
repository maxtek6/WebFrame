#include <webframe.hpp>

namespace webframe
{
    void handler::handle_request(const request *req, response *res)
    {
        try
        {
            switch (req->get_method())
            {
            case method::http_get:
                handle_get(req, res);
                break;
            case method::http_post:
                handle_post(req, res);
                break;
            case method::http_put:
                handle_put(req, res);
                break;
            case method::http_delete:
                handle_delete(req, res);
                break;
            default:
                throw exception::bad_request;
            }
        }
        catch (const exception &e)
        {
            res->set_status(e.get_status_code());
            res->set_header("Content-Type", e.get_content_type());
            const std::string &message = e.get_message();
            res->set_body(reinterpret_cast<const uint8_t *>(message.data()), message.size());
        }
    }

    void handler::handle_get(const request *req, response *res)
    {
        throw exception::method_not_allowed;
    }

    void handler::handle_post(const request *req, response *res)
    {
        throw exception::method_not_allowed;
    }

    void handler::handle_put(const request *req, response *res)
    {
        throw exception::method_not_allowed;
    }

    void handler::handle_delete(const request *req, response *res)
    {
        throw exception::method_not_allowed;
    }
}