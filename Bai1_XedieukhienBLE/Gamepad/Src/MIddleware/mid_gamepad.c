#include "ip_gamepad.h"
#include "mid_gamepad.h"

void Mid_Gamepad_Init(Mid_Gamepad_t *gamepad, uint8_t joy_x, uint8_t joy_y,
                      GPIO_TypeDef *mode_port, uint16_t mode_pin)
{
    Ip_Gamepad_Init(gamepad, joy_x, joy_y, mode_port, mode_pin);
}

void Mid_Gamepad_Update(Mid_Gamepad_t *gamepad)
{
    Ip_Gamepad_Update(gamepad);
}