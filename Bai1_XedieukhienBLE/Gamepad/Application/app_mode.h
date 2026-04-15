#ifndef __APP_MODE_H
#define __APP_MODE_H

#include "stm32f10x.h"
#include "app_protocol.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    app_protocol_mode_t current_mode;
    uint8_t last_state;
} App_Mode_t;

void App_Mode_Init(App_Mode_t *mode, GPIO_TypeDef *port, uint16_t pin);

app_protocol_mode_t App_Mode_Update(App_Mode_t *mode);

#endif