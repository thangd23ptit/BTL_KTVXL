#include "app_gamepad.h"
#include "mid_gamepad.h"

void App_Gamepad_Init(App_Gamepad_t *gp, uint8_t joy_x, uint8_t joy_y,
                      GPIO_TypeDef *mode_port, uint16_t mode_pin)
{
    Mid_Gamepad_Init((Mid_Gamepad_t *)gp, joy_x, joy_y, mode_port, mode_pin);
}

void App_Gamepad_Update(App_Gamepad_t *gp)
{
    Mid_Gamepad_Update((Mid_Gamepad_t *)gp);
}