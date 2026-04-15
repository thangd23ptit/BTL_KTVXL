#include "ip_gpio.h"
#include "mid_gpio.h"

void Mid_GPIO_Config(GPIO_TypeDef *GPIOx, uint16_t pin, mid_gpio_mode_t mode)
{
    Ip_GPIO_Config(GPIOx, pin, mode);
}

void Mid_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state)
{
    Ip_GPIO_Write_Pin(GPIOx, pin, state);
}

uint8_t Mid_GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    return Ip_GPIO_Read_Pin(GPIOx, pin);
}

void Mid_GPIO_Toggle(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    Ip_GPIO_Toggle(GPIOx, pin);
}