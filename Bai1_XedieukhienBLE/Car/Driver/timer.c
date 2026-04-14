#include "timer.h"

static volatile uint32_t g_tick_ms = 0;

/* ================= TIM3 1ms ================= */
void TIM3_Init_1ms(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // 72MHz / 7200 = 10kHz
    TIM3->PSC = 7200 - 1;

    // 10kHz / 10 = 1kHz ? 1ms
    TIM3->ARR = 10 - 1;

    TIM3->CNT = 0;

    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1  |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM3_IRQn);
}

/* ================= INTERRUPT ================= */
void TIM3_IRQHandler(void)
{
    if(TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF;
        g_tick_ms++;
    }
}

/* ================= GET TICK ================= */
uint32_t GetTickMs(void)
{
    return g_tick_ms;
}

/* ================= DELAY ================= */
void Delay_ms(uint32_t ms)
{
    uint32_t start = GetTickMs();
    while((GetTickMs() - start) < ms);
}

void TIM4_Init_1us(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    TIM4->PSC = 72 - 1;     // 72MHz -> 1MHz
    TIM4->ARR = 0xFFFF;
    TIM4->CNT = 0;
    TIM4->CR1 |= TIM_CR1_CEN;
}

void Delay_us(uint16_t us)
{
    TIM4->CNT = 0;
    while(TIM4->CNT < us);
}