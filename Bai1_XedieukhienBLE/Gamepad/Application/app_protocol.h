#ifndef __APP_PROTOCOL_H
#define __APP_PROTOCOL_H

#include <stdint.h>

typedef enum
{
    APP_MODE_MANUAL = 'M',
    APP_MODE_AUTO   = 'A'
} app_protocol_mode_t;

typedef enum
{
    APP_CMD_STOP     = 'S',
    APP_CMD_FORWARD  = 'F',
    APP_CMD_BACKWARD = 'B',
    APP_CMD_LEFT     = 'L',
    APP_CMD_RIGHT    = 'R'
} app_protocol_cmd_t;

app_protocol_cmd_t App_Protocol_Encode(uint16_t x, uint16_t y);
void App_Protocol_Send(app_protocol_mode_t mode, app_protocol_cmd_t cmd, uint16_t speed);

#endif