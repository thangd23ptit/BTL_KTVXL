#ifndef _MID_PWM_H
#define _MID_PWM_H

#include "stm32f10x.h"
#include <stdint.h>

void Mid_PWM_Init(void);
void Mid_PWM_SetLeft(uint16_t duty);
void Mid_PWM_SetRight(uint16_t duty);

#endif