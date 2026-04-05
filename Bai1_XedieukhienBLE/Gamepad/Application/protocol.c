#include "protocol.h"
#include "bluetooth.h"

#define JOY_HIGH_THRESHOLD   3000
#define JOY_LOW_THRESHOLD    1000
#define JOY_CENTER_MIN       1800
#define JOY_CENTER_MAX       2200

protocol_cmd_t Protocol_Encode(uint16_t x, uint16_t y)
{
    /* joystick ? gi?a */
    if((x > JOY_CENTER_MIN && x < JOY_CENTER_MAX) &&
       (y > JOY_CENTER_MIN && y < JOY_CENTER_MAX))
    {
        return CMD_STOP;
    }

    /* uu tiên ti?n lùi */
    if(y > JOY_HIGH_THRESHOLD)
    {
        return CMD_FORWARD;
    }

    if(y < JOY_LOW_THRESHOLD)
    {
        return CMD_BACKWARD;
    }

    if(x > JOY_HIGH_THRESHOLD)
    {
        return CMD_RIGHT;
    }

    if(x < JOY_LOW_THRESHOLD)
    {
        return CMD_LEFT;
    }

    return CMD_STOP;
}
void Protocol_Send(protocol_mode_t mode,
                   protocol_cmd_t cmd,
                   uint16_t speed)
{
    char buffer[20];

    sprintf(buffer, "$%c,%c,%d#",
            (char)mode,
            (char)cmd,
            speed);

    Bluetooth_SendString(buffer);
}