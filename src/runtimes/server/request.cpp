#include <server.hpp>

namespace webframe::server
{
    request::request(struct evhttp_request *req) : _req(req)
    {
        _headers = evhttp_request_get_input_headers(_req);
        struct evbuffer *input_buffer = evhttp_request_get_input_buffer(_req);
        size_t body_size = evbuffer_get_length(input_buffer);
        _body.resize(body_size);
        evbuffer_copyout(input_buffer, _body.data(), body_size);
    }

    webframe::method request::get_method() const
    {
        webframe::method method;
        switch(evhttp_request_get_command(_req))
        {
        case EVHTTP_REQ_GET:
            method = webframe::method::http_get;
            break;
        case EVHTTP_REQ_POST:
            method = webframe::method::http_post;
            break;
        case EVHTTP_REQ_PUT:
            method = webframe::method::http_put;
            break;
        case EVHTTP_REQ_DELETE:
            method = webframe::method::http_delete;
            break;
        default:
            method = static_cast<webframe::method>(-1);
            break;
        }
        return method;

    }

    std::string request::get_uri() const
    {
        const char *uri = evhttp_request_get_uri(_req);
        return std::string(uri);
    }

    std::string request::get_path() const
    {
        const evhttp_uri *uri = evhttp_request_get_evhttp_uri(_req);
        const char *path = evhttp_uri_get_path(uri);
        return path ? path : "";
    }

    bool request::get_header(const std::string &key, std::string &value) const
    {
        const char *header_value = evhttp_find_header(_headers, key.c_str());
        bool result(false);
        if (header_value)
        {
            value = header_value;
            result = true;
        }
        return result;
    }

    std::pair<const uint8_t *, size_t> request::get_body() const
    {
        return { _body.data(), _body.size() };
    }

    void request::read_body(const std::function<void(const uint8_t *, size_t)> &callback) const
    {
        callback(_body.data(), _body.size());
    }

}