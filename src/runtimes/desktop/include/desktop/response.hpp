#ifndef WEBFRAME_DESKTOP_RESPONSE_HPP
#define WEBFRAME_DESKTOP_RESPONSE_HPP

#include "wxwidgets.hpp"

namespace webframe::desktop
{
    class response : public webframe::response
    {
    public:
        response(wxWebViewHandlerResponse *response, bool &sent);
        ~response() = default;
        void set_status(int status) override;
        void set_header(const std::string &key, const std::string &value) override;
        void set_body(const uint8_t *data, size_t size) override;
        void write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback) override;

    private:
        wxWebViewHandlerResponse *_response;
        bool &_sent;
    };
}

#endif