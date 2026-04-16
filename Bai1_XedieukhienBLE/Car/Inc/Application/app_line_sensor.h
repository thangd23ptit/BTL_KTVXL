#ifndef _APP_LINE_SENSOR_H
#define _APP_LINE_SENSOR_H

#include "stm32f10x.h"
#include <stdint.h>

void App_LineSensor_Init(void);
uint8_t App_LineSensor_ReadRaw(void);
int8_t App_LineSensor_GetError(void);

#endif