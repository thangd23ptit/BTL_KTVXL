#ifndef __MID_PROTOCOL_H
#define __MID_PROTOCOL_H

#include <stdint.h>

typedef enum
{
    MID_MODE_MANUAL = 'M',
    MID_MODE_AUTO   = 'A'
} mid_protocol_mode_t;

typedef enum
{
    MID_CMD_STOP     = 'S',
    MID_CMD_FORWARD  = 'F',
    MID_CMD_BACKWARD = 'B',
    MID_CMD_LEFT     = 'L',
    MID_CMD_RIGHT    = 'R'
} mid_protocol_cmd_t;

mid_protocol_cmd_t Mid_Protocol_Encode(uint16_t x, uint16_t y);
void Mid_Protocol_Send(mid_protocol_mode_t mode, mid_protocol_cmd_t cmd, uint16_t speed);

#endif