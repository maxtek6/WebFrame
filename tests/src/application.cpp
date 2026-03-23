#include <test.hpp>

namespace webframe::test
{
    void application::configure_router(webframe::router *router)
    {
        setup_router(router);
        _client = std::make_unique<client>(router);
    }

    void application::setup_router(webframe::router *router)
    {
        (void)router;
    }

    void application::on_dispatch()
    {
        run_tests(_client.get());
    }

    void dispatch_error::run_tests(client *c)
    {
        (void)c;
        throw std::runtime_error("dispatch error");
    }

    void empty_router::run_tests(client *c)
    {
        request req;
        req.method = webframe::method::http_get;
        req.path = "/somepath";
        response res;
        c->run(&req, &res);
        MAXTEST_ASSERT(res.status_code == 404);
    }
}