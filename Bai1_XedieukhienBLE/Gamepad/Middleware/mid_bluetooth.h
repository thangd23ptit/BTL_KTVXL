#ifndef __MID_BLUETOOTH_H
#define __MID_BLUETOOTH_H

#include "stm32f10x.h"

void Mid_Bluetooth_Init(uint32_t baudrate);
void Mid_Bluetooth_SendChar(char c);
void Mid_Bluetooth_SendString(char *str);
uint8_t Mid_Bluetooth_Available(void);
char Mid_Bluetooth_Read(void);
void Mid_Bluetooth_SendNum(int32_t num);

#endif