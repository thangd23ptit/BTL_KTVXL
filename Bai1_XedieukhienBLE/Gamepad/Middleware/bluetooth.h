#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include <stdint.h>

void Bluetooth_Init(uint32_t baudrate);

void Bluetooth_SendChar(char c);
void Bluetooth_SendString(const char *str);
void Bluetooth_SendBuffer(uint8_t *data, uint16_t len);

/* RX interrupt wrapper */
uint8_t Bluetooth_Available(void);
char Bluetooth_ReadChar(void);

#endif