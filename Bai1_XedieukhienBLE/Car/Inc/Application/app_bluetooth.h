#ifndef _APP_BLUETOOTH_H
#define _APP_BLUETOOTH_H

#include <stdint.h>

void App_Bluetooth_Init(uint32_t baudrate);
uint8_t App_Bluetooth_Available(void);
char App_Bluetooth_ReadChar(void);
void App_Bluetooth_SendChar(char c);
void App_Bluetooth_SendString(const char *str);

#endif