#ifndef __SENSOR_H
#define __SENSOR_H

#include "stm32f10x.h"

void Sensor_Init(void);
void Sensor_Trigger(void);
uint16_t Sensor_GetFront(void);

#endif