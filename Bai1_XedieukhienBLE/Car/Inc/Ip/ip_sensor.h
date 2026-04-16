#ifndef _IP_SENSOR_H
#define _IP_SENSOR_H

#include "stm32f10x.h"

void Ip_Sensor_Init(void);
void Ip_Sensor_Trigger(void);
uint16_t Ip_Sensor_GetFront(void);

#endif