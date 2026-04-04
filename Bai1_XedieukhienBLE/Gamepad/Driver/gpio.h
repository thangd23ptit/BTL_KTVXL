#ifndef GPIO_H
#define GPIO_H

#include "stm32f10x.h"

void GPIO_Config_Output(GPIO_TypeDef *GPIOx, uint16_t pin);
void GPIO_Config_Input_PU(GPIO_TypeDef *GPIOx, uint16_t pin);
void GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state);
uint8_t GPIO_Read(GPIO_TypeDef *GPIOx, uint16_t pin);

#endif