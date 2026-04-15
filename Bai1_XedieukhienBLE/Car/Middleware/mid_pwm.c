#include "mid_pwm.h"
#include "ip_pwm.h"

void Mid_PWM_Init(void)
{
    Ip_PWM_Init();
}

void Mid_PWM_SetLeft(uint16_t duty)
{
    Ip_PWM_SetLeft(duty);
}

void Mid_PWM_SetRight(uint16_t duty)
{
    Ip_PWM_SetRight(duty);
}