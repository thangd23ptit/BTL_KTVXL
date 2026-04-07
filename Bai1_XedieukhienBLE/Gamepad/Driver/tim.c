#include "tim.h"

void TIM2_Init_1ms(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->PSC = 7200 - 1;   // 72MHz -> 10kHz
    TIM2->ARR = 10 - 1;     // 1ms

    TIM2->CNT = 0;
    TIM2->EGR |= TIM_EGR_UG;
    TIM2->SR &= ~TIM_SR_UIF;
    TIM2->CR1 |= TIM_CR1_CEN;
}

void Delay_ms(uint16_t ms)
{
    while(ms--)
    {
        TIM2->CNT = 0;
        TIM2->SR &= ~TIM_SR_UIF;

        while(!(TIM2->SR & TIM_SR_UIF));
    } 	
}