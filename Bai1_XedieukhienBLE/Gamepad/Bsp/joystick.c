#include "joystick.h"
#include "adc.h"

#define JOY_FILTER_SAMPLES 4

static uint16_t Joystick_ReadAvg(uint8_t channel)
{
    uint32_t sum = 0;

    for(uint8_t i = 0; i < JOY_FILTER_SAMPLES; i++)
    {
        sum += ADC1_ReadChannel(channel);
    }

    return (uint16_t)(sum / JOY_FILTER_SAMPLES);
}

void Joystick_Init(void)
{
    ADC1_Init();
}

void Joystick_Read(uint16_t *x, uint16_t *y)
{
    *x = Joystick_ReadAvg(0);   // PA0
    *y = Joystick_ReadAvg(1);   // PA1
}

joystick_data_t Joystick_GetData(void)
{
    joystick_data_t joy;

    Joystick_Read(&joy.x, &joy.y);

    return joy;
}