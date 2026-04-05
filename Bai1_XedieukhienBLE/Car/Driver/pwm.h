#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"
#include <stdint.h>

void PWM_Init(void);
void PWM_SetLeft(uint16_t duty);
void PWM_SetRight(uint16_t duty);

#endif