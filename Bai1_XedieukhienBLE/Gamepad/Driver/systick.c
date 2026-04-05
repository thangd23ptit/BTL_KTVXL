#include "systick.h"
#include "stm32f10x.h"

static volatile uint32_t g_tick = 0;

void SysTick_Handler(void)
{
    g_tick++;
}

void SysTick_Init(void)
{
    SysTick->LOAD = SystemCoreClock / 1000 - 1;
    SysTick->VAL  = 0;

    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk   |
                    SysTick_CTRL_ENABLE_Msk;
}

void SysTick_DelayMs(uint32_t ms)
{
    uint32_t start = g_tick;
    while((g_tick - start) < ms);
}

uint32_t SysTick_GetTick(void)
{
    return g_tick;
}