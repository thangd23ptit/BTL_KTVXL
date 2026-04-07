#include "joystick.h"
#include "adc.h"

void Joystick_Init(Joystick_t *joy,
                   uint8_t x_channel,
                   uint8_t y_channel)
{
    joy->x_channel = x_channel;
    joy->y_channel = y_channel;
    joy->center = 2048;
}

uint16_t Joystick_ReadX(Joystick_t *joy)
{
    ADC1_Init_Single(joy->x_channel);
    return ADC1_Read();
}

uint16_t Joystick_ReadY(Joystick_t *joy)
{
    ADC1_Init_Single(joy->y_channel);
    return ADC1_Read();
}

int16_t Joystick_GetXOffset(Joystick_t *joy)
{
    return (int16_t)Joystick_ReadX(joy) - joy->center;
}

int16_t Joystick_GetYOffset(Joystick_t *joy)
{
    return (int16_t)Joystick_ReadY(joy) - joy->center;
}