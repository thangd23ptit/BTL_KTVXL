#include "motor.h"
#include "control.h"

int main(void)
{
    Motor_Init();
    Control_Init();
    Motor_Stop();

    while(1)
    {
        Control_Run();
        Control_Execute(Control_GetData());
    }
}