#ifndef _MID_TIM_H
#define _MID_TIM_H

#include "stm32f10x.h"
#include <stdint.h>

void Mid_TIM2_Init_1ms(void);
void Mid_Delay_ms(uint16_t ms);

#endif