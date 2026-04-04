#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>

typedef struct
{
    uint16_t x;
    uint16_t y;
} Joystick_Data_t;

void Joystick_Init(void);
void Joystick_Read(Joystick_Data_t *joy);
uint8_t Mode_Read(void);

#endif