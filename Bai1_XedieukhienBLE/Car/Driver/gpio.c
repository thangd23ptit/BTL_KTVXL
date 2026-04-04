#include "gpio.h"

void GPIO_ConfigOutput(GPIO_TypeDef* port, uint16_t pin)
{
    GPIO_InitTypeDef gpio;

    gpio.GPIO_Pin = pin;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(port, &gpio);
}

void GPIO_ConfigInput(GPIO_TypeDef* port, uint16_t pin)
{
    GPIO_InitTypeDef gpio;

    gpio.GPIO_Pin = pin;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(port, &gpio);
}

void GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t pin, uint8_t state)
{
    if(state)
        GPIO_SetBits(GPIOx, pin);
    else
        GPIO_ResetBits(GPIOx, pin);
}
uint8_t GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t pin)
{
    return GPIO_ReadInputDataBit(GPIOx, pin);
}

void GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t pin)
{
    GPIOx->ODR ^= pin;
}