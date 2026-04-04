#include "motor.h"

void Config_Motor(void){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_ConfigOutput(MOTOR_PORT , R_IN1);
		GPIO_ConfigOutput(MOTOR_PORT , R_IN2);
		GPIO_ConfigOutput(MOTOR_PORT , L_IN1);
		GPIO_ConfigOutput(MOTOR_PORT , L_IN2);
}

void Motor_Init(void)
{
		Config_Motor();
    PWM_Init();
    Motor_Stop();
}

void Motor_Stop(void)
{		GPIO_WritePin(GPIOB ,R_IN1,0);
		GPIO_WritePin(GPIOB ,R_IN2,0);
		GPIO_WritePin(GPIOB ,L_IN1,0);
		GPIO_WritePin(GPIOB ,L_IN2,0);
	
    PWM_SetDuty_Left(0);
    PWM_SetDuty_Right(0);
}

void Motor_Forward(uint16_t speed)
{
    GPIO_WritePin(GPIOB ,R_IN1,1);
		GPIO_WritePin(GPIOB ,R_IN2,0);
		GPIO_WritePin(GPIOB ,L_IN1,1);
		GPIO_WritePin(GPIOB ,L_IN2,0);

    PWM_SetDuty_Left(speed);
    PWM_SetDuty_Right(speed);
}

void Motor_Backward(uint16_t speed)
{
    GPIO_WritePin(GPIOB ,R_IN1,0);
		GPIO_WritePin(GPIOB ,R_IN2,1);
		GPIO_WritePin(GPIOB ,L_IN1,0);
		GPIO_WritePin(GPIOB ,L_IN2,1);

    PWM_SetDuty_Left(speed);
    PWM_SetDuty_Right(speed);
}

void Motor_Left(uint16_t speed)
{
    GPIO_WritePin(GPIOB ,R_IN1,1);
		GPIO_WritePin(GPIOB ,R_IN2,0);
		GPIO_WritePin(GPIOB ,L_IN1,0);
		GPIO_WritePin(GPIOB ,L_IN2,0);

    PWM_SetDuty_Left(0);
    PWM_SetDuty_Right(speed);
}

void Motor_Right(uint16_t speed)
{
    GPIO_WritePin(GPIOB ,R_IN1,0);
		GPIO_WritePin(GPIOB ,R_IN2,0);
		GPIO_WritePin(GPIOB ,L_IN1,1);
		GPIO_WritePin(GPIOB ,L_IN2,0);

    PWM_SetDuty_Left(speed);
    PWM_SetDuty_Right(0);
}

void Motor_SetSpeed(int left, int right)
{
    GPIO_SetBits(GPIOB, L_IN1);
    GPIO_ResetBits(GPIOB, L_IN2);
    GPIO_SetBits(GPIOB, R_IN1);
    GPIO_ResetBits(GPIOB, R_IN2);
	
    PWM_SetDuty_Left(left);
    PWM_SetDuty_Right(right);
}