#ifndef __PWM_H__
#define __PWM_H__

#include "stm32f10x.h"

void PWM_Init(void);
void PWM_SetDuty_Left(uint16_t duty);
void PWM_SetDuty_Right(uint16_t duty);

#endif