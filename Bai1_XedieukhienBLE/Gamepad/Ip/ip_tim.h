#ifndef _IP_TIM_H
#define _IP_TIM_H

#include "stm32f10x.h"
#include <stdint.h>

void Ip_TIM2_Init_1ms(void);
void Ip_Delay_ms(uint16_t ms);

#endif