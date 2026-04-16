#include "app_adc.h"
#include "mid_adc.h"

void App_ADC1_Init_Single(uint8_t channel)
{
    Mid_ADC1_Init_Single(channel);
}

uint16_t App_ADC1_Read(void)
{
    return Mid_ADC1_Read();
}

float App_ADC1_ReadVoltage(void)
{
    return Mid_ADC1_ReadVoltage();
}