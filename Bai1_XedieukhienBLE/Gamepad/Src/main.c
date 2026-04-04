#include "main.h"

void System_Init(void)
{
    SysTick_Init();
    Gamepad_Init();
}

int main(void)
{
    System_Init();

    while (1)
    {
        Gamepad_Update();
        SysTick_DelayMs(20);
    }
}
