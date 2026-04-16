#ifndef _IP_GPIO_H
#define _IP_GPIO_H

#include "stm32f10x.h"
#include <stdint.h>

typedef enum {
    IP_GPIO_MODE_OUTPUT_PP,
    IP_GPIO_MODE_INPUT_PULLUP,
    IP_GPIO_MODE_INPUT_FLOATING
} ip_gpio_mode_t;

void Ip_GPIO_Config(GPIO_TypeDef *GPIOx, uint16_t pin, ip_gpio_mode_t mode);
void Ip_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state);
uint8_t Ip_GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t pin);
void Ip_GPIO_Toggle(GPIO_TypeDef *GPIOx, uint16_t pin);

#endif