#ifndef __MID_JOYSTICK_H
#define __MID_JOYSTICK_H

#include "stm32f10x.h"

typedef struct
{
    uint8_t x_channel;
    uint8_t y_channel;
    uint16_t center;
} Mid_Joystick_t;

void Mid_Joystick_Init(Mid_Joystick_t *joys, uint8_t x_channel, uint8_t y_channel);

uint16_t Mid_Joystick_ReadX(Mid_Joystick_t *joys);
uint16_t Mid_Joystick_ReadY(Mid_Joystick_t *joys);
int16_t Mid_Joystick_GetXOffset(Mid_Joystick_t *joys);
int16_t Mid_Joystick_GetYOffset(Mid_Joystick_t *joys);

#endif