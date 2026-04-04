#ifndef __SENSOR_H
#define __SENSOR_H

#include <stdint.h>
#include "gpio.h"
#include "timer.h"
#include "stm32f10x.h"

void Config_Trigger_Sensor(void);
void Config_Echo_Sensor(void);
void Sensor_Init(void);
uint16_t Sensor_Front(void);
uint16_t Sensor_Left(void);
uint16_t Sensor_Right(void);

#endif