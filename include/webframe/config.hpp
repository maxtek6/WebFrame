/* WebFrame
 *
 * Copyright (C) 2026 Maxtek Consulting
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef WEBFRAME_CONFIG_HPP
#define WEBFRAME_CONFIG_HPP

#include <list>
#include <optional>
#include <string>

/**
 * @file webframe/config.hpp
 * @brief WebFrame configuration API
 * @author John R Patek Sr <johnpatek2@gmail.com>
 */
namespace webframe
{
    class desktop_config
    {
    public:
        desktop_config() = default;
        ~desktop_config() = default;

        void set_dark_mode(bool dark_mode);
        void set_default_window_size(int width, int height);

        void set_icon(const std::string& path);
        void set_icons(const std::initializer_list<std::string>& paths);

        bool get_dark_mode(bool &dark_mode) const;
        std::pair<int, int> get_default_window_size() const;

    private:
        std::optional<bool> _force_dark_mode;
        std::pair<int, int> _default_window_size = {800, 600};
        std::list<std::string> _icon_paths;
    };

    class server_config
    {
    public:
        server_config() = default;
        ~server_config() = default;

        void set_host(const std::string &host);
        void set_port(uint16_t port);

        std::string get_host() const;
        uint16_t get_port() const;

    private:
        std::string _host;
        uint16_t _port;
    };
}

#endif