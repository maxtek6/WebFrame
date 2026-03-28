#include <webframe.hpp>

namespace webframe
{
    webframe::window* desktop_context::create_window(window *parent, int width, int height)
    {
        (void)parent;
        (void)width;
        (void)height;
        return nullptr;
    }

    webframe::window* desktop_context::find_window(const std::string& id)
    {
        (void)id;
        return nullptr;
    }

    void desktop_context::destroy_window(window* handle)
    {
        (void)handle;
    }

    void server_context::sighandle(int signum)
    {
        (void)signum;
    }

    std::string desktop_context::get_exe_path() const
    {
        return {};
    }
}