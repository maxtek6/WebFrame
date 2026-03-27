#include <desktop.hpp>

namespace webframe::desktop
{
    context::context(webframe::desktop_config *config, webframe::router *router) : _webview_handler(wxSharedPtr<wxWebViewHandler>(new webframe::desktop::webview_handler(router)))
    {
        auto const &[default_width, default_height] = config->get_default_window_size();
        _default_width = default_width;
        _default_height = default_height;
    }

    webframe::window *context::create_window(webframe::window *parent, int width, int height)
    {
        // TODO: do something with window ID to avoid the reinterpret_cast
        webframe::desktop::window *parent_window = reinterpret_cast<webframe::desktop::window *>(parent);
        wxFrame *frame = new wxFrame(
            parent_window ? parent_window->get_frame() : nullptr,
            wxID_ANY,
            "WebFrame",
            wxDefaultPosition,
            wxSize(width > 0 ? width : _default_width, height > 0 ? height : _default_height));
        return new webframe::desktop::window(frame, _webview_handler);
    }

    webframe::window *context::find_window(const std::string &id)
    {
        webframe::window *result(nullptr);
        auto it = _windows.find(id);
        if (it != _windows.end())
        {
            result = it->second.get();
        }
        return result;
    }

    void context::destroy_window(webframe::window *handle)
    {
        _windows.erase(handle->get_id());
    }

    std::string context::get_exe_path() const
    {
        return wxStandardPaths::Get().GetExecutablePath().ToStdString();
    }
}