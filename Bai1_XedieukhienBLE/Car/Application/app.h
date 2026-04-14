#ifndef __APP_H
#define __APP_H

#include "stm32f10x.h"

typedef enum
{
    APP_MODE_AUTO = 0,
    APP_MODE_MANUAL
} app_mode_t;

void App_SetMode(app_mode_t mode);
void App_Run(void);

#endif