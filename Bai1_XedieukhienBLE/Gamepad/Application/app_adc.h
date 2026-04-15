#ifndef _APP_ADC_H
#define _APP_ADC_H

#include "stm32f10x.h"
#include <stdint.h>

void App_ADC1_Init_Single(uint8_t channel);
uint16_t App_ADC1_Read(void);
float App_ADC1_ReadVoltage(void);

#endif