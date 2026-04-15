#include "app_tim.h"
#include "mid_tim.h"

void App_TIM2_Init_1ms(void)
{
    Mid_TIM2_Init_1ms();
}

void App_Delay_ms(uint16_t ms)
{
    Mid_Delay_ms(ms);
}