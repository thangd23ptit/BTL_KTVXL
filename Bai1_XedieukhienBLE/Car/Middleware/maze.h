#ifndef MAZE_H
#define MAZE_H

#include "sensor.h"
#include "motor.h"

#define BASE_SPEED 600
#define DESIRED_DIST 10 //khoang canh tuong phai
#define KP 15
#define KD 8

#define WALL_TH 15

void Maze_Init(void);
void Maze_Run(void);

#endif