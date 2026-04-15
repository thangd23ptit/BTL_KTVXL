#ifndef __IP_JOYSTICK_H
#define __IP_JOYSTICK_H

#include "stm32f10x.h"

typedef struct
{
    uint8_t x_channel;
    uint8_t y_channel;
    uint16_t center;
} Joystick_t;

void Ip_Joystick_Init(Joystick_t *joy, uint8_t x_channel, uint8_t y_channel);

uint16_t Ip_Joystick_ReadX(Joystick_t *joy);
uint16_t Ip_Joystick_ReadY(Joystick_t *joy);
int16_t Ip_Joystick_GetXOffset(Joystick_t *joy);
int16_t Ip_Joystick_GetYOffset(Joystick_t *joy);

#endif