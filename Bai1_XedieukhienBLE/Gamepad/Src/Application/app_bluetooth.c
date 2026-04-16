#include "app_bluetooth.h"
#include "mid_bluetooth.h"

void App_Bluetooth_Init(uint32_t baudrate)
{
    Mid_Bluetooth_Init(baudrate);
}

void App_Bluetooth_SendChar(char c)
{
    Mid_Bluetooth_SendChar(c);
}

void App_Bluetooth_SendString(char *str)
{
    Mid_Bluetooth_SendString(str);
}

uint8_t App_Bluetooth_Available(void)
{
    return Mid_Bluetooth_Available();
}

char App_Bluetooth_Read(void)
{
    return Mid_Bluetooth_Read();
}

void App_Bluetooth_SendNum(int32_t num)
{
    Mid_Bluetooth_SendNum(num);
}