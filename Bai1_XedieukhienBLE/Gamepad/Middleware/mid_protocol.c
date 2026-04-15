#include "ip_protocol.h"
#include "ip_bluetooth.h"
#include "mid_protocol.h"

mid_protocol_cmd_t Mid_Protocol_Encode(uint16_t x, uint16_t y)
{
    return Ip_Protocol_Encode(x, y);
}

void Mid_Protocol_Send(mid_protocol_mode_t mode, mid_protocol_cmd_t cmd, uint16_t speed)
{
    Ip_Protocol_Send(mode, cmd, speed);
}