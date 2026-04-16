#ifndef _APP_PWM_H
#define _APP_PWM_H

#include "stm32f10x.h"
#include <stdint.h>

void App_PWM_Init(void);
void App_PWM_SetLeft(uint16_t duty);
void App_PWM_SetRight(uint16_t duty);

#endif