#include <test.hpp>

MAXTEST_MAIN
{
    WEBFRAME_TEST_CASE(noop_test);
    WEBFRAME_TEST_CASE(dispatch_error_test);
    WEBFRAME_TEST_CASE(empty_router_test);
};