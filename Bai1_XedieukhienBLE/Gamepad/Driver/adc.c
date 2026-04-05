#include "adc.h"

void ADC1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* PA0 PA1 analog */
    GPIOA->CRL &= ~((0xF << 0) | (0xF << 4));

    /* ADC clock = PCLK2 / 6 */
    RCC->CFGR &= ~RCC_CFGR_ADCPRE;
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    /* single conversion */
    ADC1->SQR1 = 0;

    /* enable ADC */
    ADC1->CR2 |= ADC_CR2_ADON;

    for(volatile int i = 0; i < 10000; i++);

    /* reset calibration */
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while(ADC1->CR2 & ADC_CR2_RSTCAL);

    /* calibration */
    ADC1->CR2 |= ADC_CR2_CAL;
    while(ADC1->CR2 & ADC_CR2_CAL);
}

uint16_t ADC1_ReadChannel(uint8_t channel)
{
    /* choose channel */
    ADC1->SQR3 = channel;

    /* sample time 239.5 cycles */
    ADC1->SMPR2 &= ~(0x7 << (channel * 3));
    ADC1->SMPR2 |=  (0x7 << (channel * 3));

    /* start conversion */
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* wait end */
    while(!(ADC1->SR & ADC_SR_EOC));

    uint16_t value = ADC1->DR;

    ADC1->SR &= ~ADC_SR_EOC;

    return value;
}

void Joystick_ADC_Read(uint16_t *x, uint16_t *y)
{
    *x = ADC1_ReadChannel(0);
    *y = ADC1_ReadChannel(1);
}