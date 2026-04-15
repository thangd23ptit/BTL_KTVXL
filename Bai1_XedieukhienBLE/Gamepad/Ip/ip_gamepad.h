#ifndef __IP_GAMEPAD_H
#define __IP_GAMEPAD_H

#include "ip_joystick.h"
#include "ip_mode.h"

typedef struct
{
    Joystick_t joystick;
    Mode_t mode_button;
} Gamepad_t;

void Ip_Gamepad_Init(Gamepad_t *gp, uint8_t joy_x, uint8_t joy_y, GPIO_TypeDef *mode_port, uint16_t mode_pin);
void Ip_Gamepad_Update(Gamepad_t *gp);

#endif