#ifndef _IP_BLUETOOTH_H
#define _IP_BLUETOOTH_H

#include <stdint.h>

// ================== FUNCTION ==================

void Ip_Bluetooth_Init(uint32_t baudrate);
uint8_t Ip_Bluetooth_Available(void);
char Ip_Bluetooth_ReadChar(void);
void Ip_Bluetooth_SendChar(char c);
void Ip_Bluetooth_SendString(const char *str);

#endif