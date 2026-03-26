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

#ifndef WEBFRAME_CONTEXT_HPP
#define WEBFRAME_CONTEXT_HPP

/**
 * @file webframe/context.hpp
 * @brief WebFrame context API
 * @author John R Patek Sr <johnpatek2@gmail.com>
 */

#include <csignal>
#include <string>

namespace webframe
{
    class window
    {
    public:
        virtual void load_url(const std::string& url) = 0;
        virtual void load_path(const std::string& path) = 0;
        virtual std::string get_id() const = 0;
    };

    class desktop_context
    {
    public:
        desktop_context() = default;
        ~desktop_context() = default;
        virtual window* create_window(window *parent, int width = -1, int height = -1);
        virtual window* find_window(const std::string& id);
        virtual void destroy_window(window* handle);
    };
    
    class server_context
    {
    public:
        server_context() = default;
        ~server_context() = default;
        virtual void sighandle(int signum);
    };
}

#endif