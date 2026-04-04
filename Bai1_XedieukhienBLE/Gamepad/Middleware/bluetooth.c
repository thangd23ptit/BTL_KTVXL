#include "bluetooth.h"
#include "uart.h"

void Bluetooth_Init(void)
{
    UART1_Init(9600);
}

void Bluetooth_SendPacket(uint16_t joy_x, uint16_t joy_y, uint8_t mode)
{
    uint8_t packet[	5];

    packet[0] = 0xAA;
    packet[1] = (uint8_t)(joy_x >> 4); // 12-bit -> 8-bit
    packet[2] = (uint8_t)(joy_y >> 4);
    packet[3] = mode;
    packet[4] = 0x55;

    UART1_SendBuffer(packet, 5);
}

void Bluetooth_SendAuto(void)
{
    uint8_t packet[5] = {0xAA, 0x80, 0x80, 2, 0x55};
    UART1_SendBuffer(packet, 5);
}

