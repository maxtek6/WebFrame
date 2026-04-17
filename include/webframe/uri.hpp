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

#ifndef WEBFRAME_URI_HPP
#define WEBFRAME_URI_HPP

#include <string>
#include <memory>
#include <unordered_map>

namespace webframe
{
    class uri
    {
    public:
        uri(const std::string& str);
        ~uri() = default;
        
        std::string get_scheme() const;
        std::string get_host() const;
        int get_port() const;
        std::string get_path() const;
        bool get_query(const std::string& key, std::string& value) const;
        std::string get_fragment() const;
    private:
        static bool find_keyword(const std::string& input_url, size_t& st, size_t& before, const std::string& delim, std::string& result);
        static bool split_query(const std::string& str, const std::string& delim, std::string& key, std::string& value);
        void parse(const std::string& str);
        std::string _scheme;
		std::string _userinfo;
		std::string _host;
		int _port;
		std::string _path;
        std::unordered_map<std::string, std::string> _query;
		std::string _fragment;
    };
}

#endif