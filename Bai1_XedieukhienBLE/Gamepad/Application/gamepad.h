#ifndef __GAMEPAD_H
#define __GAMEPAD_H

#include "joystick.h"
#include "mode.h"

typedef struct
{
    Joystick_t joystick;
    Mode_t mode_button;
} Gamepad_t;

void Gamepad_Init(Gamepad_t *gp,
                  uint8_t joy_x,
                  uint8_t joy_y,
                  GPIO_TypeDef *mode_port,
                  uint16_t mode_pin);

void Gamepad_Update(Gamepad_t *gp);

#endif