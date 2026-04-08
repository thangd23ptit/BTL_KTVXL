#include "adc.h"

static uint8_t current_channel = 0;

static void ADC_GPIO_Config(uint8_t channel){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN;
    if(channel <= 7){
        GPIOA->CRL &= ~(0xF << (channel * 4));
    }
    else if(channel == 8){
        GPIOB->CRL &= ~(0xF << 0);
    }
    else if(channel == 9){
        GPIOB->CRL &= ~(0xF << 4);
    }
}

void ADC1_Init_Single(uint8_t channel){
    static uint8_t adc_inited = 0;
    current_channel = channel;
    ADC_GPIO_Config(channel);
    if(!adc_inited){
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
        RCC->CFGR &= ~RCC_CFGR_ADCPRE;
        RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
        ADC1->CR1 = 0;
        ADC1->CR2 = 0;
        ADC1->CR2 |= ADC_CR2_EXTTRIG;
        ADC1->CR2 |= ADC_CR2_EXTSEL;
        ADC1->CR2 |= ADC_CR2_ADON;
        for(volatile int i=0; i<10000; i++);
        ADC1->CR2 |= ADC_CR2_RSTCAL;
        while(ADC1->CR2 & ADC_CR2_RSTCAL);
        ADC1->CR2 |= ADC_CR2_CAL;
        while(ADC1->CR2 & ADC_CR2_CAL);
        adc_inited = 1;
    }
    ADC1->SQR1 = 0;
    ADC1->SQR3 = channel;
    ADC1->SMPR2 &= ~(0x7 << (channel * 3));
    ADC1->SMPR2 |=  (0x7 << (channel * 3));
}

uint16_t ADC1_Read(void){
    ADC1->SQR3 = current_channel;
    ADC1->SR &= ~ADC_SR_EOC;
    ADC1->CR2 |= ADC_CR2_SWSTART;
    while(!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

float ADC1_ReadVoltage(void){
    return (ADC1_Read() * 3.3f) / 4095.0f;
}