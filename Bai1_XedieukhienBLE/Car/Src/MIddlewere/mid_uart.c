#include "mid_uart.h"
#include "ip_uart.h"

void Mid_UART1_Init(uint32_t baudrate)
{
    Ip_UART1_Init(baudrate);
}

void Mid_UART1_SendChar(char c)
{
    Ip_UART1_SendChar(c);
}

void Mid_UART1_SendString(const char *str)
{
    Ip_UART1_SendString(str);
}

uint8_t Mid_UART1_Available(void)
{
    return Ip_UART1_Available();
}

char Mid_UART1_ReadChar(void)
{
    return Ip_UART1_ReadChar();
}

void Mid_UART1_SendNum(uint16_t num)
{
    Ip_UART1_SendNum(num);
}