#ifndef _APP_TIMER_H
#define _APP_TIMER_H

#include "stm32f10x.h"
#include <stdint.h>

void App_TIM3_Init_1ms(void);
uint32_t App_GetTickMs(void);
void App_Delay_ms(uint32_t ms);
void App_TIM4_Init_1us(void);
void App_Delay_us(uint16_t us);

#endif