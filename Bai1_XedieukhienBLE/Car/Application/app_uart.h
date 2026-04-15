#ifndef _APP_UART_H
#define _APP_UART_H

#include "stm32f10x.h"
#include <stdint.h>

void App_UART1_Init(uint32_t baudrate);
void App_UART1_SendChar(char c);
void App_UART1_SendString(const char *str);
uint8_t App_UART1_Available(void);
char App_UART1_ReadChar(void);
void App_UART1_SendNum(uint16_t num);

#endif