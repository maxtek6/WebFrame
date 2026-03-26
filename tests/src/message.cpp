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

#include <test.hpp>

namespace webframe::test
{
    webframe::method request::get_method() const
    {
        return method;
    }

    std::string request::get_path() const
    {
        return path;
    }

    bool request::get_header(const std::string &key, std::string &value) const
    {
        bool result(false);
        auto it = headers.find(key);
        if (it != headers.end())
        {
            result = true;
            value = it->second;
        }
        return result;
    }

    std::pair<const uint8_t *, size_t> request::get_body() const
    {
        return { body.data(), body.size() };
    }

    void request::read_body(const std::function<void(const uint8_t *, size_t)> &callback) const
    {
        callback(body.data(), body.size());
    }

    void response::set_status(int status)
    {
        status_code = status;
    }

    void response::set_header(const std::string &key, const std::string &value)
    {
        headers[key] = value;
    }

    void response::set_body(const uint8_t *data, size_t size)
    {
        body.assign(data, data + size);
    }

    void response::write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback)
    {
        bool has_more = true;
        while (has_more)
        {
            std::pair<const uint8_t *, size_t> chunk;
            has_more = callback(chunk);
            if(chunk.first && chunk.second > 0)
            {
                body.insert(body.end(), chunk.first, chunk.first + chunk.second);
            }
        }
        
    }
}