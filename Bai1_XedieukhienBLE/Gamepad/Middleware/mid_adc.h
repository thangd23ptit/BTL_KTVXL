#ifndef _MID_ADC_H
#define _MID_ADC_H

#include "stm32f10x.h"
#include <stdint.h>

void Mid_ADC1_Init_Single(uint8_t channel);
uint16_t Mid_ADC1_Read(void);
float Mid_ADC1_ReadVoltage(void);

#endif