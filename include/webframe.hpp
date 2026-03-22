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

#ifndef WEBFRAME_HPP
#define WEBFRAME_HPP

#include <cstdint>

#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include <webframe/exception.hpp>
#include <webframe/handler.hpp>
#include <webframe/router.hpp>

#if defined(_WIN32) && defined(WEBFRAME_DESKTOP)
#define WEBFRAME_WIN32_APP 1
#endif

namespace webframe
{
    enum class method
    {
        GET,
        POST,
        PUT,
        DELETE
    };

    class request
    {
    public:
        virtual method get_method() const;
        virtual std::string get_path() const;
        virtual bool get_header(const std::string &key, std::string &value) const;
        virtual std::pair<const uint8_t *, size_t> get_body() const;
        virtual void read_body(const std::function<void(const uint8_t *, size_t)> &callback) const;
    };

    class response
    {
    public:
        virtual void set_status(int status_code);
        virtual void set_header(const std::string &key, const std::string &value);
        virtual void set_body(const uint8_t *data, size_t size);
        virtual void write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback);
    };

    class application
    {
    public:
        virtual void configure_desktop();
        virtual void configure_server(int argc, const char **argv);
        virtual void configure_router(router *ctrl);
    };

    class runtime
    {
    public:
#ifdef WEBFRAME_WIN32_APP
        virtual int dispatch(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow, application *a, router *r) = 0;
#else
        virtual int dispatch(int argc, const char **argv, application *a, router *r) = 0;
#endif
    };

    runtime *webframe_init();
}

#if defined(WEBFRAME_WIN32_APP)
    #define WEBFRAME_MAIN(AppType) \
        int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) \
        { \
            std::unique_ptr<webframe::runtime> runtime(webframe::webframe_init()); \
            AppType app; \
            webframe::router router; \
            return runtime->dispatch(hInstance, hPrevInstance, pCmdLine, nCmdShow, &app, &router); \
        }
#else
    #define WEBFRAME_MAIN(AppType) \
        int main(int argc, const char **argv) \
        { \
            std::unique_ptr<webframe::runtime> runtime(webframe::webframe_init()); \
            AppType app; \
            webframe::router router; \
            return runtime->dispatch(argc, argv, &app, &router); \
        }
#endif

#endif
