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

#ifndef WEBFRAME_EXCEPTION_HPP
#define WEBFRAME_EXCEPTION_HPP

#include <string>

namespace webframe
{
    class exception
    {
    public:
        exception(int status_code, const std::string &message, const std::string &content_type = "text/plain");
        int get_status_code() const;
        std::string get_message() const;
        std::string get_content_type() const;
        
        static exception bad_request;
        static exception unauthorized;
        static exception forbidden;
        static exception not_found;
        static exception method_not_allowed;
        static exception internal_server_error;
    private:
        int _status_code;
        std::string _message;
        std::string _content_type;
    };
}

#endif