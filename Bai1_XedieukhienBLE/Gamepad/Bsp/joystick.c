#include "joystick.h"
#include "adc.h"
#include "gpio.h"

void Joystick_Init(void)
{
    ADC1_Init();

    // 2 chân d?c công t?c 3 mode
    GPIO_Config_Input_PU(GPIOB, 10);
    GPIO_Config_Input_PU(GPIOB, 11);
}

void Joystick_Read(Joystick_Data_t *joy)
{
    Joystick_ADC_Read(&joy->x, &joy->y);
}

uint8_t Mode_Read(void)
{
    uint8_t sw1 = GPIO_Read(GPIOB, 10);
    uint8_t sw2 = GPIO_Read(GPIOB, 11);

    // Công t?c ON-OFF-ON
    if (sw1 == 0) return 0;      // Manual Normal
    if (sw2 == 0) return 2;      // Auto
    return 1;                    // Precision (gi?a)
}

