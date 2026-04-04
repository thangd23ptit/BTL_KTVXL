#include "timer.h"

void Timer_Init(void)
{
    TIM_TimeBaseInitTypeDef tim;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    tim.TIM_Prescaler = 72 - 1;   
    tim.TIM_Period = 0xFFFF;      
    tim.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4, &tim);
    TIM_Cmd(TIM4, ENABLE);
}

uint32_t Micros(void)
{
    return TIM_GetCounter(TIM4);
}

void Delay_us(uint16_t us)
{
    uint16_t start = TIM_GetCounter(TIM4);

    while((uint16_t)(TIM_GetCounter(TIM4) - start) < us);
}

void Delay_ms(uint16_t ms)
{
    while(ms--)
    {
        Delay_us(1000);
    }
}

