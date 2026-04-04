#include "mode.h"

uint8_t Mode_GetMode(uint8_t raw_mode)
{
    if (raw_mode > MODE_AUTO)
        return MODE_MANUAL_NORMAL;
    return raw_mode;
}

uint8_t Mode_IsAuto(uint8_t mode)
{
    return (mode == MODE_AUTO);
}

uint8_t Mode_LimitSpeed(uint8_t mode, uint8_t pwm)
{
    if (mode == MODE_PRECISION)
    {
        return (pwm * 40) / 100;
    }
    return pwm;
}

