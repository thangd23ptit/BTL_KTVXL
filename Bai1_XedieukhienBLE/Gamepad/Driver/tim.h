#ifndef TIM_H
#define TIM_H

#include "stm32f10x.h"
#include <stdint.h>

void TIM2_Init_1ms(void);
void Delay_ms(uint16_t ms);

#endif