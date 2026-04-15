#ifndef _APP_SYSTICK_H
#define _APP_SYSTICK_H

#include "stm32f10x.h"
#include <stdint.h>

void App_SysTick_DelayUs(uint32_t us);
void App_SysTick_DelayMs(uint32_t ms);

#endif