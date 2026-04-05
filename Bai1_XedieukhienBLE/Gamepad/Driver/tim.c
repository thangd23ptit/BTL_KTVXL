#include "tim.h"

void TIM2_Init_1ms(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* 72MHz / 7200 = 10kHz => 0.1ms */
    TIM2->PSC = 7200 - 1;

    /* 10 tick = 1ms */
    TIM2->ARR = 10 - 1;

    TIM2->CNT = 0;

    /* force update register */
    TIM2->EGR |= TIM_EGR_UG;

    /* clear update flag */
    TIM2->SR &= ~TIM_SR_UIF;

    /* start timer */
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