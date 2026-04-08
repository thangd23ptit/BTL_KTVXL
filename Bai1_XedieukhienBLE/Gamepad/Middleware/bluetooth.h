#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include "stm32f10x.h"

void Bluetooth_Init(uint32_t baudrate);
void Bluetooth_SendChar(char c);
void Bluetooth_SendString(char *str);
uint8_t Bluetooth_Available(void);
char Bluetooth_Read(void);
void Bluetooth_SendNum(int32_t num);

#endif