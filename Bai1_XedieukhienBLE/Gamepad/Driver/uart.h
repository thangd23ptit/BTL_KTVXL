#ifndef __UART_H
#define __UART_H

#include "stm32f10x.h"
#define UART_RX_BUFFER_SIZE 64
void UART1_Init(uint32_t baudrate);
void UART1_SendChar(char c);
void UART1_SendString(char *str);
uint8_t UART1_Available(void);
char UART1_ReadBuffer(void);
void UART1_SendNumber(int32_t num);

#endif