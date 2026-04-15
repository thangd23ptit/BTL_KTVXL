#include "main.h"

App_Gamepad_t gamepad;

int main(void)
{
    App_UART1_Init(9600);
    App_SysTick_DelayMs(1);

    App_Gamepad_Init(&gamepad, 0, 1, GPIOB, (1 << 0));

    while (1)
    {
        App_Gamepad_Update(&gamepad);
        App_SysTick_DelayMs(100);
    }
}