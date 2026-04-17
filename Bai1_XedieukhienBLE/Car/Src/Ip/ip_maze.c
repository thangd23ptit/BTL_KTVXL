#include "ip_maze.h"
#include "ip_line_sensor.h"
#include "ip_motor.h"
#include "ip_timer.h"

/* ================= CONFIG ================= */
#define MAX_SPEED 500

/* ================= STATE ================= */
typedef enum {
    STATE_RUN,
    STATE_STOP_READ,
    STATE_EXECUTE
} SysState_t;

typedef enum {
    DIR_LEFT = 0,
    DIR_STRAIGHT,
    DIR_RIGHT,
    DIR_BACK
} Dir_t;

/* ================= GLOBAL ================= */
static SysState_t state = STATE_RUN;

static uint8_t sensor_snapshot = 0;
static Dir_t planned_move = DIR_STRAIGHT;
static Dir_t last_move = DIR_STRAIGHT;

/* ================= MOTOR ================= */
static void motor(int16_t l, int16_t r)
{
    if (l > MAX_SPEED) l = MAX_SPEED;
    if (r > MAX_SPEED) r = MAX_SPEED;
    if (l < -MAX_SPEED) l = -MAX_SPEED;
    if (r < -MAX_SPEED) r = -MAX_SPEED;

    Ip_Motor_SetSpeed(l, r);
}

/* ================= SENSOR ================= */
static uint8_t read_sensor_stable(void)
{
    uint8_t s1 = Ip_LineSensor_ReadRaw();
    Ip_Delay_ms(2);
    uint8_t s2 = Ip_LineSensor_ReadRaw();
    Ip_Delay_ms(2);
    uint8_t s3 = Ip_LineSensor_ReadRaw();

    return (s1 & s2) | (s2 & s3) | (s1 & s3);
}

/* ================= DETECT ================= */
static uint8_t is_intersection(uint8_t s)
{
    return (s == 0x1F);
}

/* ================= STRONG SKEW ================= */
static uint8_t is_strong_skew(uint8_t s)
{
    /* 11000 ho?c 00011 */
    if (s == 0x18 || s == 0x03)
        return 1;

    return 0;
}

/* ================= DECIDE ================= */
static Dir_t decide(uint8_t s)
{
    if (s & (1 << 0)) return DIR_LEFT;
    if (s & (1 << 2)) return DIR_STRAIGHT;
    if (s & (1 << 4)) return DIR_RIGHT;

    return DIR_BACK;
}

/* ================= TURN ================= */
static void turn(Dir_t d)
{
    last_move = d;

    motor(0, 0);
		Ip_Delay_ms(20);
    if (d == DIR_LEFT)
        motor(400, -400);
    else if (d == DIR_RIGHT)
        motor(-400, 400);
    else
        motor(450, 450);
}

/* ================= LOST RECOVERY ================= */
static void lost_recovery(void)
{
    motor(0, 0);
		Ip_Delay_ms(20);
    if (last_move == DIR_LEFT)
        motor(350, -350);   // quay ph?i tìm l?i
    else if (last_move == DIR_RIGHT)
        motor(-350, 350);   // quay trái tìm l?i
    else
        motor(400, -400);
}

/* ================= FOLLOW LINE ================= */
static void follow_line(void)
{
    int16_t error = Ip_LineSensor_GetError();

    int16_t base = 250;
    int16_t corr = error * 0.8f;

    motor(base + corr, base - corr);
}

/* ================= MAIN ================= */
void Ip_Maze_Run(uint16_t base_speed)
{
    switch (state)
    {
        /* ================= RUN ================= */
        case STATE_RUN:
        {
            uint8_t s = read_sensor_stable();

            /* ================= LOST ================= */
            if (s == 0x00)
            {
                motor(0, 0);
                state = STATE_STOP_READ;
                break;
            }

            /* ================= STRONG SKEW (11100 / 00111) ================= */
            if (is_strong_skew(s))
            {
                motor(0, 0);
                state = STATE_STOP_READ;
                break;
            }

            /* ================= INTERSECTION ================= */
            if (is_intersection(s))
            {
                motor(0, 0);
                state = STATE_STOP_READ;
                break;
            }

            /* ================= NORMAL FOLLOW ================= */
            follow_line();

            break;
        }

        /* ================= STOP + READ ================= */
        case STATE_STOP_READ:
        {
            sensor_snapshot = read_sensor_stable();

            /* ================= LOST ================= */
            if (sensor_snapshot == 0x00)
            {
                lost_recovery();
                state = STATE_RUN;
                break;
            }

            planned_move = decide(sensor_snapshot);

            state = STATE_EXECUTE;
            break;
        }

        /* ================= EXECUTE ================= */
        case STATE_EXECUTE:
        {
            turn(planned_move);
            state = STATE_RUN;
            break;
        }
    }
}

/* ================= RESET ================= */
void Ip_Maze_Reset(void)
{
    state = STATE_RUN;
    last_move = DIR_STRAIGHT;
}