#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "stm32f10x.h"

typedef struct
{
    uint8_t x_channel;
    uint8_t y_channel;
    uint16_t center;
} Joystick_t;

void Joystick_Init(Joystick_t *joy, uint8_t x_channel, uint8_t y_channel);

uint16_t Joystick_ReadX(Joystick_t *joy);
uint16_t Joystick_ReadY(Joystick_t *joy);
int16_t Joystick_GetXOffset(Joystick_t *joy);
int16_t Joystick_GetYOffset(Joystick_t *joy);

#endif