#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f10x.h"

void SysTick_DelayUs(uint32_t us);
void SysTick_DelayMs(uint32_t ms);

#endif