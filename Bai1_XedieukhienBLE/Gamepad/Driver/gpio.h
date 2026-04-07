#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

typedef enum
{
    GPIO_MODE_OUTPUT_PP,
    GPIO_MODE_INPUT_PULLUP,
    GPIO_MODE_INPUT_FLOATING
} GPIO_Mode_Custom;

void GPIO_Config(GPIO_TypeDef *GPIOx,
                 uint16_t pin,
                 GPIO_Mode_Custom mode);

void GPIO_Write_Pin(GPIO_TypeDef *GPIOx,
                uint16_t pin,
                uint8_t state);

uint8_t GPIO_Read_Pin(GPIO_TypeDef *GPIOx,
                  uint16_t pin);

void GPIO_Toggle(GPIO_TypeDef *GPIOx,
                 uint16_t pin);

#endif