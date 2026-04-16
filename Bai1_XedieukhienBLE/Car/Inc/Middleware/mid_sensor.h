#ifndef _MID_SENSOR_H
#define _MID_SENSOR_H

#include "stm32f10x.h"
#include <stdint.h>

void Mid_Sensor_Init(void);
void Mid_Sensor_Trigger(void);
uint16_t Mid_Sensor_GetFront(void);

#endif