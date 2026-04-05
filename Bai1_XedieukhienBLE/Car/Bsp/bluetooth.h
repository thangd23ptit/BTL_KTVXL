#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include <stdint.h>

void Bluetooth_Init(uint32_t baudrate);
uint8_t Bluetooth_Available(void);
char Bluetooth_ReadChar(void);
void Bluetooth_SendChar(char c);
void Bluetooth_SendString(const char *str);

#endif