#include "app_gpio.h"
#include "mid_gpio.h"

void App_GPIO_Config(GPIO_TypeDef *GPIOx, uint16_t pin, app_gpio_mode_t mode)
{
    Mid_GPIO_Config(GPIOx, pin, (mid_gpio_mode_t)mode);
}

void App_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state)
{
    Mid_GPIO_Write_Pin(GPIOx, pin, state);
}

uint8_t App_GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    return Mid_GPIO_Read_Pin(GPIOx, pin);
}

void App_GPIO_Toggle(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    Mid_GPIO_Toggle(GPIOx, pin);
}