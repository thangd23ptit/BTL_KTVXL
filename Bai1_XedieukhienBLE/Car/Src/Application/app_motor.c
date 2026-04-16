#include "app_motor.h"
#include "mid_motor.h"

void App_Motor_Init(void)
{
    Mid_Motor_Init();
}

void App_Motor_Forward(uint16_t speed)
{
    Mid_Motor_Forward(speed);
}

void App_Motor_Backward(uint16_t speed)
{
    Mid_Motor_Backward(speed);
}

void App_Motor_Left(uint16_t speed)
{
    Mid_Motor_Left(speed);
}

void App_Motor_Right(uint16_t speed)
{
    Mid_Motor_Right(speed);
}

void App_Motor_Stop(void)
{
    Mid_Motor_Stop();
}

void App_Motor_SetSpeed(uint16_t left, uint16_t right)
{
    Mid_Motor_SetSpeed(left, right);
}