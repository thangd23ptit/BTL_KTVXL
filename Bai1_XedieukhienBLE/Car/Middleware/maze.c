#include "maze.h"
#include "line_sensor.h"
#include "sensor.h"
#include "motor.h"
#include "timer.h"

/* ================= CONFIG ================= */
#define FRONT_LIMIT      10
#define TURN_SPEED       420

#define KP               38.0f
#define KD               20.0f

#define TURN_DELAY_90    220
#define UTURN_DELAY      420

/* ================= PID ================= */
static float prev_error = 0;

/* ================= UTIL ================= */
static uint16_t clamp_speed(int32_t x)
{
    if(x < 0) return 0;
    if(x > 1000) return 1000;
    return (uint16_t)x;
}

static void Turn_Left_90(void)
{
    Motor_Left(TURN_SPEED);
    Delay_ms(TURN_DELAY_90);

    while(LineSensor_ReadRaw() == 0)
    {
        Motor_Left(TURN_SPEED);
    }
}

static void Turn_Right_90(void)
{
    Motor_Right(TURN_SPEED);
    Delay_ms(TURN_DELAY_90);

    while(LineSensor_ReadRaw() == 0)
    {
        Motor_Right(TURN_SPEED);
    }
}

static void Turn_Back(void)
{
    Motor_Right(TURN_SPEED);
    Delay_ms(UTURN_DELAY);

    while(LineSensor_ReadRaw() == 0)
    {
        Motor_Right(TURN_SPEED);
    }
}

/* ================= MAIN ================= */
void Maze_Run(uint16_t base_speed)
{
    static uint32_t last_sr05 = 0;

    /* trigger SR05 m?i 60ms */
    if(GetTickMs() - last_sr05 >= 60)
    {
        Sensor_Trigger();
        last_sr05 = GetTickMs();
    }

    uint16_t front = Sensor_GetFront();
    uint8_t raw = LineSensor_ReadRaw();

    /* ===== WALL FRONT ===== */
    if(front > 0 && front < FRONT_LIMIT)
    {
        if((raw & 0x07) == 0x07)
        {
            Turn_Left_90();
        }
        else if((raw & 0x1C) == 0x1C)
        {
            Turn_Right_90();
        }
        else
        {
            Turn_Back();
        }
        return;
    }

    /* ===== INTERSECTION ===== */
    if(raw == 0x1F)
    {
        Turn_Left_90();
        return;
    }

    /* ===== LEFT L ===== */
    if((raw & 0x07) == 0x07)
    {
        Turn_Left_90();
        return;
    }

    /* ===== RIGHT L ===== */
    if((raw & 0x1C) == 0x1C)
    {
        Turn_Right_90();
        return;
    }

    /* ===== PID LINE FOLLOW ===== */
    int8_t error = LineSensor_GetError();

    float pid = KP * error + KD * (error - prev_error);
    prev_error = error;

    int32_t left  = base_speed - pid + 20;
    int32_t right = base_speed + pid;

    Motor_SetSpeed(
        clamp_speed(left),
        clamp_speed(right)
    );
}