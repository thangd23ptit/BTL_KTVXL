#include "gpio.h"

static void GPIO_EnableClock(GPIO_TypeDef *GPIOx)
{
    if(GPIOx == GPIOA) RCC->APB2ENR |= (1 << 2);
    else if(GPIOx == GPIOB) RCC->APB2ENR |= (1 << 3);
    else if(GPIOx == GPIOC) RCC->APB2ENR |= (1 << 4);
    else if(GPIOx == GPIOD) RCC->APB2ENR |= (1 << 5);
}

void GPIO_Config(GPIO_TypeDef *GPIOx,
                 uint16_t pin,
                 GPIO_Mode_Custom mode)
{
    uint8_t pos = 0;

    GPIO_EnableClock(GPIOx);

    while(((pin >> pos) & 0x01) == 0) pos++;

    volatile uint32_t *config_reg;
    if(pos < 8)
        config_reg = &GPIOx->CRL;
    else
    {
        config_reg = &GPIOx->CRH;
        pos -= 8;
    }

    *config_reg &= ~(0xF << (pos * 4));

    switch(mode)
    {
        case GPIO_MODE_OUTPUT_PP:
            *config_reg |= (0x3 << (pos * 4));   // MODE=11, CNF=00
            break;

        case GPIO_MODE_INPUT_PULLUP:
            *config_reg |= (0x8 << (pos * 4));   // MODE=00, CNF=10
            GPIOx->ODR |= pin;
            break;

        case GPIO_MODE_INPUT_FLOATING:
            *config_reg |= (0x4 << (pos * 4));   // MODE=00, CNF=01
            break;
    }
}

void GPIO_Write_Pin(GPIO_TypeDef *GPIOx,
                uint16_t pin,
                uint8_t state)
{
    if(state)
        GPIOx->BSRR = pin;
    else
        GPIOx->BRR = pin;
}

uint8_t GPIO_Read(GPIO_TypeDef *GPIOx,
                  uint16_t pin)
{
    return (GPIOx->IDR & pin) ? 1 : 0;
}

void GPIO_Toggle(GPIO_TypeDef *GPIOx,
                 uint16_t pin)
{
    GPIOx->ODR ^= pin;
}