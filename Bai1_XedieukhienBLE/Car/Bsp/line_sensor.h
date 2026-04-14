#ifndef __LINE_SENSOR_H
#define __LINE_SENSOR_H

#include "stm32f10x.h"

void LineSensor_Init(void);
uint8_t LineSensor_ReadRaw(void);
int8_t LineSensor_GetError(void);

#endif