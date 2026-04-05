#include "mode.h"
#include "gpio.h"

#define MODE_MAZE_PIN   3

void Mode_Init(void)
{
    GPIO_Config_Input_PU(GPIOA, MODE_MAZE_PIN);
}

protocol_mode_t Mode_Get(void)
{
    if(GPIO_Read(GPIOA, MODE_MAZE_PIN) == 0)
    {
        return MODE_MAZE;
    }

    return MODE_MANUAL;
}

