#include "gpio.h"

static void GPIO_EnableClock(GPIO_TypeDef *GPIOx)
{
    if (GPIOx == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    else if (GPIOx == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    else if (GPIOx == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
}

void GPIO_Config_Output(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    GPIO_EnableClock(GPIOx);

    if (pin < 8)
    {
        GPIOx->CRL &= (uint16_t)~(0xF << (pin * 4));
        GPIOx->CRL |= (uint16_t) (0x3 << (pin * 4)); // output 50MHz push-pull
    }
    else
    {
        pin -= 8;
        GPIOx->CRH &= (uint16_t)~(0xF << (pin * 4));
        GPIOx->CRH |= (uint16_t) (0x3 << (pin * 4));
    }
}

void GPIO_Config_Input_PU(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    GPIO_EnableClock(GPIOx);

    if (pin < 8)
    {
        GPIOx->CRL &=  (uint16_t)~(0xF << (pin * 4));
        GPIOx->CRL |=  (uint16_t)(0x8 << (pin * 4)); // input pull-up/down
    }
    else
    {
        pin -= 8;
        GPIOx->CRH &= (uint16_t)~(0xF << (pin * 4));
        GPIOx->CRH |= (uint16_t) (0x8 << (pin * 4));
    }

    GPIOx->ODR |= (1 << pin); // pull-up
}

void GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state)
{
    if (state) GPIOx->BSRR = (1 << pin);
    else GPIOx->BRR = (1 << pin);
}

uint8_t GPIO_Read(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    return (GPIOx->IDR & (1 << pin)) ? 1 : 0;
}

