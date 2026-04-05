#include "app.h"
#include "mode.h"
#include "app_control.h"
#include "app_auto.h"

void App_Init(void)
{
    /* reserved */
}

void App_Run(void)
{
    switch(Mode_Get())
    {
        case MODE_MANUAL:
            App_Control_Run();
            break;

        case MODE_AUTO:
            App_Auto_Run();
            break;

        default:
            App_Control_Run();
            break;
    }
}