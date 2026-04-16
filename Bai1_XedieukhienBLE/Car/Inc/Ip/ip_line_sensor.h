#ifndef _IP_LINE_SENSOR_H
#define _IP_LINE_SENSOR_H

#include "stm32f10x.h"

// ================== FUNCTION ==================

void Ip_LineSensor_Init(void);
uint8_t Ip_LineSensor_ReadRaw(void);
int8_t Ip_LineSensor_GetError(void);

#endif