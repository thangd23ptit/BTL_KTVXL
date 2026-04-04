#ifndef __ADC_H
#define __ADC_H
#include "stm32f10x.h"
void adc_Init(void);
int ADC_Read(uint8_t channel);

#endif

