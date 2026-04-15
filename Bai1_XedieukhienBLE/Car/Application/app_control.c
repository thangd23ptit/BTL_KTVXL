#include "app_control.h"
#include "mid_control.h"

void App_Control_Init(void)
{
    Mid_Control_Init();
}

void App_Control_Run(void)
{
    Mid_Control_Run();
}

app_control_data_t App_Control_GetData(void)
{
    mid_control_data_t mid_data = Mid_Control_GetData();

    app_control_data_t app_data;
    app_data.mode  = mid_data.mode;
    app_data.cmd   = mid_data.cmd;
    app_data.speed = mid_data.speed;

    return app_data;
}

void App_Control_Execute(app_control_data_t data)
{
    mid_control_data_t mid_data;

    mid_data.mode  = data.mode;
    mid_data.cmd   = data.cmd;
    mid_data.speed = data.speed;

    Mid_Control_Execute(mid_data);
}