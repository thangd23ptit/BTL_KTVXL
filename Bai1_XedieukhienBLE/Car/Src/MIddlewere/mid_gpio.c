#include "mid_gpio.h"
#include "ip_gpio.h"

void Mid_GPIO_Config_Output(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    Ip_GPIO_Config_Output(GPIOx, pin);
}

void Mid_GPIO_Config_Input_PU(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    Ip_GPIO_Config_Input_PU(GPIOx, pin);
}

void Mid_GPIO_Config_Input(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    Ip_GPIO_Config_Input(GPIOx, pin);
}

void Mid_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state)
{
    Ip_GPIO_Write_Pin(GPIOx, pin, state);
}

uint8_t Mid_GPIO_Read(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    return Ip_GPIO_Read(GPIOx, pin);
}