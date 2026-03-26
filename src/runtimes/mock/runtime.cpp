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
                    webframe::desktop_config desktop_config;
                    webframe::server_config server_config;
                    a->configure_desktop(&desktop_config);
                    a->configure_server(&server_config, argc, argv);
                    a->configure_router(r);
                    a->launch_desktop(nullptr);
                    a->launch_server(nullptr);
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

    runtime *create_runtime()
    {
        return new mock::runtime();
    }
}
