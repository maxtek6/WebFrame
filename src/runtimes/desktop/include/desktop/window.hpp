#ifndef WEBFRAME_DESKTOP_WINDOW_HPP
#define WEBFRAME_DESKTOP_WINDOW_HPP

#include "wxwidgets.hpp"

namespace webframe::desktop
{
    class window : public webframe::window
    {
    public:
        window(wxFrame *frame, wxSharedPtr<wxWebViewHandler> webview_handler);
        ~window() = default;
        void load_path(const std::string &path) override;
        void load_url(const std::string &url) override;
        std::string get_id() const override;

        wxFrame *get_frame() const;

    private:
        std::unique_ptr<wxFrame> _frame;
        wxWebView *_webview;
        struct webview_data
        {
            std::atomic<bool> created{false};
            std::string initial_url;
            wxSharedPtr<wxWebViewHandler> webview_handler;
        } _webview_data;
    };
}

#endif