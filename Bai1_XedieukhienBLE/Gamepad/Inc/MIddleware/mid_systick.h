#ifndef __MID_SYSTICK_H
#define __MID_SYSTICK_H

#include "stm32f10x.h"
#include <stdint.h>

void Mid_SysTick_DelayUs(uint32_t us);
void Mid_SysTick_DelayMs(uint32_t ms);

#endif