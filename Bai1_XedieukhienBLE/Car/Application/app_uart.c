#include "app_uart.h"
#include "mid_uart.h"

void App_UART1_Init(uint32_t baudrate)
{
    Mid_UART1_Init(baudrate);
}

void App_UART1_SendChar(char c)
{
    Mid_UART1_SendChar(c);
}

void App_UART1_SendString(const char *str)
{
    Mid_UART1_SendString(str);
}

uint8_t App_UART1_Available(void)
{
    return Mid_UART1_Available();
}

char App_UART1_ReadChar(void)
{
    return Mid_UART1_ReadChar();
}

void App_UART1_SendNum(uint16_t num)
{
    Mid_UART1_SendNum(num);
}