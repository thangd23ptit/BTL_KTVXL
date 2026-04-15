#include "ip_joystick.h"
#include "mid_joystick.h"

void Mid_Joystick_Init(Mid_Joystick_t *joys, uint8_t x_channel, uint8_t y_channel)
{
    Ip_Joystick_Init(joys, x_channel, y_channel);
}

uint16_t Mid_Joystick_ReadX(Mid_Joystick_t *joys)
{
    return Ip_Joystick_ReadX(joys);
}

uint16_t Mid_Joystick_ReadY(Mid_Joystick_t *joys)
{
    return Ip_Joystick_ReadY(joys);
}

int16_t Mid_Joystick_GetXOffset(Mid_Joystick_t *joys)
{
    return Ip_Joystick_GetXOffset(joys);
}

int16_t Mid_Joystick_GetYOffset(Mid_Joystick_t *joys)
{
    return Ip_Joystick_GetYOffset(joys);
}