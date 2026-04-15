#ifndef _APP_GPIO_H
#define _APP_GPIO_H

#include "stm32f10x.h"
#include <stdint.h>

typedef enum {
    APP_GPIO_MODE_OUTPUT_PP,
    APP_GPIO_MODE_INPUT_PULLUP,
    APP_GPIO_MODE_INPUT_FLOATING
} app_gpio_mode_t;

void App_GPIO_Config(GPIO_TypeDef *GPIOx, uint16_t pin, app_gpio_mode_t mode);
void App_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state);
uint8_t App_GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t pin);
void App_GPIO_Toggle(GPIO_TypeDef *GPIOx, uint16_t pin);

#endif