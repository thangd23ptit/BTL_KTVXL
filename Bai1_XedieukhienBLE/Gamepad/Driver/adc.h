#ifndef ADC_H
#define ADC_H

#include "stm32f10x.h"
#include <stdint.h>

void ADC1_Init(void);
uint16_t ADC1_ReadChannel(uint8_t channel);
void Joystick_ADC_Read(uint16_t *x, uint16_t *y);

#endif