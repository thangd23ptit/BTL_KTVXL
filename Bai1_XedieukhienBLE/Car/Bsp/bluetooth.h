#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include <stdint.h>

void Bluetooth_Init(void);
uint8_t Bluetooth_Available(void);
char Bluetooth_Read(void);
void Bluetooth_Send(char *str);

#endif