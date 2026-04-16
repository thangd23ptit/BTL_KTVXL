#include "ip_uart.h"
#include "mid_uart.h"

static volatile char rx_buffer[MID_UART_RX_BUFFER_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;

void Mid_UART1_Init(uint32_t baudrate)
{
    Ip_UART1_Init(baudrate);
}

void Mid_UART1_SendChar(char c)
{
    Ip_UART1_SendChar(c);
}

void Mid_UART1_SendString(char *str)
{
    Ip_UART1_SendString(str);
}

uint8_t Mid_UART1_Available(void)
{
    return Ip_UART1_Available();
}

char Mid_UART1_ReadBuffer(void)
{
    return Ip_UART1_ReadBuffer();
}

void Mid_UART1_SendNumber(int32_t num)
{
    Ip_UART1_SendNumber(num);
}