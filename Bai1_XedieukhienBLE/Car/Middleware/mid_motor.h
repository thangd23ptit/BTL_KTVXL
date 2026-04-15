#ifndef _MID_MOTOR_H
#define _MID_MOTOR_H

#include <stdint.h>

void Mid_Motor_Init(void);
void Mid_Motor_Forward(uint16_t speed);
void Mid_Motor_Backward(uint16_t speed);
void Mid_Motor_Left(uint16_t speed);
void Mid_Motor_Right(uint16_t speed);
void Mid_Motor_Stop(void);
void Mid_Motor_SetSpeed(uint16_t left, uint16_t right);

#endif