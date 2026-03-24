#include <desktop.hpp>

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
    }
}