#include "motor.h"
#include "gpio.h"
#include "pwm.h"

#define IN1_PORT GPIOB
#define IN2_PORT GPIOB
#define IN3_PORT GPIOB
#define IN4_PORT GPIOB

#define IN1_PIN 0
#define IN2_PIN 1
#define IN3_PIN 10
#define IN4_PIN 11

void Motor_Init(void)
{
    GPIO_Config_Output(IN1_PORT, IN1_PIN);
    GPIO_Config_Output(IN2_PORT, IN2_PIN);
    GPIO_Config_Output(IN3_PORT, IN3_PIN);
    GPIO_Config_Output(IN4_PORT, IN4_PIN);

    PWM_Init();
    Motor_Stop();
}

void Motor_Forward(uint16_t speed)
{
    GPIO_Write_Pin(IN1_PORT, IN1_PIN, 1);
    GPIO_Write_Pin(IN2_PORT, IN2_PIN, 0);
    GPIO_Write_Pin(IN3_PORT, IN3_PIN, 1);
    GPIO_Write_Pin(IN4_PORT, IN4_PIN, 0);

    PWM_SetLeft(speed);
    PWM_SetRight(speed);
}

void Motor_Backward(uint16_t speed)
{
    GPIO_Write_Pin(IN1_PORT, IN1_PIN, 0);
    GPIO_Write_Pin(IN2_PORT, IN2_PIN, 1);
    GPIO_Write_Pin(IN3_PORT, IN3_PIN, 0);
    GPIO_Write_Pin(IN4_PORT, IN4_PIN, 1);

    PWM_SetLeft(speed);
    PWM_SetRight(speed);
}

void Motor_Left(uint16_t speed)
{
    GPIO_Write_Pin(IN1_PORT, IN1_PIN, 0);
    GPIO_Write_Pin(IN2_PORT, IN2_PIN, 0);
    GPIO_Write_Pin(IN3_PORT, IN3_PIN, 1);
    GPIO_Write_Pin(IN4_PORT, IN4_PIN, 0);

    PWM_SetLeft(0);
    PWM_SetRight(speed);
}

void Motor_Right(uint16_t speed)
{
    GPIO_Write_Pin(IN1_PORT, IN1_PIN, 1);
    GPIO_Write_Pin(IN2_PORT, IN2_PIN, 0);
    GPIO_Write_Pin(IN3_PORT, IN3_PIN, 0);
    GPIO_Write_Pin(IN4_PORT, IN4_PIN, 0);

    PWM_SetLeft(speed);
    PWM_SetRight(0);
}

void Motor_Stop(void)
{
    GPIO_Write_Pin(IN1_PORT, IN1_PIN, 0);
    GPIO_Write_Pin(IN2_PORT, IN2_PIN, 0);
    GPIO_Write_Pin(IN3_PORT, IN3_PIN, 0);
    GPIO_Write_Pin(IN4_PORT, IN4_PIN, 0);

    PWM_SetLeft(0);
    PWM_SetRight(0);
}
void Motor_SetSpeed(uint16_t left, uint16_t right)
{
    GPIO_Write_Pin(IN1_PORT, IN1_PIN, 1);
    GPIO_Write_Pin(IN2_PORT, IN2_PIN, 0);
    GPIO_Write_Pin(IN3_PORT, IN3_PIN, 1);
    GPIO_Write_Pin(IN4_PORT, IN4_PIN, 0);

    PWM_SetLeft(left);
    PWM_SetRight(right);
}