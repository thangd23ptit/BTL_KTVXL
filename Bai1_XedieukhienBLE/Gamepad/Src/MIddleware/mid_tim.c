#include "ip_tim.h"
#include "mid_tim.h"

void Mid_TIM2_Init_1ms(void)
{
    Ip_TIM2_Init_1ms();
}

void Mid_Delay_ms(uint16_t ms)
{
    Ip_Delay_ms(ms);
}