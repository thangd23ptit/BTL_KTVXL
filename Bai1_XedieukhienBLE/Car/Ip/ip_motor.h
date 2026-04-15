#ifndef _IP_MOTOR_H
#define _IP_MOTOR_H

#include <stdint.h>

void Ip_Motor_Init(void);
void Ip_Motor_Forward(uint16_t speed);
void Ip_Motor_Backward(uint16_t speed);
void Ip_Motor_Left(uint16_t speed);
void Ip_Motor_Right(uint16_t speed);
void Ip_Motor_Stop(void);
void Ip_Motor_SetSpeed(uint16_t left, uint16_t right);

#endif