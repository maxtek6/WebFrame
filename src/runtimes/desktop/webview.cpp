#include <desktop.hpp>

#ifdef __WXMSW__
static void OnWebViewNavigating(wxWebViewEvent &event);
#endif

namespace webframe
{
    namespace desktop
    {
        webview_handler::webview_handler(webframe::router *router) : wxWebViewHandler("https"), _router(router)
        {
            SetVirtualHost("webframe.ipc");
        }

        void webview_handler::StartRequest(const wxWebViewHandlerRequest& request, wxSharedPtr<wxWebViewHandlerResponse> response)
        {
            bool sent(false);
            webframe::desktop::request req(&request);
            webframe::desktop::response res(response.get(), sent);
            webframe::handler *handler = _router->find_route(req.get_path());
            handler->handle_request(&req, &res);
            if (!sent)
            {
                response->Finish("");
            }
        }

        wxSharedPtr<wxWebViewHandler> create_webview_handler(webframe::router *router)
        {
            return wxSharedPtr<wxWebViewHandler>(new webview_handler(router));
        }

        wxWebView *create_webview(wxFrame *frame, wxSharedPtr<wxWebViewHandler> webview_handler)
        {
            wxWebView *webview = wxWebView::New(frame, wxID_ANY, "about:blank", wxDefaultPosition, wxDefaultSize, wxWebViewBackendEdge, wxBORDER_NONE);
#ifdef __WXMSW__
            webview->Bind(wxEVT_WEBVIEW_NAVIGATING, OnWebViewNavigating);
#endif
            webview->RegisterHandler(webview_handler);
            return webview;
        }
    }
}

#ifdef __WXMSW__
void OnWebViewNavigating(wxWebViewEvent &event)
{
    const wxString url = event.GetURL();
    if (!url.StartsWith("https://webframe.ipc"))
    {
        event.Skip();
    }
}
#endif