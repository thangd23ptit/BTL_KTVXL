#include "ip_motor.h"
#include "ip_gpio.h"
#include "ip_pwm.h"

#define IN1_PORT GPIOB
#define IN2_PORT GPIOB
#define IN3_PORT GPIOB
#define IN4_PORT GPIOB

#define IN1_PIN 0
#define IN2_PIN 1
#define IN3_PIN 10
#define IN4_PIN 11

/**
 * @brief Khoi tao motor (GPIO output + PWM)
 * @param None
 * @retval None
 */
void Ip_Motor_Init(void){
    Ip_GPIO_Config_Output(IN1_PORT, IN1_PIN);
    Ip_GPIO_Config_Output(IN2_PORT, IN2_PIN);
    Ip_GPIO_Config_Output(IN3_PORT, IN3_PIN);
    Ip_GPIO_Config_Output(IN4_PORT, IN4_PIN);

    Ip_PWM_Init();

    Ip_Motor_Stop();
}

/**
 * @brief Dieu khien motor di thang
 * @param speed Toc do (0-1000)
 * @retval None
 */
void Ip_Motor_Forward(uint16_t speed){
    Ip_GPIO_Write_Pin(IN1_PORT, IN1_PIN, 1);
    Ip_GPIO_Write_Pin(IN2_PORT, IN2_PIN, 0);
    Ip_GPIO_Write_Pin(IN3_PORT, IN3_PIN, 1);
    Ip_GPIO_Write_Pin(IN4_PORT, IN4_PIN, 0);

    Ip_PWM_SetLeft(speed);
    Ip_PWM_SetRight(speed - 20);
}

/**
 * @brief Dieu khien motor di lui
 * @param speed Toc do (0-1000)
 * @retval None
 */
void Ip_Motor_Backward(uint16_t speed){
    Ip_GPIO_Write_Pin(IN1_PORT, IN1_PIN, 0);
    Ip_GPIO_Write_Pin(IN2_PORT, IN2_PIN, 1);
    Ip_GPIO_Write_Pin(IN3_PORT, IN3_PIN, 0);
    Ip_GPIO_Write_Pin(IN4_PORT, IN4_PIN, 1);

    Ip_PWM_SetLeft(speed);
    Ip_PWM_SetRight(speed - 20);
}

/**
 * @brief Re trai
 * @param speed Toc do
 * @retval None
 */
void Ip_Motor_Left(uint16_t speed){
    Ip_GPIO_Write_Pin(IN1_PORT, IN1_PIN, 0);
    Ip_GPIO_Write_Pin(IN2_PORT, IN2_PIN, 1);
    Ip_GPIO_Write_Pin(IN3_PORT, IN3_PIN, 0);
    Ip_GPIO_Write_Pin(IN4_PORT, IN4_PIN, 1);

    Ip_PWM_SetLeft(speed / 2);
    Ip_PWM_SetRight(speed - 20);
}

/**
 * @brief Re phai
 * @param speed Toc do
 * @retval None
 */
void Ip_Motor_Right(uint16_t speed){
    Ip_GPIO_Write_Pin(IN1_PORT, IN1_PIN, 0);
    Ip_GPIO_Write_Pin(IN2_PORT, IN2_PIN, 1);
    Ip_GPIO_Write_Pin(IN3_PORT, IN3_PIN, 0);
    Ip_GPIO_Write_Pin(IN4_PORT, IN4_PIN, 1);

    Ip_PWM_SetLeft(speed);
    Ip_PWM_SetRight(speed / 2 - 20);
}

/**
 * @brief Dung motor
 * @param None
 * @retval None
 */
void Ip_Motor_Stop(void){
    Ip_GPIO_Write_Pin(IN1_PORT, IN1_PIN, 0);
    Ip_GPIO_Write_Pin(IN2_PORT, IN2_PIN, 0);
    Ip_GPIO_Write_Pin(IN3_PORT, IN3_PIN, 0);
    Ip_GPIO_Write_Pin(IN4_PORT, IN4_PIN, 0);

    Ip_PWM_SetLeft(0);
    Ip_PWM_SetRight(0);
}

/**
 * @brief Set toc do rieng cho 2 banh
 * @param left Toc do ben trai
 * @param right Toc do ben phai
 * @retval None
 */
void Ip_Motor_SetSpeed(uint16_t left, uint16_t right){
    Ip_GPIO_Write_Pin(IN1_PORT, IN1_PIN, 0);
    Ip_GPIO_Write_Pin(IN2_PORT, IN2_PIN, 1);
    Ip_GPIO_Write_Pin(IN3_PORT, IN3_PIN, 0);
    Ip_GPIO_Write_Pin(IN4_PORT, IN4_PIN, 1);

    Ip_PWM_SetLeft(left);
    Ip_PWM_SetRight(right - 20);
}