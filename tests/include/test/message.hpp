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

#ifndef WEBFRAME_TEST_MESSAGE_HPP
#define WEBFRAME_TEST_MESSAGE_HPP

#include <webframe.hpp>

#include <map>
#include <vector>

namespace webframe::test
{
    struct message_data
    {
        std::map<std::string, std::string> headers;
        std::vector<uint8_t> body;
    };

    struct request_data : public message_data
    {
        webframe::method method;
        std::string path;
    };

    struct response_data : public message_data
    {
        int status_code;
    };

    class request : public webframe::request, public request_data
    {
    public:
        webframe::method get_method() const override;
        std::string get_path() const override;
        bool get_header(const std::string &key, std::string &value) const override;
        std::pair<const uint8_t *, size_t> get_body() const override;
        void read_body(const std::function<void(const uint8_t *, size_t)> &callback) const override;
    };

    class response : public webframe::response, public response_data
    {
    public:
        void set_status(int status) override;
        void set_header(const std::string &key, const std::string &value) override;
        void set_body(const uint8_t *data, size_t size) override;
        void write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback) override;
    };
}
#endif