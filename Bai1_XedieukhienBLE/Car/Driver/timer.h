#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"

void TIM3_Init_1ms(void);
void Delay_ms(uint16_t ms);
void Delay_us(uint16_t us);
uint32_t GetTickMs(void);

#endif