#ifndef __IP_MODE_H
#define __IP_MODE_H

#include "stm32f10x.h"
#include "ip_protocol.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    protocol_mode_t current_mode;
    uint8_t last_state;
} Mode_t;

void Ip_Mode_Init(Mode_t *mode, GPIO_TypeDef *port, uint16_t pin);

protocol_mode_t Ip_Mode_Update(Mode_t *mode);

#endif