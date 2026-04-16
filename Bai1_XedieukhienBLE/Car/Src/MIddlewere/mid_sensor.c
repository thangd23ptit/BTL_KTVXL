#include "mid_sensor.h"
#include "ip_sensor.h"

void Mid_Sensor_Init(void)
{
    Ip_Sensor_Init();
}

void Mid_Sensor_Trigger(void)
{
    Ip_Sensor_Trigger();
}

uint16_t Mid_Sensor_GetFront(void)
{
    return Ip_Sensor_GetFront();
}