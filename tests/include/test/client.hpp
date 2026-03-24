#ifndef WEBFRAME_TEST_CLIENT_HPP
#define WEBFRAME_TEST_CLIENT_HPP

#include <webframe.hpp>

namespace webframe::test
{
    class client
    {
    public:
        client(webframe::router *router);
        ~client() = default;
        void run(const webframe::request *request, webframe::response *response);
    private:
        webframe::router *_router;
    };
}

#endif