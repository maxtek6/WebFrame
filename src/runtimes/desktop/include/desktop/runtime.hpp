#ifndef WEBFRAME_DESKTOP_RUNTIME_HPP
#define WEBFRAME_DESKTOP_RUNTIME_HPP

#include "wxwidgets.hpp"

class wfApp;

namespace webframe::desktop
{
    class context;

    struct runtime_data
    {
        webframe::application *application;
        webframe::router *router;
        std::unique_ptr<webframe::desktop_context> context;
    };

    class runtime : public webframe::runtime
    {
    public:
#ifdef WEBFRAME_WIN32_APP
        int dispatch(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, webframe::application *a, webframe::router *r) override;
#else
        int dispatch(int argc, const char **argv, webframe::application *a, webframe::router *r) override;
#endif
    private:
        int launch_wx_app(wfApp *app, webframe::application *a, webframe::router *r);
        runtime_data _runtime_data;
    };
}

#endif