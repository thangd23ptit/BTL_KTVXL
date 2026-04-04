#ifndef MODE_H
#define MODE_H

#include <stdint.h>

#define MODE_MANUAL_NORMAL   0
#define MODE_PRECISION       1
#define MODE_AUTO            2

uint8_t Mode_GetMode(uint8_t raw_mode);
uint8_t Mode_IsAuto(uint8_t mode);
uint8_t Mode_LimitSpeed(uint8_t mode, uint8_t pwm);

#endif