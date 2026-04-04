#include "bluetooth.h"
#include "uart.h"

void Bluetooth_Init(void)
{
    UART_Init();
}

uint8_t Bluetooth_Available(void)
{
    return UART_Available();
}

char Bluetooth_Read(void)
{
    return UART_Read();
}

void Bluetooth_Send(char *str)
{
    UART_SendString(str);
}