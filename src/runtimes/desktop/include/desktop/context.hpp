#ifndef WEBFRAME_DESKTOP_CONTEXT_HPP
#define WEBFRAME_DESKTOP_CONTEXT_HPP

#include "wxwidgets.hpp"

namespace webframe::desktop
{
    class context : public webframe::desktop_context
    {
    public:
        context(webframe::desktop_config *config, webframe::router *router);
        ~context() = default;
        webframe::window *create_window(webframe::window *parent, int width, int height) override;
        webframe::window *find_window(const std::string &id) override;
        void destroy_window(webframe::window *handle) override;
        std::string get_exe_path() const override;

    private:
        int _default_width;
        int _default_height;
        std::unordered_map<std::string, std::unique_ptr<window>> _windows;
        wxSharedPtr<wxWebViewHandler> _webview_handler;
    };
}
#endif