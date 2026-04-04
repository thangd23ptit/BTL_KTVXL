#include "maze.h"
#include "sensor.h"
#include "motor.h"

#define BASE_SPEED   600
#define WALL_TH      15
#define DESIRED      10

#define KP 15
#define KD 8

static int prev_error = 0;

static void PID(uint16_t right)
{
    int error = DESIRED - right;
    int d = error - prev_error;

    int out = KP*error + KD*d;
    prev_error = error;
    if(out > 300) out = 300;
    if(out < -300) out = -300;

    int left  = BASE_SPEED + out;
    int right_spd = BASE_SPEED - out;

    if(left < 0) left = 0;
    if(right_spd < 0) right_spd = 0;

    if(left > 1000) left = 1000;
    if(right_spd > 1000) right_spd = 1000;

    Motor_SetSpeed(left, right_spd);
}

void Maze_Init(void)
{
    Sensor_Init();
    Motor_Init();
}

void Maze_Run(void)
{
    Sensor_Update();

    uint16_t f = Sensor_Front();
    uint16_t l = Sensor_Left();
    uint16_t r = Sensor_Right();

    if(r > WALL_TH)
    {
        Motor_Right(BASE_SPEED);
    }
    else if(f > WALL_TH)
    {
        PID(r);
    }
    else if(l > WALL_TH)
    {
        Motor_Left(BASE_SPEED);
    }
    else
    {
        Motor_Backward(BASE_SPEED);
    }
}