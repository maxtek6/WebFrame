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
#include <webframe/config.hpp>
#include <webframe/context.hpp>
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

/**
 * @file webframe.hpp
 * @brief WebFrame API
 * @author John R Patek Sr <johnpatek2@gmail.com>
 */
namespace webframe
{
    /**
     * @enum method
     * @brief HTTP methods supported by WebFrame
     * @details Basic CRUD operations via the HTTP methods GET, POST, PUT, and DELETE.
     */
    enum class method
    {
        http_get,
        http_post,
        http_put,
        http_delete
    };

    /**
     * @class request
     * @brief abstract interface for HTTP requests
     * @details Common abstraction for all WebFrame runtimes to process HTTP requests.
     */
    class request
    {
    public:
        /**
         * @brief get the HTTP method of the request
         * @return the HTTP method of the request
         */
        virtual method get_method() const = 0;
        /**
         * @brief get the path of the request
         * @return the path of the request
         */
        virtual std::string get_path() const = 0;
        
        /**
         * @brief get the value of a specific header
         * @param key the header key
         * @param value reference to the header value
         * @return true if the header exists, false otherwise. The string reference will only 
         * be set if the header exists.
         */
        virtual bool get_header(const std::string &key, std::string &value) const = 0;

        /**
         * @brief get the body of the request as a pointer and size
         * @return a pair containing a pointer to the body data and the size of the body
         * @details The body data is not guaranteed to be null-terminated. The pointer and size are only 
         * valid for the duration of the request handling. If the request does not have a body, the pointer 
         * will be null and the size will be zero.
         */
        virtual std::pair<const uint8_t *, size_t> get_body() const = 0;

        /**
         * @brief read the body of the request using a callback
         * @param callback a function to be called with the body data and size
         * @details The callback will be called with chunks of the body data. None of the runtimes are 
         * currently capable of streaming request bodies, so the callback will be called at most once with the 
         * entire body. If there is no request body, the callback will not be called.
         */
        virtual void read_body(const std::function<void(const uint8_t *, size_t)> &callback) const = 0;
    };

    /**
     * @class response
     * @brief abstract interface for HTTP responses
     * @details Common abstraction for all WebFrame runtimes to generate HTTP responses.
     */
    class response
    {
    public:
        /**
         * @brief set the HTTP status code of the response
         * @param status_code the HTTP status code
         * @details The status code is not checked against valid HTTP status codes. It can be set to 
         * any integer value, but there is no guarantee that the runtime implementation will accept it.
         */
        virtual void set_status(int status_code) = 0;
        
        /**
         * @brief set a header of the response
         * @param key the header key
         * @param value the header value
         * @details The headers are not validated, and there is no standard way to handle duplicate entries.
         */
        virtual void set_header(const std::string &key, const std::string &value) = 0;
        
        /**
         * @brief set the body of the response
         * @param data pointer to the body data
         * @param size the size of the body data
         * @details This must be called once after the status and headers have been set. If it is called 
         * before, the status will be 200 and the headers will be empty. There is no standard way to handle 
         * multiple calls.
         */
        virtual void set_body(const uint8_t *data, size_t size) = 0;

        /**
         * @brief write the body of the response using a callback
         * @param callback a function to be called with a chunk to set the body data and size.
         * @details The callback will be called with chunks of the body data until it returns false to indicate 
         * end-of-stream. The callback will always be called at least once, and will only populate the chunk if 
         * the data is not null and the size is greater than zero.
         */
        virtual void write_body(const std::function<bool(std::pair<const uint8_t *, size_t> &)> &callback) = 0;
    };

    /**
     * @class runtime
     * @brief abstract interface for WebFrame runtimes
     * @details Given an application and a router, the runtime is responsible for abstracting HTTP traffic from the 
     * underlying platform. The user will rarely, if ever, interact with this interface directly.
     */
    class runtime
    {
    public:
#ifdef WEBFRAME_WIN32_APP
        /**
         * @brief dispatch the application using the Win32 API
         * @param hInstance the handle to the current instance of the application
         * @param hPrevInstance the handle to the previous instance of the application (always null)
         * @param lpCmdLine the command line arguments as a single string
         * @param nCmdShow the show state of the application window
         * @param a the application to dispatch
         * @param r the router to use for dispatching requests
         * @return the exit code of the application
         * @details This is only used for the Win32 desktop runtime. You should not call this directly. Use the WEBFRAME_MAIN macro 
         * to define the entry point of your application, and it will call this function for you.
         */
        virtual int dispatch(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, application *a, router *r) = 0;
#else
        /**
         * @brief dispatch the application using the standard C++ API
         * @param argc the number of command line arguments
         * @param argv the command line arguments as an array of strings
         * @param a the application to dispatch
         * @param r the router to use for dispatching requests
         * @return the exit code of the application
         * @details This is used for all non-Win32 runtimes, including Windows servers. Like the other dispatch function, it 
         * should not be called directly.
         */
        virtual int dispatch(int argc, const char **argv, application *a, router *r) = 0;
#endif
    };

    /**
     * @brief create a WebFrame runtime instance
     * @return a pointer to a WebFrame runtime instance
     * @details Stub for constructing a runtime. The actual implementation is determined by the runtime library.
     */
    runtime *create_runtime();
}

#if defined(WEBFRAME_WIN32_APP)
#define WEBFRAME_MAIN(AppType)                                                                      \
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) \
    {                                                                                               \
        std::unique_ptr<webframe::runtime> runtime(webframe::create_runtime());                     \
        AppType app;                                                                                \
        webframe::router router;                                                                    \
        return runtime->dispatch(hInstance, hPrevInstance, lpCmdLine, nCmdShow, &app, &router);     \
    }
#else
#define WEBFRAME_MAIN(AppType)                                                  \
    int main(int argc, const char **argv)                                       \
    {                                                                           \
        std::unique_ptr<webframe::runtime> runtime(webframe::create_runtime()); \
        AppType app;                                                            \
        webframe::router router;                                                \
        return runtime->dispatch(argc, argv, &app, &router);                    \
    }
#endif

#endif
