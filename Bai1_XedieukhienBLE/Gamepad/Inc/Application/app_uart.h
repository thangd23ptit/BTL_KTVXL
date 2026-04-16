#ifndef _APP_UART_H
#define _APP_UART_H

#include "stm32f10x.h"
#include <stdint.h>

#define APP_UART_RX_BUFFER_SIZE 64

void App_UART1_Init(uint32_t baudrate);
void App_UART1_SendChar(char c);
void App_UART1_SendString(char *str);
uint8_t App_UART1_Available(void);
char App_UART1_ReadBuffer(void);
void App_UART1_SendNumber(int32_t num);

#endif