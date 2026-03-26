#include <desktop.hpp>

class wfApp : public wxApp
{
public:
    void Init(webframe::desktop::runtime_data *runtime_data)
    {
        _runtime_data = runtime_data;
    }

    bool OnInit() override
    {
        webframe::desktop_config config;
        _runtime_data->application->configure_desktop(&config);
        _runtime_data->application->configure_router(_runtime_data->router);
        _runtime_data->context = std::make_unique<webframe::desktop::context>(&config, _runtime_data->router);
        _runtime_data->application->launch_desktop(_runtime_data->context.get());
        return true;
    }

private:
    webframe::desktop::runtime_data *_runtime_data;
};

namespace webframe
{
    namespace desktop
    {
        int runtime::launch_wx_app(wfApp *app, webframe::application *a, webframe::router *r)
        {
            int result(0);
            _runtime_data.application = a;
            _runtime_data.router = r;
            app->Init(&_runtime_data);
            if (app->CallOnInit())
            {
                result = app->OnRun();
            }
            else
            {
                result = 1;
            }
            wxEntryCleanup();
            return result;
        }
    }

    runtime *create_runtime()
    {
        return new desktop::runtime();
    }
}

// keep platform specific garbage down here
wxIMPLEMENT_APP_NO_MAIN(wfApp);
#ifdef WEBFRAME_WIN32_APP
#include <wx/msw/init.h>
int webframe::desktop::runtime::dispatch(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, webframe::application *a, webframe::router *r)
{
    wxEntryStart(hInstance);
    return launch_wx_app(reinterpret_cast<wfApp *>(wxTheApp), a, r);
}
#else
int webframe::desktop::runtime::dispatch(int argc, const char **argv, webframe::application *a, webframe::router *r)
{
    wxEntryStart(argc, const_cast<char **>(argv));
    return launch_wx_app(reinterpret_cast<wfApp *>(wxTheApp), a, r);
}
#endif