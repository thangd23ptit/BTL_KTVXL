#ifndef __APP_JOYSTICK_H
#define __APP_JOYSTICK_H

#include "stm32f10x.h"

typedef struct
{
    uint8_t x_channel;
    uint8_t y_channel;
    uint16_t center;
} App_Joystick_t;

void App_Joystick_Init(App_Joystick_t *joy, uint8_t x_channel, uint8_t y_channel);

uint16_t App_Joystick_ReadX(App_Joystick_t *joy);
uint16_t App_Joystick_ReadY(App_Joystick_t *joy);
int16_t App_Joystick_GetXOffset(App_Joystick_t *joy);
int16_t App_Joystick_GetYOffset(App_Joystick_t *joy);

#endif