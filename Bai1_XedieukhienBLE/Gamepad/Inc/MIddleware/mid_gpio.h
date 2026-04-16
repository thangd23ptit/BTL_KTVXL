#ifndef _MID_GPIO_H
#define _MID_GPIO_H

#include "stm32f10x.h"
#include <stdint.h>

typedef enum {
    MID_GPIO_MODE_OUTPUT_PP,
    MID_GPIO_MODE_INPUT_PULLUP,
    MID_GPIO_MODE_INPUT_FLOATING
} mid_gpio_mode_t;

void Mid_GPIO_Config(GPIO_TypeDef *GPIOx, uint16_t pin, mid_gpio_mode_t mode);
void Mid_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state);
uint8_t Mid_GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t pin);
void Mid_GPIO_Toggle(GPIO_TypeDef *GPIOx, uint16_t pin);

#endif