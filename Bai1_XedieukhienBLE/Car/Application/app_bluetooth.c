#include "app_bluetooth.h"
#include "mid_bluetooth.h"

void App_Bluetooth_Init(uint32_t baudrate)
{
    Mid_Bluetooth_Init(baudrate);
}

uint8_t App_Bluetooth_Available(void)
{
    return Mid_Bluetooth_Available();
}

char App_Bluetooth_ReadChar(void)
{
    return Mid_Bluetooth_ReadChar();
}

void App_Bluetooth_SendChar(char c)
{
    Mid_Bluetooth_SendChar(c);
}

void App_Bluetooth_SendString(const char *str)
{
    Mid_Bluetooth_SendString(str);
}