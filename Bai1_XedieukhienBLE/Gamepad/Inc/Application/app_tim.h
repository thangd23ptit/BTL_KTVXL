#ifndef _APP_TIM_H
#define _APP_TIM_H

#include "stm32f10x.h"
#include <stdint.h>

void App_TIM2_Init_1ms(void);
void App_Delay_ms(uint16_t ms);

#endif