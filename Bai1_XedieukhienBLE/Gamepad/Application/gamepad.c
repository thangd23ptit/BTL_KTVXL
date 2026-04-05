#include "gamepad.h"
#include "joystick.h"
#include "mode.h"
#include "protocol.h"
#include "bluetooth.h"

static protocol_cmd_t g_last_cmd = CMD_STOP;
static protocol_mode_t g_last_mode = MODE_MANUAL;

void Gamepad_Init(void)
{
    Bluetooth_Init(9600);
    Joystick_Init();
    Mode_Init();
}

void Gamepad_Run(void)
{
    joystick_data_t joy;
    protocol_cmd_t cmd;
    protocol_mode_t mode;
    uint16_t speed;

    joy = Joystick_GetData();
    mode = Mode_Get();
    cmd  = Protocol_Encode(joy.x, joy.y);

    speed = joy.y / 4;   // 0..1023

    Protocol_Send(mode, cmd, speed);
}

