#include "mid_bluetooth.h"
#include "ip_bluetooth.h"

void Mid_Bluetooth_Init(uint32_t baudrate)
{
    Ip_Bluetooth_Init(baudrate);
}

uint8_t Mid_Bluetooth_Available(void)
{
    return Ip_Bluetooth_Available();
}

char Mid_Bluetooth_ReadChar(void)
{
    return Ip_Bluetooth_ReadChar();
}

void Mid_Bluetooth_SendChar(char c)
{
    Ip_Bluetooth_SendChar(c);
}

void Mid_Bluetooth_SendString(const char *str)
{
    Ip_Bluetooth_SendString(str);
}