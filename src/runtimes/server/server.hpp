#ifndef WEBFRAME_SERVER_HPP
#define WEBFRAME_SERVER_HPP

#include <webframe.hpp>

#include <event2/buffer.h>
#include <event2/event.h>
#include <event2/http.h>

namespace webframe::server
{
    class request : public webframe::request
    {
    public:
        request(struct evhttp_request *req);
        ~request() = default;
        webframe::method get_method() const override;
        std::string get_path() const override;
        bool get_header(const std::string &key, std::string &value) const override;
        std::pair<const uint8_t *, size_t> get_body() const override;
        void read_body(const std::function<void(const uint8_t *, size_t)> &callback) const override;
    private:
        struct evhttp_request *_req;  
        evkeyvalq *_headers;
        std::vector<uint8_t> _body;
    };

    class response : public webframe::response
    {
    public:
        response(struct evhttp_request *req, bool &sent_response, int &status);
        ~response() = default;
        void set_status(int status) override;
        void set_header(const std::string &key, const std::string &value) override;
        void set_body(const uint8_t *data, size_t size) override;
        void write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback) override;
    private:
        struct evhttp_request *_req;
        evkeyvalq *_headers;

        bool &_sent_response;
        int &_status;
    };

    class runtime : public webframe::runtime
    {
    public:
        int dispatch(int argc, const char **argv, webframe::application *a, webframe::router *r) override;
    private:
        void listen(const char *address, int port);
        void serve();
        void stop();
        
        std::unique_ptr<struct event_base, decltype(&event_base_free)> _event_base{nullptr, &event_base_free};
        std::unique_ptr<struct evhttp, decltype(&evhttp_free)> _http{nullptr, &evhttp_free};
    };
}

#endif