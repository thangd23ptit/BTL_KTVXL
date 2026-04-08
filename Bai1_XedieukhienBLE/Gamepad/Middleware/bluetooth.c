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

void Bluetooth_SendString(char *str)
{
    UART1_SendString(str);
}

uint8_t Bluetooth_Available(void)
{
    return UART1_Available();
}

char Bluetooth_Read(void)
{
    return UART1_ReadBuffer();
}

void Bluetooth_SendNum(int32_t num){
		return UART1_SendNumber(num);
}