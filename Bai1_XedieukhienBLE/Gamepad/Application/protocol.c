#include "protocol.h"

void Protocol_BuildPacket(uint16_t joy_x,
                          uint16_t joy_y,
                          uint8_t mode,
                          uint8_t *buffer)
{
    buffer[0] = PKT_HEADER;
    buffer[1] = (uint8_t)(joy_x >> 4);
    buffer[2] = (uint8_t)(joy_y >> 4);
    buffer[3] = mode;
    buffer[4] = PKT_TAIL;
}

uint8_t Protocol_ParseMode(uint8_t *buffer)
{
    if (buffer[0] != PKT_HEADER || buffer[4] != PKT_TAIL)
        return 0;

    return buffer[3];
}

