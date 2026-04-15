#include "app_mode.h"
#include "app_control.h"

app_mode_t App_Mode_Get(void)
{
    app_control_data_t data = App_Control_GetData();
    return (app_mode_t)data.mode;
}