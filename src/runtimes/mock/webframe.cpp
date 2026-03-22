#include <webframe.hpp>

namespace webframe
{
    exception exception::bad_request(400, "Bad Request");
    exception exception::unauthorized(401, "Unauthorized");
    exception exception::forbidden(403, "Forbidden");
    exception exception::not_found(404, "Not Found");
    exception exception::method_not_allowed(405, "Method Not Allowed");
    exception exception::internal_server_error(500, "Internal Server Error");

    void handler::handle_request(const request* req, response* res)
    {
        try
        {
            switch(req->get_method())
            {
                case method::GET:
                    handle_get(req, res);
                    break;
                case method::POST:
                    handle_post(req, res);
                    break;
                case method::PUT:
                    handle_put(req, res);
                    break;
                case method::DELETE:
                    handle_delete(req, res);
                    break;
                default:
                    throw exception::method_not_allowed;
            }
        }
        catch(const exception& e)
        {
            res->set_status(e.get_status_code());
            res->set_header("Content-Type", e.get_content_type());
            res->set_body(reinterpret_cast<const uint8_t*>(e.get_message().data()), e.get_message().size());
        }
    }
}