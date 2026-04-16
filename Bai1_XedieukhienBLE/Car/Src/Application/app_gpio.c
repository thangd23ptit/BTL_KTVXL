#include "app_gpio.h"
#include "mid_gpio.h"

void App_GPIO_Config_Output(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    Mid_GPIO_Config_Output(GPIOx, pin);
}

void App_GPIO_Config_Input_PU(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    Mid_GPIO_Config_Input_PU(GPIOx, pin);
}

void App_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state)
{
    Mid_GPIO_Write_Pin(GPIOx, pin, state);
}

uint8_t App_GPIO_Read(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    return Mid_GPIO_Read(GPIOx, pin);
}

void App_GPIO_Config_Input(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    Mid_GPIO_Config_Input(GPIOx, pin);
}