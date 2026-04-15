#include "mid_motor.h"
#include "ip_motor.h"

void Mid_Motor_Init(void)
{
    Ip_Motor_Init();
}

void Mid_Motor_Forward(uint16_t speed)
{
    Ip_Motor_Forward(speed);
}

void Mid_Motor_Backward(uint16_t speed)
{
    Ip_Motor_Backward(speed);
}

void Mid_Motor_Left(uint16_t speed)
{
    Ip_Motor_Left(speed);
}

void Mid_Motor_Right(uint16_t speed)
{
    Ip_Motor_Right(speed);
}

void Mid_Motor_Stop(void)
{
    Ip_Motor_Stop();
}

void Mid_Motor_SetSpeed(uint16_t left, uint16_t right)
{
    Ip_Motor_SetSpeed(left, right);
}