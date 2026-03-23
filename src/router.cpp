#include <webframe.hpp>

class global_default_handler : public webframe::handler
{
protected:
    void handle_get(const webframe::request* req, webframe::response* res) override
    {
        throw webframe::exception::not_found;
    }

    void handle_post(const webframe::request* req, webframe::response* res) override
    {
        throw webframe::exception::not_found;
    }

    void handle_put(const webframe::request* req, webframe::response* res) override
    {
        throw webframe::exception::not_found;
    }

    void handle_delete(const webframe::request* req, webframe::response* res) override
    {
        throw webframe::exception::not_found;
    }
};

static global_default_handler g_default_handler;

namespace webframe
{
    void router::add_route(const std::string& path, handler* h)
    {
        _handlers[path] = h;
    }

    void router::set_default(handler* h)
    {
        _default_handler = h;
    }

    handler* router::find_route(const std::string& path)
    {
        auto it = _handlers.find(path);
        if (it != _handlers.end()) {
            return it->second;
        }
        return get_default();
    }

    handler* router::get_default()
    {
        return _default_handler ? _default_handler : &g_default_handler;      
    }
}