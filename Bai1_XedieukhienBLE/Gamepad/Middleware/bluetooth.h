#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdint.h>

void Bluetooth_Init(void);
void Bluetooth_SendPacket(uint16_t joy_x, uint16_t joy_y, uint8_t mode);
void Bluetooth_SendAuto(void);

#endif