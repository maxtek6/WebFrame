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

#ifndef WEBFRAME_TEST_APPLICATION_HPP
#define WEBFRAME_TEST_APPLICATION_HPP

#include <webframe.hpp>

namespace webframe::test
{
    class client;

    class application : public webframe::application
    {
    public:
        void configure_router(webframe::router *router) override;

    protected:
        virtual void setup_router(webframe::router *router);
        virtual void run_tests(client *c) = 0;
    private:
        std::unique_ptr<client> _client;
    };

    class dispatch_error : public application
    {
    protected:
        void run_tests(client *c) override;
    };

    class empty_router : public application
    {
    protected:
        void run_tests(client *c) override;
    };
}

#endif