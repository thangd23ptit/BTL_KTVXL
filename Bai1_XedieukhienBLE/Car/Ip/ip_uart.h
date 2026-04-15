#ifndef _IP_UART_H
#define _IP_UART_H

#include "stm32f10x.h"
#include <stdint.h>

// ================== FUNCTION ==================

void Ip_UART1_Init(uint32_t baudrate);
void Ip_UART1_SendChar(char c);
void Ip_UART1_SendString(const char *str);
uint8_t Ip_UART1_Available(void);
char Ip_UART1_ReadChar(void);
void Ip_UART1_SendNum(uint16_t num);

#endif