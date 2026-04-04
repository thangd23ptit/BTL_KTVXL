#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"
//Delay

void Timer_Init(void);

void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);

uint32_t Micros(void);
uint32_t Millis(void);

#endif	