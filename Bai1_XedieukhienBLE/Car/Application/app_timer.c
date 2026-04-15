#include "app_timer.h"
#include "mid_timer.h"

void App_TIM3_Init_1ms(void)
{
    Mid_TIM3_Init_1ms();
}

uint32_t App_GetTickMs(void)
{
    return Mid_GetTickMs();
}

void App_Delay_ms(uint32_t ms)
{
    Mid_Delay_ms(ms);
}

void App_TIM4_Init_1us(void)
{
    Mid_TIM4_Init_1us();
}

void App_Delay_us(uint16_t us)
{
    Mid_Delay_us(us);
}