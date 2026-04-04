#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define PKT_HEADER 0xAA
#define PKT_TAIL   0x55

typedef struct
{
    uint8_t x;
    uint8_t y;
    uint8_t mode;
} Protocol_Packet_t;

void Protocol_BuildPacket(uint16_t joy_x,
                          uint16_t joy_y,
                          uint8_t mode,
                          uint8_t *buffer);

uint8_t Protocol_ParseMode(uint8_t *buffer);

#endif