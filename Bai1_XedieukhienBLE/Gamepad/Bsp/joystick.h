#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include <stdint.h>

typedef struct
{
    uint16_t x;
    uint16_t y;
} joystick_data_t;

void Joystick_Init(void);
void Joystick_Read(uint16_t *x, uint16_t *y);
joystick_data_t Joystick_GetData(void);

#endif