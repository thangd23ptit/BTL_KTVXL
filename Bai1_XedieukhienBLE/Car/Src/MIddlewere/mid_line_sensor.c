#include "mid_line_sensor.h"
#include "ip_line_sensor.h"

void Mid_LineSensor_Init(void)
{
    Ip_LineSensor_Init();
}

uint8_t Mid_LineSensor_ReadRaw(void)
{
    return Ip_LineSensor_ReadRaw();
}

int8_t Mid_LineSensor_GetError(void)
{
    return Ip_LineSensor_GetError();
}