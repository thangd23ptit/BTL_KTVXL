#ifndef __MID_MODE_H
#define __MID_MODE_H

#include "stm32f10x.h"
#include "ip_protocol.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    protocol_mode_t current_mode;
    uint8_t last_state;
}Mid_Mode_t;

void Mid_Mode_Init(Mid_Mode_t *mode, GPIO_TypeDef *port, uint16_t pin);
protocol_mode_t Mid_Mode_Update(Mid_Mode_t *mode);

#endif