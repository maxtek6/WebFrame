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

#ifndef WEBFRAME_ROUTER_HPP
#define WEBFRAME_ROUTER_HPP

#include <string>
#include <unordered_map>

namespace webframe
{
    class request;
    class response;
    class handler;

    class router
    {
    public:
        router() = default;
        ~router() = default;
        void add_route(const std::string& path, handler* h);
        handler *find_route(const std::string& path);
        void set_default(handler* h);
        handler* get_default();
    private:        
        std::unordered_map<std::string, handler*> _handlers;
        handler* _default_handler = nullptr;
    };
}
#endif