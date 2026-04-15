#ifndef __IP_BLUETOOTH_H
#define __IP_BLUETOOTH_H

#include "stm32f10x.h"

void Ip_Bluetooth_Init(uint32_t baudrate);
void Ip_Bluetooth_SendChar(char c);
void Ip_Bluetooth_SendString(char *str);
uint8_t Ip_Bluetooth_Available(void);
char Ip_Bluetooth_Read(void);
void Ip_Bluetooth_SendNum(int32_t num);

#endif