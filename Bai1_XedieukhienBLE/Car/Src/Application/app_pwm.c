#include "app_pwm.h"
#include "mid_pwm.h"

void App_PWM_Init(void)
{
    Mid_PWM_Init();
}

void App_PWM_SetLeft(uint16_t duty)
{
    Mid_PWM_SetLeft(duty);
}

void App_PWM_SetRight(uint16_t duty)
{
    Mid_PWM_SetRight(duty);
}