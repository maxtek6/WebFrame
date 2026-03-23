#include <test.hpp>

namespace webframe::test
{
    client::client(webframe::router *router) : _router(router)
    {
    }

    void client::run(const webframe::request *request, webframe::response *response)
    {
        webframe::handler *handler = _router->find_route(request->get_path());
        handler->handle_request(request, response);
    }
}