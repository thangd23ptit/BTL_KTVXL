#ifndef __MOTOR_H
#define __MOTOR_H

#include <stdint.h>

void Motor_Init(void);
void Motor_Forward(uint16_t speed);
void Motor_Backward(uint16_t speed);
void Motor_Left(uint16_t speed);
void Motor_Right(uint16_t speed);
void Motor_Stop(void);
void Motor_SetSpeed(uint16_t left, uint16_t right);
#endif