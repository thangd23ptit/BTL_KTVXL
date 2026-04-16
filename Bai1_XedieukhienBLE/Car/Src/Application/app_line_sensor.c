#include "app_line_sensor.h"
#include "mid_line_sensor.h"

void App_LineSensor_Init(void)
{
    Mid_LineSensor_Init();
}

uint8_t App_LineSensor_ReadRaw(void)
{
    return Mid_LineSensor_ReadRaw();
}

int8_t App_LineSensor_GetError(void)
{
    return Mid_LineSensor_GetError();
}