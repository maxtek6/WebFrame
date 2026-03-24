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

#include <webframe/application.hpp>
#include <webframe/exception.hpp>
#include <webframe/handler.hpp>
#include <webframe/router.hpp>

#if defined(_WIN32) && defined(WEBFRAME_DESKTOP_RUNTIME)
#define WEBFRAME_WIN32_APP 1
#endif

#if defined(WEBFRAME_WIN32_APP)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

namespace webframe
{
    enum class method
    {
        http_get,
        http_post,
        http_put,
        http_delete
    };

    class request
    {
    public:
        virtual method get_method() const = 0;
        virtual std::string get_path() const = 0;
        virtual bool get_header(const std::string &key, std::string &value) const = 0;
        virtual std::pair<const uint8_t *, size_t> get_body() const = 0;
        virtual void read_body(const std::function<void(const uint8_t *, size_t)> &callback) const = 0;
    };

    class response
    {
    public:
        virtual void set_status(int status_code) = 0;
        virtual void set_header(const std::string &key, const std::string &value) = 0;
        virtual void set_body(const uint8_t *data, size_t size) = 0;
        virtual void write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback) = 0 ;
    };



    class runtime
    {
    public:
#ifdef WEBFRAME_WIN32_APP
        virtual int dispatch(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, application *a, router *r) = 0;
#else
        virtual int dispatch(int argc, const char **argv, application *a, router *r) = 0;
#endif
    };

    runtime *webframe_init();
}

#if defined(WEBFRAME_WIN32_APP)
    #define WEBFRAME_MAIN(AppType) \
        int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) \
        { \
            std::unique_ptr<webframe::runtime> runtime(webframe::webframe_init()); \
            AppType app; \
            webframe::router router; \
            return runtime->dispatch(hInstance, hPrevInstance, lpCmdLine, nCmdShow, &app, &router); \
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
