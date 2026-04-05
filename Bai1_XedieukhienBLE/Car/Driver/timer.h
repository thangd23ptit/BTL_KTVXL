#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"
#include <stdint.h>

void TIM3_Init_1ms(void);
void Delay_ms(uint16_t ms);

#endif