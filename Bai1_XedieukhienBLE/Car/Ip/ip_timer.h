#ifndef _IP_TIMER_H
#define _IP_TIMER_H

#include "stm32f10x.h"

void Ip_TIM3_Init_1ms(void);
uint32_t Ip_GetTickMs(void);
void Ip_Delay_ms(uint32_t ms);

void Ip_TIM4_Init_1us(void);
void Ip_Delay_us(uint16_t us);

#endif