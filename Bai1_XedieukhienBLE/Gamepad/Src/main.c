#include "main.h"

int main(void)
{
    /* init system clock 72MHz */
    SystemInit();

    /* init delay tick */
    SysTick_Init();

    /* init gamepad modules */
    Gamepad_Init();

    while(1)
    {
        Gamepad_Run();

        /* g?i packet m?i 50ms */
        SysTick_DelayMs(50);
    }
}