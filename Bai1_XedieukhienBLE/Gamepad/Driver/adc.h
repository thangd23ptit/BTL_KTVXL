#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"

void ADC1_Init_Single(uint8_t channel);
uint16_t ADC1_Read(void);
float ADC1_ReadVoltage(void);

#endif