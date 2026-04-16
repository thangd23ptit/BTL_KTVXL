#ifndef __APP_GAMEPAD_H
#define __APP_GAMEPAD_H

#include "app_joystick.h"
#include "app_mode.h"

typedef struct
{
    App_Joystick_t joystick;
    App_Mode_t mode_button;
} App_Gamepad_t;

void App_Gamepad_Init(App_Gamepad_t *gp, uint8_t joy_x, uint8_t joy_y, GPIO_TypeDef *mode_port, uint16_t mode_pin);
void App_Gamepad_Update(App_Gamepad_t *gp);

#endif