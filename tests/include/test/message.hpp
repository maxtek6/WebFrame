#ifndef WEBFRAME_TEST_MESSAGE_HPP
#define WEBFRAME_TEST_MESSAGE_HPP

#include <webframe.hpp>

#include <map>
#include <vector>

namespace webframe::test
{
    struct message_data
    {
        std::map<std::string, std::string> headers;
        std::vector<uint8_t> body;
    };

    struct request_data : public message_data
    {
        webframe::method method;
        std::string path;
    };

    struct response_data : public message_data
    {
        int status_code;
    };

    class request : public webframe::request, public request_data
    {
    public:
        webframe::method get_method() const override;
        std::string get_path() const override;
        bool get_header(const std::string &key, std::string &value) const override;
        std::pair<const uint8_t *, size_t> get_body() const override;
        void read_body(const std::function<void(const uint8_t *, size_t)> &callback) const override;
    };

    class response : public webframe::response, public response_data
    {
    public:
        void set_status(int status) override;
        void set_header(const std::string &key, const std::string &value) override;
        void set_body(const uint8_t *data, size_t size) override;
        void write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback) override;
    };
}
#endif