#ifndef __MOTOR_H
#define __MOTOR_H
//Include
#include <stdint.h>
#include "gpio.h"
#include "pwm.h"

void Motor_Init(void);

void Motor_Stop(void);
void Motor_Forward(uint16_t speed);
void Motor_Backward(uint16_t speed);
void Motor_Left(uint16_t speed);
void Motor_Right(uint16_t speed);
void Motor_SetSpeed(int left, int right);
#endif