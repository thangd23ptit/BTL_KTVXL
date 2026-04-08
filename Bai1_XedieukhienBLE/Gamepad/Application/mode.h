#ifndef __MODE_H
#define __MODE_H

#include "stm32f10x.h"
#include "protocol.h"

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    protocol_mode_t current_mode;
    uint8_t last_state;
} Mode_t;

void Mode_Init(Mode_t *mode, GPIO_TypeDef *port, uint16_t pin);

protocol_mode_t Mode_Update(Mode_t *mode);

#endif