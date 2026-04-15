#ifndef __APP_BLUETOOTH_H
#define __APP_BLUETOOTH_H

#include "stm32f10x.h"

void App_Bluetooth_Init(uint32_t baudrate);
void App_Bluetooth_SendChar(char c);
void App_Bluetooth_SendString(char *str);
uint8_t App_Bluetooth_Available(void);
char App_Bluetooth_Read(void);
void App_Bluetooth_SendNum(int32_t num);

#endif