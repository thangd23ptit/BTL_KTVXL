#ifndef __UART_H
#define __UART_H

#include "stm32f10x.h"

#define UART_BUFFER_SIZE 128

void UART_Init(void);

uint8_t UART_Available(void);
char UART_Read(void);

void UART_SendChar(char c);
void UART_SendString(char *str);

#endif