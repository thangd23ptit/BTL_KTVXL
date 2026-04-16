#ifndef __MID_GAMEPAD_H
#define __MID_GAMEPAD_H

#include "mid_joystick.h"
#include "mid_mode.h"

typedef struct
{
    Mid_Joystick_t joystick;
    Mid_Mode_t mode_button;
} Mid_Gamepad_t;

void Mid_Gamepad_Init(Mid_Gamepad_t *gamepad, uint8_t joy_x, uint8_t joy_y, GPIO_TypeDef *mode_port, uint16_t mode_pin);
void Mid_Gamepad_Update(Mid_Gamepad_t *gamepad);

#endif