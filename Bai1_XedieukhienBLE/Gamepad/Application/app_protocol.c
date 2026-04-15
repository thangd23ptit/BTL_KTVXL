#include "app_protocol.h"
#include "mid_protocol.h"

app_protocol_cmd_t App_Protocol_Encode(uint16_t x, uint16_t y)
{
    return (app_protocol_cmd_t)Mid_Protocol_Encode(x, y);
}

void App_Protocol_Send(app_protocol_mode_t mode, app_protocol_cmd_t cmd, uint16_t speed)
{
    Mid_Protocol_Send((mid_protocol_mode_t)mode, (mid_protocol_cmd_t)cmd, speed);
}