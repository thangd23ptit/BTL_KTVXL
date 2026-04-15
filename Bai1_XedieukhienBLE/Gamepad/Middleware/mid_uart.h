#ifndef _MID_UART_H
#define _MID_UART_H

#include "stm32f10x.h"
#include <stdint.h>

#define MID_UART_RX_BUFFER_SIZE 64

void Mid_UART1_Init(uint32_t baudrate);
void Mid_UART1_SendChar(char c);
void Mid_UART1_SendString(char *str);
uint8_t Mid_UART1_Available(void);
char Mid_UART1_ReadBuffer(void);
void Mid_UART1_SendNumber(int32_t num);

#endif