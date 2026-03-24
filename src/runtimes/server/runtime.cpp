#ifdef _WIN32
#include <winsock2.h>
#endif

#include <server.hpp>

#include <stdexcept>

#ifdef _WIN32
namespace
{
    class winsock_session
    {
    public:
        winsock_session()
        {
            const int result = WSAStartup(MAKEWORD(2, 2), &_data);
            if (result != 0)
            {
                throw std::runtime_error("WSAStartup failed");
            }
        }

        ~winsock_session()
        {
            WSACleanup();
        }

    private:
        WSADATA _data{};
    };
}
#endif

static void evhttp_callback(struct evhttp_request *req, void *arg)
{
    bool sent_response = false;
    int status = 200;
    webframe::router *runtime = static_cast<webframe::router *>(arg);
    webframe::server::request request(req);
    webframe::server::response response(req, sent_response, status);
    webframe::handler *handler = runtime->find_route(request.get_path());
    handler->handle_request(&request, &response);
    if (!sent_response)
    {
        evhttp_send_reply(req, status, nullptr, nullptr);
    }
}

namespace webframe
{
    namespace server
    {
        int runtime::dispatch(int argc, const char **argv, webframe::application *a, webframe::router *r)
        {
#ifdef _WIN32
            winsock_session winsock;
#endif
            a->configure_server(argc, argv);
            a->configure_router(r);
            _event_base.reset(event_base_new());
            _http.reset(evhttp_new(_event_base.get()));
            evhttp_set_gencb(_http.get(), evhttp_callback, r);
            listen("0.0.0.0", 8080);
            a->on_dispatch();
            serve();
            return 0;
        }
        void runtime::listen(const char *address, int port)
        {
            evhttp_bind_socket(_http.get(), address, port);
        }
        void runtime::serve()
        {
            event_base_dispatch(_event_base.get());
        }
        void runtime::stop()
        {
            event_base_loopbreak(_event_base.get());
        }
    }
    runtime *webframe_init()
    {
        return new server::runtime();
    }
}