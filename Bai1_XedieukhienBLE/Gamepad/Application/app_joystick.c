#include "app_joystick.h"
#include "mid_joystick.h"

void App_Joystick_Init(App_Joystick_t *joy, uint8_t x_channel, uint8_t y_channel)
{
    Mid_Joystick_Init((Mid_Joystick_t *)joy, x_channel, y_channel);
}

uint16_t App_Joystick_ReadX(App_Joystick_t *joy)
{
    return Mid_Joystick_ReadX((Mid_Joystick_t *)joy);
}

uint16_t App_Joystick_ReadY(App_Joystick_t *joy)
{
    return Mid_Joystick_ReadY((Mid_Joystick_t *)joy);
}

int16_t App_Joystick_GetXOffset(App_Joystick_t *joy)
{
    return Mid_Joystick_GetXOffset((Mid_Joystick_t *)joy);
}

int16_t App_Joystick_GetYOffset(App_Joystick_t *joy)
{
    return Mid_Joystick_GetYOffset((Mid_Joystick_t *)joy);
}