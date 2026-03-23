#include <server.hpp>

namespace webframe::server
{
    response::response(struct evhttp_request *req, bool &sent_response, int &status) : _req(req), _sent_response(sent_response), _status(status)
    {
        _headers = evhttp_request_get_output_headers(_req);
    }

    void response::set_status(int status)
    {
        _status = status;
    }

    void response::set_header(const std::string &key, const std::string &value)
    {
        evhttp_add_header(_headers, key.c_str(), value.c_str());
    }

    void response::set_body(const uint8_t *data, size_t size)
    {
        std::unique_ptr<struct evbuffer, decltype(&evbuffer_free)> output_buffer(evbuffer_new(), &evbuffer_free);
        evbuffer_add(output_buffer.get(), data, size);
        evhttp_send_reply(_req, _status, nullptr, output_buffer.get());
        _sent_response = true;
    }

    void response::write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback)
    {
        bool has_more = true;
        evhttp_send_reply_start(_req, _status, nullptr);
        while (has_more)
        {
            std::unique_ptr<struct evbuffer, decltype(&evbuffer_free)> output_buffer(evbuffer_new(), &evbuffer_free);
            std::pair<const uint8_t *, size_t> chunk;
            has_more = callback(chunk);
            if(chunk.first && chunk.second > 0)
            {
                evbuffer_add(output_buffer.get(), chunk.first, chunk.second);
            }
            evhttp_send_reply_chunk(_req, output_buffer.get());
        }
        evhttp_send_reply_end(_req);
        _sent_response = true;
    }
}