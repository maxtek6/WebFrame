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

#ifndef WEBFRAME_TEST_HPP
#define WEBFRAME_TEST_HPP

#include <test/application.hpp>
#include <test/client.hpp>
#include <test/message.hpp>

#include <maxtest.hpp>

namespace webframe::test
{
    template <class ApplicationType, int ExpectedStatusCode = 0>
    struct test_case
    {
        static inline void run()
        {
            std::unique_ptr<webframe::runtime> runtime(webframe::create_runtime());
            ApplicationType app;
            webframe::router router;
            const int actual_result = runtime->dispatch(0, nullptr, &app, &router);
            MAXTEST_ASSERT(actual_result == ExpectedStatusCode);
        }
    };

    using noop_test = test_case<webframe::application>;
    using dispatch_error_test = test_case<dispatch_error, 1>;
    using empty_router_test = test_case<empty_router>;
}

#define WEBFRAME_TEST_CASE(TestName) \
    MAXTEST_TEST_CASE(webframe::TestName) \
    { \
    }

#endif