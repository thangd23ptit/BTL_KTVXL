#ifndef _MID_BLUETOOTH_H
#define _MID_BLUETOOTH_H

#include <stdint.h>

void Mid_Bluetooth_Init(uint32_t baudrate);
uint8_t Mid_Bluetooth_Available(void);
char Mid_Bluetooth_ReadChar(void);
void Mid_Bluetooth_SendChar(char c);
void Mid_Bluetooth_SendString(const char *str);

#endif