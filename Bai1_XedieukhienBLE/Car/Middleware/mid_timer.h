#ifndef _MID_TIMER_H
#define _MID_TIMER_H

#include "stm32f10x.h"
#include <stdint.h>

void Mid_TIM3_Init_1ms(void);
uint32_t Mid_GetTickMs(void);
void Mid_Delay_ms(uint32_t ms);

void Mid_TIM4_Init_1us(void);
void Mid_Delay_us(uint16_t us);

#endif