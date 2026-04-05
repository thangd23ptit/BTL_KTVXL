#include "bluetooth.h"
#include "uart.h"

void Bluetooth_Init(uint32_t baudrate)
{
    UART1_Init(baudrate);
}

void Bluetooth_SendChar(char c)
{
    UART1_SendChar(c);
}

void Bluetooth_SendString(const char *str)
{
    UART1_SendString(str);
}

void Bluetooth_SendBuffer(uint8_t *data, uint16_t len)
{
    UART1_SendBuffer(data, len);
}

uint8_t Bluetooth_Available(void)
{
    return UART1_Available();
}

char Bluetooth_ReadChar(void)
{
    return UART1_ReadChar();
}