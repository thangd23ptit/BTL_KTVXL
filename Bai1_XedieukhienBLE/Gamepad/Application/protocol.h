#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <stdint.h>

typedef enum
{
    MODE_MANUAL = 'M',
    MODE_AUTO   = 'A'
} protocol_mode_t;

typedef enum
{
    CMD_STOP     = 'S',
    CMD_FORWARD  = 'F',
    CMD_BACKWARD = 'B',
    CMD_LEFT     = 'L',
    CMD_RIGHT    = 'R'
} protocol_cmd_t;

protocol_cmd_t Protocol_Encode(uint16_t x, uint16_t y);
void Protocol_Send(protocol_mode_t mode, protocol_cmd_t cmd, uint16_t speed);

#endif