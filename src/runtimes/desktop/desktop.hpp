#ifndef WEBFRAME_DESKTOP_HPP
#define WEBFRAME_DESKTOP_HPP

#include <webframe.hpp>

#include <wx/wx.h>
#include <wx/webview.h>
#include <wx/uri.h>

class wfApp;

namespace webframe::desktop
{
    class request : public webframe::request
    {
    public:
        request(const wxWebViewHandlerRequest *request);
        ~request() = default;
        webframe::method get_method() const override;
        std::string get_path() const override;
        bool get_header(const std::string &key, std::string &value) const override;
        std::pair<const uint8_t *, size_t> get_body() const override;
        void read_body(const std::function<void(const uint8_t *, size_t)> &callback) const override;
    private:
        const wxWebViewHandlerRequest *_request;
        wxString _body;
    };

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

    class webview_handler : public wxWebViewHandler
    {
    public:
        webview_handler(webframe::router *router);
        ~webview_handler() = default;
        void StartRequest(const wxWebViewHandlerRequest& request, wxSharedPtr<wxWebViewHandlerResponse> response) override;
    private:
        webframe::router *_router;
    };

    class runtime : public webframe::runtime
    {
    public:
#ifdef WEBFRAME_WIN32_APP
        int dispatch(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, webframe::application *a, webframe::router *r) override;
#else
        int dispatch(int argc, const char **argv, webframe::application *a, webframe::router *r) override;
#endif
    private:
        int launch_wx_app(wfApp *app, webframe::application *a, webframe::router *r);
    };
}

#endif