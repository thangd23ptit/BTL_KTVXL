#ifndef _APP_SENSOR_H
#define _APP_SENSOR_H

#include "stm32f10x.h"
#include <stdint.h>

void App_Sensor_Init(void);
void App_Sensor_Trigger(void);
uint16_t App_Sensor_GetFront(void);

#endif