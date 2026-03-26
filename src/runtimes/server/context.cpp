#include <server.hpp>

namespace webframe::server
{
    context::context(event_base *base) : _base(base)
    {
    }

    void context::sighandle(int signum)
    {
        
    }
}