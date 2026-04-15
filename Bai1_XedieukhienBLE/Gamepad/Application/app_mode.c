#include "app_mode.h"
#include "mid_mode.h"

void App_Mode_Init(App_Mode_t *mode, GPIO_TypeDef *port, uint16_t pin)
{
    Mid_Mode_Init((Mid_Mode_t *)mode, port, pin);
}

app_protocol_mode_t App_Mode_Update(App_Mode_t *mode)
{
    return (app_protocol_mode_t)Mid_Mode_Update((Mid_Mode_t *)mode);
}