#include "mid_control.h"
#include "ip_control.h"

void Mid_Control_Init(void)
{
    Ip_Control_Init();
}

void Mid_Control_Run(void)
{
    Ip_Control_Run();
}

mid_control_data_t Mid_Control_GetData(void)
{
    ip_control_data_t ip_data = Ip_Control_GetData();

    mid_control_data_t mid_data;
    mid_data.mode  = ip_data.mode;
    mid_data.cmd   = ip_data.cmd;
    mid_data.speed = ip_data.speed;

    return mid_data;
}

void Mid_Control_Execute(mid_control_data_t data)
{
    ip_control_data_t ip_data;

    ip_data.mode  = data.mode;
    ip_data.cmd   = data.cmd;
    ip_data.speed = data.speed;

    Ip_Control_Execute(ip_data);
}
