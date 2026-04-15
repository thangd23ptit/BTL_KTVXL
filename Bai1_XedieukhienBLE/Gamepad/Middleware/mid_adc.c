#include "ip_adc.h"
#include "mid_adc.h"

void Mid_ADC1_Init_Single(uint8_t channel)
{
    Ip_ADC1_Init_Single(channel);
}

uint16_t Mid_ADC1_Read(void)
{
    return Ip_ADC1_Read();
}

float Mid_ADC1_ReadVoltage(void)
{
    return Ip_ADC1_ReadVoltage();
}