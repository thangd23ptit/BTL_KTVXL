#ifndef _MID_LINE_SENSOR_H
#define _MID_LINE_SENSOR_H

#include "stm32f10x.h"
#include <stdint.h>

void Mid_LineSensor_Init(void);
uint8_t Mid_LineSensor_ReadRaw(void);
int8_t Mid_LineSensor_GetError(void);

#endif