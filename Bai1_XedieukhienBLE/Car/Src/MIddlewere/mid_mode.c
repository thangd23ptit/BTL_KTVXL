#include "mid_mode.h"
#include "mid_control.h"

mid_mode_t Mid_Mode_Get(void)
{
    mid_control_data_t data = Mid_Control_GetData();
    return (mid_mode_t)data.mode;
}