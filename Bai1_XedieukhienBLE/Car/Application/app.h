#ifndef __APP_H
#define __APP_H

#include "stm32f10x.h"

typedef enum
{
    APP_MODE_MANUAL = 'M',
    APP_MODE_AUTO   = 'A'
} app_mode_t;

void App_Init(void);
void App_Run(void);

#endif