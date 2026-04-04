#ifndef SYSTICK_H
#define SYSTICK_H

#include "stm32f10x.h"
#include <stdint.h>

void SysTick_Init(void);
void SysTick_DelayMs(uint32_t ms);
uint32_t SysTick_GetTick(void);
void SysTick_Handler(void);
#endif

