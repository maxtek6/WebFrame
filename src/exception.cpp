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
    exception::exception(int status_code, const std::string &message, const std::string &content_type)
        : _status_code(status_code), _message(message), _content_type(content_type) {}

    int exception::get_status_code() const
    {
        return _status_code;
    }

    std::string exception::get_message() const
    {
        return _message;
    }

    std::string exception::get_content_type() const
    {
        return _content_type;
    }

    exception exception::bad_request(400, "Bad Request");
    exception exception::unauthorized(401, "Unauthorized");
    exception exception::forbidden(403, "Forbidden");
    exception exception::not_found(404, "Not Found");
    exception exception::method_not_allowed(405, "Method Not Allowed");
    exception exception::internal_server_error(500, "Internal Server Error");
}