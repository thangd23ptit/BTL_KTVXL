#include "gamepad.h"
#include "joystick.h"
#include "bluetooth.h"

static Joystick_Data_t g_joy;
static uint8_t g_mode;

void Gamepad_Init(void)
{
    Joystick_Init();
    Bluetooth_Init();
}

void Gamepad_Update(void)
{
    Joystick_Read(&g_joy);
    g_mode = Mode_Read();

    // Auto mode g?i frame trung tâm c? d?nh
    if (g_mode == 2)
    {
        Bluetooth_SendAuto();
    }
    else
    {
        Bluetooth_SendPacket(g_joy.x, g_joy.y, g_mode);
    }
}

