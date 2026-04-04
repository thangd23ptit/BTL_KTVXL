#include "adc.h"

void ADC1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // PA0, PA1 analog mode
    GPIOA->CRL &= (uint16_t)~((0xF << (0 * 4)) | (0xF << (1 * 4)));

    // ADC clock = PCLK2 / 6
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->SQR1 = 0;
    ADC1->CR2 |= ADC_CR2_ADON;

    for (volatile int i = 0; i < 10000; i++);

    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);
}

uint16_t ADC1_ReadChannel(uint8_t channel)
{
    ADC1->SQR3 = channel;
    ADC1->SMPR2 |= (uint16_t)(0x7 << (channel * 3)); // 239.5 cycles

    ADC1->CR2 |= ADC_CR2_ADON;
    while (!(ADC1->SR & ADC_SR_EOC));

    return (uint16_t)ADC1->DR;
}

void Joystick_ADC_Read(uint16_t *x, uint16_t *y)
{
    *x = ADC1_ReadChannel(0); // PA0
    *y = ADC1_ReadChannel(1); // PA1
}

