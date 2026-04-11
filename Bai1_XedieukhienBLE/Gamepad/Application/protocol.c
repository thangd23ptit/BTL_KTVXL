#include "protocol.h"
#include "bluetooth.h"

#define JOY_CENTER   2048
#define DEADZONE     300
#define MAX_ADC      4095

protocol_cmd_t Protocol_Encode(uint16_t x, uint16_t y){
    int16_t x_offset = x - JOY_CENTER;
    int16_t y_offset = y - JOY_CENTER;
    if(y_offset > DEADZONE){
        return CMD_BACKWARD;
    }
    else if(y_offset < -DEADZONE){
        return CMD_FORWARD;
    }
    else if(x_offset > DEADZONE){
        return CMD_RIGHT;
    }
    else if(x_offset < -DEADZONE){
        return CMD_LEFT;
    }
    return CMD_STOP;
}

void Protocol_Send(protocol_mode_t mode, protocol_cmd_t cmd, uint16_t speed)
{
    Bluetooth_SendChar('$');
    Bluetooth_SendChar((char)mode);
    Bluetooth_SendChar(',');
    Bluetooth_SendChar((char)cmd);
    Bluetooth_SendChar(',');
    Bluetooth_SendNum(speed);
    Bluetooth_SendChar('#');
}