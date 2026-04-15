#ifndef _IP_UART_H
#define _IP_UART_H

#include "stm32f10x.h"
#include <stdint.h>

#define IP_UART_RX_BUFFER_SIZE 64

void Ip_UART1_Init(uint32_t baudrate);
void Ip_UART1_SendChar(char c);
void Ip_UART1_SendString(char *str);
uint8_t Ip_UART1_Available(void);
char Ip_UART1_ReadBuffer(void);
void Ip_UART1_SendNumber(int32_t num);

#endif