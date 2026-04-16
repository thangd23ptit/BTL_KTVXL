#include "ip_protocol.h"
#include "ip_bluetooth.h"

#define JOY_CENTER   2048
#define DEADZONE     300
#define MAX_ADC      4095

/**
 * @brief Ma hoa du lieu joystick thanh lenh dieu khien
 * @param x Gia tri ADC truc X
 * @param y Gia tri ADC truc Y
 * @retval Lenh dieu khien (CMD_STOP, CMD_FORWARD, ...)
 */
protocol_cmd_t Ip_Protocol_Encode(uint16_t x, uint16_t y)
{
    int16_t x_offset = x - JOY_CENTER;
    int16_t y_offset = y - JOY_CENTER;

    if (y_offset > DEADZONE)
    {
        return CMD_FORWARD;
    }
    else if (y_offset < -DEADZONE)
    {
        return CMD_BACKWARD;
    }
    else if (x_offset > DEADZONE)
    {
        return CMD_RIGHT;
    }
    else if (x_offset < -DEADZONE)
    {
        return CMD_LEFT;
    }

    return CMD_STOP;
}

/**
 * @brief Gui frame dieu khien qua Bluetooth
 * @param mode Che do hoat dong (MANUAL/AUTO)
 * @param cmd Lenh dieu khien
 * @param speed Toc do dong co
 * @retval None
 */
void Ip_Protocol_Send(protocol_mode_t mode, protocol_cmd_t cmd, uint16_t speed)
{
    Ip_Bluetooth_SendChar('$');
    Ip_Bluetooth_SendChar((char)mode);
    Ip_Bluetooth_SendChar(',');
    Ip_Bluetooth_SendChar((char)cmd);
    Ip_Bluetooth_SendChar(',');
    Ip_Bluetooth_SendNum(speed);
    Ip_Bluetooth_SendChar('#');
}