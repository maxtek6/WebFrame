#include <desktop.hpp>

namespace webframe::desktop
{
    window::window(wxFrame *frame, wxSharedPtr<wxWebViewHandler> webview_handler) : _frame(frame)
    {
        _webview = webframe::desktop::create_webview(frame, webview_handler);
        _webview_data.webview_handler = webview_handler;
        _webview->Bind(
            wxEVT_WEBVIEW_CREATED,
            [this](wxWebViewEvent &event)
            {
                wxWebView *webview = reinterpret_cast<wxWebView *>(event.GetEventObject());
                webview->RegisterHandler(_webview_data.webview_handler);
                if (!_webview_data.initial_url.empty())
                {
                    wxString wx_url = wxString(_webview_data.initial_url.c_str());
                    webview->LoadURL(wx_url);
                }
                _webview_data.created = true;
            });
        _frame->Show();
    }

    void window::load_path(const std::string &path)
    {
        const std::string url = "https://webframe.ipc/" + path;
        load_url(url);
    }

    void window::load_url(const std::string &url)
    {
        if (_webview_data.created)
        {
            wxString wx_url = wxString(url.c_str());
            _webview->LoadURL(wx_url);
        }
        else
        {
            _webview_data.initial_url = url;
        }
    }

    std::string window::get_id() const
    {
        return std::to_string(_frame->GetId());
    }

    wxFrame *window::get_frame() const
    {
        return _frame.get();
    }

    void window::set_title(const std::string &title)
    {
        wxString wx_title = wxString(title.c_str());
        _frame->SetTitle(wx_title);
    }
}
