#ifndef _APP_MOTOR_H
#define _APP_MOTOR_H

#include <stdint.h>

void App_Motor_Init(void);
void App_Motor_Forward(uint16_t speed);
void App_Motor_Backward(uint16_t speed);
void App_Motor_Left(uint16_t speed);
void App_Motor_Right(uint16_t speed);
void App_Motor_Stop(void);
void App_Motor_SetSpeed(uint16_t left, uint16_t right);

#endif