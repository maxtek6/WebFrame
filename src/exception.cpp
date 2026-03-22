#include <webframe.hpp>

namespace webframe
{
    exception::exception(int status_code, const std::string &message, const std::string &content_type)
        : _status_code(status_code), _message(message), _content_type(content_type) {}

    int exception::get_status_code() const
    {
        return _status_code;
    }

    std::string exception::get_message() const
    {
        return _message;
    }

    std::string exception::get_content_type() const
    {
        return _content_type;
    }

    exception exception::bad_request(400, "Bad Request");
    exception exception::unauthorized(401, "Unauthorized");
    exception exception::forbidden(403, "Forbidden");
    exception exception::not_found(404, "Not Found");
    exception exception::method_not_allowed(405, "Method Not Allowed");
    exception exception::internal_server_error(500, "Internal Server Error");
}