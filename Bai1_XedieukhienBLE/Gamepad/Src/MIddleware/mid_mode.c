#include "ip_mode.h"
#include "mid_mode.h"

void Mid_Mode_Init(Mid_Mode_t *mode, GPIO_TypeDef *port, uint16_t pin)
{
    Ip_Mode_Init(mode, port, pin);
}

protocol_mode_t Mid_Mode_Update(Mid_Mode_t *mode)
{
    return Ip_Mode_Update(mode);
}