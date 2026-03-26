#ifndef WEBFRAME_DESKTOP_WEBVIEW_HPP
#define WEBFRAME_DESKTOP_WEBVIEW_HPP

#include "wxwidgets.hpp"

namespace webframe::desktop
{
    class webview_handler : public wxWebViewHandler
    {
    public:
        webview_handler(webframe::router *router);
        ~webview_handler() = default;
        void StartRequest(const wxWebViewHandlerRequest &request, wxSharedPtr<wxWebViewHandlerResponse> response) override;

    private:
        webframe::router *_router;
    };

    wxSharedPtr<wxWebViewHandler> create_webview_handler(webframe::router *router);
    wxWebView *create_webview(wxFrame *frame, wxSharedPtr<wxWebViewHandler> webview_handler);
}

#endif