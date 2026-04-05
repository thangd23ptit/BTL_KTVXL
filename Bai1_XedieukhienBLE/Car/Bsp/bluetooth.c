#include "bluetooth.h"
#include "uart.h"

void Bluetooth_Init(uint32_t baudrate)
{
    UART1_Init(baudrate);
}

uint8_t Bluetooth_Available(void)
{
    return UART1_Available();
}

char Bluetooth_ReadChar(void)
{
    return UART1_ReadChar();
}

void Bluetooth_SendChar(char c)
{
    UART1_SendChar(c);
}

void Bluetooth_SendString(const char *str)
{
    while(*str)
    {
        UART1_SendChar(*str++);
    }
}