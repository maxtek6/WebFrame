#include <webframe.hpp>

#include <iostream>

namespace webframe
{
    namespace mock
    {
        class runtime : public webframe::runtime
        {
        public:
            int dispatch(int argc, const char ** argv, application *a, router *r) override
            {
                int result(0);
                try
                {
                    a->configure_desktop();
                    a->configure_server(argc, argv);
                    a->configure_router(r);
                    a->on_dispatch();
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                    result = 1;
                }
                return result;
            }
        };
    }

    runtime *webframe_init()
    {
        return new mock::runtime();
    }
}
