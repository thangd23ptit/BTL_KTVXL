#ifndef _MID_GPIO_H
#define _MID_GPIO_H

#include "stm32f10x.h"
#include <stdint.h>

void Mid_GPIO_Config_Output(GPIO_TypeDef *GPIOx, uint16_t pin);
void Mid_GPIO_Config_Input_PU(GPIO_TypeDef *GPIOx, uint16_t pin);
void Mid_GPIO_Config_Input(GPIO_TypeDef *GPIOx, uint16_t pin);

void Mid_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state);
uint8_t Mid_GPIO_Read(GPIO_TypeDef *GPIOx, uint16_t pin);

#endif