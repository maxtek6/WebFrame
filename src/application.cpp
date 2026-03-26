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

namespace webframe
{
    void application::configure_desktop(desktop_config *config)
    {

    }

    void application::configure_server(server_config *config, int argc, const char **argv)
    {

    }

    void application::configure_router(router *ctrl)
    {

    }

    void application::launch_desktop(desktop_context *context)
    {
        window *handle = context->create_window(nullptr);
        handle->load_path("index.html");
    }

    void application::launch_server(server_context *context)
    {
        context->sighandle(SIGINT);
    }
}