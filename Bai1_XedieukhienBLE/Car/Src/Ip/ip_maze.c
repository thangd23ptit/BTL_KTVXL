#include "ip_maze.h"
#include "ip_line_sensor.h"
#include "ip_sensor.h"
#include "ip_motor.h"
#include "ip_timer.h"

#define FRONT_LIMIT   10
#define BASE_SPEED    350
#define TURN_SPEED    450

static float prev_error = 0;

/* ================= MOTOR STOP ================= */
static void Ip_Stop(void)
{
    Ip_Motor_SetSpeed(0, 0);
    Ip_Delay_ms(120);
}

/* ================= TURN ================= */
static void Ip_Turn_Left(void)
{
    Ip_Motor_SetSpeed(0, TURN_SPEED);
    Ip_Delay_ms(150);
}

static void Ip_Turn_Right(void)
{
    Ip_Motor_SetSpeed(TURN_SPEED, 0);
    Ip_Delay_ms(150);
}

static void Ip_Turn_Back(void)
{
    Ip_Stop();
    Ip_Motor_SetSpeed(TURN_SPEED, 0);
    Ip_Delay_ms(300);
}

/* ================= MAZE RUN ================= */
void Ip_Maze_Run(uint16_t base_speed)
{
    static uint32_t last_sr05 = 0;

    /* trigger ultrasonic */
    if (Ip_GetTickMs() - last_sr05 >= 60)
    {
        Ip_Sensor_Trigger();
        last_sr05 = Ip_GetTickMs();
    }

    uint16_t front = Ip_Sensor_GetFront();
    uint8_t raw = Ip_LineSensor_ReadRaw();
    int8_t error = Ip_LineSensor_GetError();

    /* ================= OBSTACLE ================= */
    if (front > 0 && front < FRONT_LIMIT)
    {
        Ip_Turn_Back();
        return;
    }

    /* ================= JUNCTION DETECT ================= */
    if (error >= -1 && error <= 1)
    {
        if ((raw & 0x0F) != 0)
        {
            /* LEFT L */
            if ((raw & 0x1C) == 0x1C)
            {
                Ip_Stop();
                Ip_Turn_Left();

                Ip_Motor_SetSpeed(base_speed, base_speed);
                Ip_Delay_ms(80);
                return;
            }

            /* RIGHT L */
            if ((raw & 0x07) == 0x07)
            {
                Ip_Stop();
                Ip_Turn_Right();

                Ip_Motor_SetSpeed(base_speed, base_speed);
                Ip_Delay_ms(80);
                return;
            }

            /* DEAD END */
            if (raw == 0)
            {
                Ip_Turn_Back();
                return;
            }
        }
    }

    /* ================= PID LINE FOLLOW ================= */
    if (error == 0)
    {
        Ip_Motor_SetSpeed(base_speed, base_speed);
        prev_error = 0;
        return;
    }

    float pid = 20.0f * error + 8.0f * (error - prev_error);
    prev_error = error;

    if (pid > 200) pid = 200;
    if (pid < -200) pid = -200;

    int32_t left  = base_speed - pid;
    int32_t right = base_speed + pid;

    Ip_Motor_SetSpeed(
        (left < 0 ? 0 : (left > 1000 ? 1000 : left)),
        (right < 0 ? 0 : (right > 1000 ? 1000 : right))
    );
}