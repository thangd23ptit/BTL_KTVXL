#include "ip_bluetooth.h"
#include "mid_bluetooth.h"

void Mid_Bluetooth_Init(uint32_t baudrate)
{
    Ip_Bluetooth_Init(baudrate);
}

void Mid_Bluetooth_SendChar(char c)
{
    Ip_Bluetooth_SendChar(c);
}

void Mid_Bluetooth_SendString(char *str)
{
    Ip_Bluetooth_SendString(str);
}

uint8_t Mid_Bluetooth_Available(void)
{
    return Ip_Bluetooth_Available();
}

char Mid_Bluetooth_Read(void)
{
    return Ip_Bluetooth_Read();
}

void Mid_Bluetooth_SendNum(int32_t num)
{
    Ip_Bluetooth_SendNum(num);
}