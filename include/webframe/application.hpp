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

#ifndef WEBFRAME_APPLICATION_HPP
#define WEBFRAME_APPLICATION_HPP

/**
 * @file webframe/application.hpp
 * @brief WebFrame application API
 * @author John R Patek Sr <johnpatek2@gmail.com>
 */
namespace webframe
{
    class desktop_config;
    class desktop_context;
    class server_config;
    class server_context;
    class router;

    /**
     * @class application
     * @brief abstract interface for WebFrame applications
     * @details Represents a single interface for all WebFrame runtimes.
     */
    class application
    {
    public:
        application() = default;
        virtual ~application() = default;

        /**
         * @brief configure the application for a desktop runtime
         * @param config the desktop configuration for the application
         * @details This is only used for desktop runtimes. Does not need to 
         * be implemented for server-only applications.
         */
        virtual void configure_desktop(desktop_config *config);
        
        /**
         * @brief configure the application for a server runtime
         * @param config the server configuration for the application
         * @param argc the number of command-line arguments
         * @param argv the command-line arguments
         * @details This is only used for server runtimes. Does not need to 
         * be implemented for desktop-only applications.
         */
        virtual void configure_server(server_config *config, int argc, const char **argv);
        
        /**
         * @brief configure the router for the application
         * @param router the router to configure
         * @details This is used to set handlers for HTTP traffic. This method 
         * should always be implemented, or the application will be unable to
         * handle requests.
         */
        virtual void configure_router(router *ctrl);

        /**
         * @brief launch the application in a desktop runtime
         * @param context the desktop context to use for launching the application
         * @details This is only used for desktop runtimes. The base implmentation will
         * create a single window with the default size and load /index.html from the 
         * router. The context pointer will remain valid while the application is running, 
         * so it can be used to create additional windows or perform other operations.
         */
        virtual void launch_desktop(desktop_context *context);
       
        /**
         * @brief launch the application in a server runtime
         * @param context the server context to use for launching the application
         * @details This is only used for server runtimes. The base implementation will
         * register SIGINT as the kill signal. The context pointer will remain valid while 
         * the application is running.
         */
        virtual void launch_server(server_context *context);
    };
}

#endif