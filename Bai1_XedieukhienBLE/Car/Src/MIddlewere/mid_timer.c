#include "mid_timer.h"
#include "ip_timer.h"

void Mid_TIM3_Init_1ms(void)
{
    Ip_TIM3_Init_1ms();
}

uint32_t Mid_GetTickMs(void)
{
    return Ip_GetTickMs();
}

void Mid_Delay_ms(uint32_t ms)
{
    Ip_Delay_ms(ms);
}

void Mid_TIM4_Init_1us(void)
{
    Ip_TIM4_Init_1us();
}

void Mid_Delay_us(uint16_t us)
{
    Ip_Delay_us(us);
}