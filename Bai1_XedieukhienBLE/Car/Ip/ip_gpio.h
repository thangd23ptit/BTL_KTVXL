#ifndef _IP_GPIO_H
#define _IP_GPIO_H

#include "stm32f10x.h"
#include <stdint.h>

void Ip_GPIO_Config_Output(GPIO_TypeDef *GPIOx, uint16_t pin);
void Ip_GPIO_Config_Input_PU(GPIO_TypeDef *GPIOx, uint16_t pin);
void Ip_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state);
uint8_t Ip_GPIO_Read(GPIO_TypeDef *GPIOx, uint16_t pin);
void Ip_GPIO_Config_Input(GPIO_TypeDef *GPIOx, uint16_t pin);

#endif