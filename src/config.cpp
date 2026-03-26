#include <webframe.hpp>

namespace webframe
{
    void desktop_config::set_dark_mode(bool dark_mode)
    {
        _force_dark_mode = dark_mode;
    }

    bool desktop_config::get_dark_mode(bool &dark_mode) const
    {
        const bool result(_force_dark_mode.has_value());
        if (result)
        {
            dark_mode = _force_dark_mode.value();
        }
        return result;
    }

    std::pair<int, int> desktop_config::get_default_window_size() const
    {
        return _default_window_size;
    }

    void desktop_config::set_default_window_size(int width, int height)
    {
        _default_window_size = {width, height};
    }

    void server_config::set_host(const std::string &host)
    {
        _host = host;
    }

    std::string server_config::get_host() const
    {
        return _host;
    }

    void server_config::set_port(uint16_t port)
    {
        _port = port;
    }

    uint16_t server_config::get_port() const
    {
        return _port;
    }
}