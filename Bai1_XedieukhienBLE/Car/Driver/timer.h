#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"

void TIM3_Init_1ms(void);
void TIM4_Init_1us(void);
uint32_t GetTickMs(void);
void Delay_ms(uint32_t ms);
void Delay_us(uint16_t us);
#endif