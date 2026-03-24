#include <desktop.hpp>

class wfApp : public wxApp
{
public:
    void Init(webframe::application *application, webframe::router *router)
    {
        _application = application;
        _router = router;
    }
    bool OnInit() override
    {
        _application->configure_desktop();
        _application->configure_router(_router);
        _frame = std::make_unique<wxFrame>(nullptr, wxID_ANY, "WebFrame");
        _webview = wxWebView::New(_frame.get(), wxID_ANY, "about:blank", wxDefaultPosition, wxDefaultSize, wxWebViewBackendEdge);
#ifdef __WXMSW__
        _webview->Bind(wxEVT_WEBVIEW_NAVIGATING, [](wxWebViewEvent &event)
                       {
        const wxString url = event.GetURL();
        if (!url.StartsWith("https://webframe.ipc"))
        {
            event.Skip();
        } });
#endif
        _webview->Bind(wxEVT_WEBVIEW_CREATED, [this](wxWebViewEvent &event)
        {
            wxWebView *webview = reinterpret_cast<wxWebView *>(event.GetEventObject());
            webview->RegisterHandler(wxSharedPtr<wxWebViewHandler>(new webframe::desktop::webview_handler(_router)));
            webview->LoadURL("https://webframe.ipc/index.html");
        });
        _frame->Show();
        return true;
    }

private:
    std::unique_ptr<wxFrame> _frame;
    wxWebView *_webview;
    webframe::application *_application;
    webframe::router *_router;
};

namespace webframe
{
    namespace desktop
    {
        int runtime::launch_wx_app(wfApp *app, webframe::application *a, webframe::router *r)
        {
            int result(0);
            app->Init(a, r);
            if (app->CallOnInit())
            {
                a->on_dispatch();
                result = app->OnRun();
            }
            else
            {
                result = 1;
            }
            wxEntryCleanup();
            return result;
        }
    }

    runtime *webframe_init()
    {
        return new desktop::runtime();
    }
}

// keep platform specific garbage down here
wxIMPLEMENT_APP_NO_MAIN(wfApp);
#ifdef WEBFRAME_WIN32_APP
#include <wx/msw/init.h>
int webframe::desktop::runtime::dispatch(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, webframe::application *a, webframe::router *r)
{
    wxEntryStart(hInstance);
    return launch_wx_app(reinterpret_cast<wfApp *>(wxTheApp), a, r);
}
#else
int webframe::desktop::runtime::dispatch(int argc, const char **argv, webframe::application *a, webframe::router *r)
{
    wxEntryStart(argc, const_cast<char **>(argv));
    return launch_wx_app(reinterpret_cast<wfApp *>(wxTheApp), a, r);
}
#endif