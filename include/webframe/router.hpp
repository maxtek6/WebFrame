#ifndef WEBFRAME_ROUTER_HPP
#define WEBFRAME_ROUTER_HPP

#include <string>
#include <unordered_map>

namespace webframe
{
    class request;
    class response;
    class handler;

    class router
    {
    public:
        router() = default;
        ~router() = default;
        void add_route(const std::string& path, handler* h);
        handler *find_route(const std::string& path);
        void set_default(handler* h);
        handler* get_default();
    private:        
        std::unordered_map<std::string, handler*> _handlers;
        handler* _default_handler = nullptr;
    };
}
#endif