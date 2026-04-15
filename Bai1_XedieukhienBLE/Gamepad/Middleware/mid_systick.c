#include "ip_systick.h"
#include "mid_systick.h"

void Mid_SysTick_DelayUs(uint32_t us)
{
    Ip_SysTick_DelayUs(us);
}

void Mid_SysTick_DelayMs(uint32_t ms)
{
    Ip_SysTick_DelayMs(ms);
}