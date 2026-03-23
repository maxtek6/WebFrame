#ifndef WEBFRAME_APPLICATION_HPP
#define WEBFRAME_APPLICATION_HPP

namespace webframe
{
    class router;

    class application
    {
    public:
        application() = default;
        virtual ~application() = default;
        virtual void configure_desktop();
        virtual void configure_server(int argc, const char **argv);
        virtual void configure_router(router *ctrl);
        virtual void on_dispatch();
    };
}

#endif