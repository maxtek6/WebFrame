#ifndef WEBFRAME_EXCEPTION_HPP
#define WEBFRAME_EXCEPTION_HPP

#include <string>

namespace webframe
{
    class exception
    {
    public:
        exception(int status_code, const std::string &message, const std::string &content_type = "text/plain");
        int get_status_code() const;
        std::string get_message() const;
        std::string get_content_type() const;
        
        static exception bad_request;
        static exception unauthorized;
        static exception forbidden;
        static exception not_found;
        static exception method_not_allowed;
        static exception internal_server_error;
    private:
        int _status_code;
        std::string _message;
        std::string _content_type;
    };
}

#endif