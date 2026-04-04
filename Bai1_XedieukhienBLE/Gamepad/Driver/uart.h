#ifndef UART_H
#define UART_H

#include "stm32f10x.h"
#include <stdint.h>

void UART1_Init(uint32_t baudrate);
void UART1_SendChar(char c);
void UART1_SendString(const char *str);
void UART1_SendBuffer(uint8_t *data, uint16_t len);

#endif