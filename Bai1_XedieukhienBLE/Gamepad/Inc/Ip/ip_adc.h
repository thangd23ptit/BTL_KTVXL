#ifndef _IP_ADC_H
#define _IP_ADC_H

#include "stm32f10x.h"
#include <stdint.h>

void Ip_ADC1_Init_Single(uint8_t channel);
uint16_t Ip_ADC1_Read(void);
float Ip_ADC1_ReadVoltage(void);

#endif