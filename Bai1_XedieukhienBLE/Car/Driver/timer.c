#include "timer.h"

void TIM3_Init_1ms(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3->PSC = 7200 - 1;
    TIM3->ARR = 10 - 1;
    TIM3->CNT = 0;
    TIM3->EGR |= TIM_EGR_UG;
    TIM3->SR &= ~TIM_SR_UIF;
    TIM3->CR1 |= TIM_CR1_CEN;
}

void Delay_ms(uint16_t ms)
{
    while(ms--)
    {
        TIM3->CNT = 0;
        TIM3->SR &= ~TIM_SR_UIF;
        while(!(TIM3->SR & TIM_SR_UIF));
    }
}