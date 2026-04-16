#ifndef __IP_SYSTICK_H
#define __IP_SYSTICK_H

#include "stm32f10x.h"

void Ip_SysTick_DelayUs(uint32_t us);
void Ip_SysTick_DelayMs(uint32_t ms);

#endif