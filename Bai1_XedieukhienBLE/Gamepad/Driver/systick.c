#include "systick.h"

void SysTick_DelayUs(uint32_t us)
{
    SysTick->LOAD = 72 * us - 1;   // 72MHz => 1us = 72 tick
    SysTick->VAL  = 0;
    SysTick->CTRL = (1 << 2) | (1 << 0); // CLKSOURCE = AHB, ENABLE

    while((SysTick->CTRL & (1 << 16)) == 0);

    SysTick->CTRL = 0;
}

void SysTick_DelayMs(uint32_t ms)
{
    while(ms--)
    {
        SysTick_DelayUs(1000);
    }
}