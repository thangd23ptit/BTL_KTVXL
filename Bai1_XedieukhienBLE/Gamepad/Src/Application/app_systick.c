#include "app_systick.h"
#include "mid_systick.h"

void App_SysTick_DelayUs(uint32_t us)
{
    Mid_SysTick_DelayUs(us);
}

void App_SysTick_DelayMs(uint32_t ms)
{
    Mid_SysTick_DelayMs(ms);
}