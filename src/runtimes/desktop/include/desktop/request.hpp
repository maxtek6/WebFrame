#ifndef WEBFRAME_DESKTOP_REQUEST_HPP
#define WEBFRAME_DESKTOP_REQUEST_HPP

#include "wxwidgets.hpp"

namespace webframe::desktop
{
    class request : public webframe::request
    {
    public:
        request(const wxWebViewHandlerRequest *request);
        ~request() = default;
        
        webframe::method get_method() const override;

        std::string get_uri() const override;

        std::string get_path() const override;
        bool get_header(const std::string &key, std::string &value) const override;
        std::pair<const uint8_t *, size_t> get_body() const override;
        void read_body(const std::function<void(const uint8_t *, size_t)> &callback) const override;

    private:
        const wxWebViewHandlerRequest *_request;
        wxString _body;
    };
}

#endif