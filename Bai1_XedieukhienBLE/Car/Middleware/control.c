#include "control.h"
#include "bluetooth.h"
#include "motor.h"
#include <stdlib.h>

static control_data_t g_control = {'M', 'S', 700};

void Control_Init(void)
{
    Bluetooth_Init(9600);
}

void Control_Run(void)
{
    static char frame[20];
    static uint8_t idx = 0;

    while(Bluetooth_Available())
    {
        char c = Bluetooth_ReadChar();

        if(c == '$') idx = 0;

        if(idx < sizeof(frame) - 1)
            frame[idx++] = c;

        if(c == '#')
        {
            frame[idx] = '\0';
            idx = 0;

            g_control.mode  = frame[1];
            g_control.cmd   = frame[3];
            g_control.speed = atoi(&frame[5]);
        }
    }
}

control_data_t Control_GetData(void)
{
    return g_control;
}

void Control_Execute(control_data_t data)
{
    switch(data.cmd)
    {
        case 'F': Motor_Forward(data.speed); break;
        case 'B': Motor_Backward(data.speed); break;
        case 'L': Motor_Left(data.speed); break;
        case 'R': Motor_Right(data.speed); break;
        default : Motor_Stop(); break;
    }
}