#ifndef _IP_PWM_H
#define _IP_PWM_H

#include "stm32f10x.h"
#include <stdint.h>

void Ip_PWM_Init(void);
void Ip_PWM_SetLeft(uint16_t duty);
void Ip_PWM_SetRight(uint16_t duty);

#endif