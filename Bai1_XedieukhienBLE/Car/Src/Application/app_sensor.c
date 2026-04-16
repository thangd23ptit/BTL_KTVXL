#include "app_sensor.h"
#include "mid_sensor.h"

void App_Sensor_Init(void)
{
    Mid_Sensor_Init();
}

void App_Sensor_Trigger(void)
{
    Mid_Sensor_Trigger();
}

uint16_t App_Sensor_GetFront(void)
{
    return Mid_Sensor_GetFront();
}