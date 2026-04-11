#include "timer.h"

static volatile uint32_t g_tick_ms = 0;

// TIM3 tao ngat moi 1ms
void TIM3_Init_1ms(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3->PSC = 7200 - 1;   // 72MHz / 7200 = 10kHz
    TIM3->ARR = 10 - 1;     // 10kHz / 10 = 1kHz = 1ms
    TIM3->CNT = 0;

    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1  |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM3_IRQn);
}

// TIM3 interrupt moi 1ms
void TIM3_IRQHandler(void)
{
    if(TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF;
        g_tick_ms++;
    }
}

// lay tick hien tai
uint32_t GetTickMs(void)
{
    return g_tick_ms;
}

// delay block ms
void Delay_ms(uint16_t ms)
{
    uint32_t start = GetTickMs();
    while((GetTickMs() - start) < ms);
}

// delay us cho 72MHz
void Delay_us(uint16_t us)
{
    while(us--)
    {
        for(volatile uint8_t i = 0; i < 18; i++)
        {
            __NOP();
        }
    }
}