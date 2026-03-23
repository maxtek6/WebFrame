#ifndef WEBFRAME_TEST_APPLICATION_HPP
#define WEBFRAME_TEST_APPLICATION_HPP

#include <webframe.hpp>

namespace webframe::test
{
    class client;

    class application : public webframe::application
    {
    public:
        void configure_router(webframe::router *router) override;
        void on_dispatch() override;

    protected:
        virtual void setup_router(webframe::router *router);
        virtual void run_tests(client *c) = 0;
    private:
        std::unique_ptr<client> _client;
    };

    class dispatch_error : public application
    {
    protected:
        void run_tests(client *c) override;
    };

    class empty_router : public application
    {
    protected:
        void run_tests(client *c) override;
    };
}

#endif