#ifndef __SENSOR_H
#define __SENSOR_H

#include "stm32f10x.h"
#include <stdint.h>

typedef struct
{
    uint16_t front;
    uint16_t left;
    uint16_t right;
} sensor_data_t;

void Sensor_Init(void);
void Sensor_Trigger_All(uint8_t id);
sensor_data_t Sensor_GetData(void);

#endif