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
            std::unique_ptr<webframe::runtime> runtime(webframe::webframe_init());
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
        webframe::test::TestName::run(); \
    }

#endif