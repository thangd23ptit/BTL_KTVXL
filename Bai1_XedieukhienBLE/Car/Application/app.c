#include "app.h"
#include "app_auto.h"
#include "app_control.h"

static app_mode_t g_app_mode = APP_MODE_AUTO;

void App_SetMode(app_mode_t mode)
{
    g_app_mode = mode;
}

void App_Run(void)
{
    switch(g_app_mode)
    {
        case APP_MODE_AUTO:
            App_Auto_Run();
            break;
        case APP_MODE_MANUAL:
						App_Control_Run();
            break;
        default:
            App_Control_Run();
            break;
    }
}