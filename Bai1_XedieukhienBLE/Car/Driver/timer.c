#include "timer.h"

static volatile uint32_t g_tick_ms = 0;

void TIM3_Init_1ms(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->PSC = 7200 - 1;
    TIM3->ARR = 10 - 1;
    TIM3->CNT = 0;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1  |= TIM_CR1_CEN;
    NVIC_EnableIRQ(TIM3_IRQn);
}

void TIM3_IRQHandler(void)
{
    if(TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF;
        g_tick_ms++;
    }
}

uint32_t GetTickMs(void){
    return g_tick_ms;
}

void Delay_ms(uint32_t ms){
    uint32_t start = GetTickMs();
    while((GetTickMs() - start) < ms);
}

void TIM4_Init_1us(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    TIM4->PSC = 72 - 1;     
    TIM4->ARR = 0xFFFF;
    TIM4->CNT = 0;
    TIM4->CR1 |= TIM_CR1_CEN;
}

void Delay_us(uint16_t us){
    TIM4->CNT = 0;
    while(TIM4->CNT < us);
}