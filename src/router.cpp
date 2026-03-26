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

#include <webframe.hpp>

class global_default_handler : public webframe::handler
{
protected:
    void handle_get(const webframe::request* req, webframe::response* res) override
    {
        throw webframe::exception::not_found;
    }

    void handle_post(const webframe::request* req, webframe::response* res) override
    {
        throw webframe::exception::not_found;
    }

    void handle_put(const webframe::request* req, webframe::response* res) override
    {
        throw webframe::exception::not_found;
    }

    void handle_delete(const webframe::request* req, webframe::response* res) override
    {
        throw webframe::exception::not_found;
    }
};

static global_default_handler g_default_handler;

namespace webframe
{
    void router::add_route(const std::string& path, handler* h)
    {
        _handlers[path] = h;
    }

    void router::set_default(handler* h)
    {
        _default_handler = h;
    }

    handler* router::find_route(const std::string& path)
    {
        auto it = _handlers.find(path);
        if (it != _handlers.end()) {
            return it->second;
        }
        return get_default();
    }

    handler* router::get_default()
    {
        return _default_handler ? _default_handler : &g_default_handler;      
    }
}