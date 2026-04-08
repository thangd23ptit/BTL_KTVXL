#include "protocol.h"
#include "uart.h"

#define JOY_CENTER   2048
#define DEADZONE     300
#define MAX_ADC      4095

protocol_cmd_t Protocol_Encode(uint16_t x, uint16_t y)
{
    int16_t x_offset = x - JOY_CENTER;
    int16_t y_offset = y - JOY_CENTER;

    // uu tiên tr?c Y
    if(y_offset > DEADZONE)
    {
        return CMD_FORWARD;
    }
    else if(y_offset < -DEADZONE)
    {
        return CMD_BACKWARD;
    }
    else if(x_offset > DEADZONE)
    {
        return CMD_RIGHT;
    }
    else if(x_offset < -DEADZONE)
    {
        return CMD_LEFT;
    }

    return CMD_STOP;
}

void Protocol_Send(protocol_mode_t mode,
                   protocol_cmd_t cmd,
                   uint16_t speed)
{
    UART1_SendChar('$');
    UART1_SendChar((char)mode);
    UART1_SendChar(',');
    UART1_SendChar((char)cmd);
    UART1_SendChar(',');
    UART1_SendNumber(speed);
    UART1_SendChar('#');
}