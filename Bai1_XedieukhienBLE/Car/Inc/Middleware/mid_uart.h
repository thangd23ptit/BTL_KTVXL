#ifndef _MID_UART_H
#define _MID_UART_H

#include "stm32f10x.h"
#include <stdint.h>

void Mid_UART1_Init(uint32_t baudrate);
void Mid_UART1_SendChar(char c);
void Mid_UART1_SendString(const char *str);
uint8_t Mid_UART1_Available(void);
char Mid_UART1_ReadChar(void);
void Mid_UART1_SendNum(uint16_t num);

#endif