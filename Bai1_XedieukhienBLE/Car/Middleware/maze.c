	#include "maze.h"
	#include "sensor.h"
	#include "motor.h"
//=== Thuat toan PID giu thang bang cho xe ===
	#define FRONT_LIMIT 20
	#define KP 15.0f
	#define KI 0.0f
	#define KD 8.0f

	static float prev_error = 0;
	static float integral = 0;
	static uint16_t clamp_speed(int32_t speed){
			if(speed < 0) return 0;
			if(speed > 1000) return 1000;
			return (uint16_t)speed;
	}
void Maze_Run(uint16_t base_speed)
{
    sensor_data_t s = Sensor_GetData();

    // gap tuong truoc
    if(s.front < FRONT_LIMIT)
    {
        if(s.left > 20)
        {
            Motor_Left(base_speed);
        }
        else if(s.right > 20)
        {
            Motor_Right(base_speed);
        }
        else
        {
            Motor_Backward(base_speed);
        }
        return;
    }

    // PID giu giua hanh lang
    if(s.left < 30 && s.right < 30)
    {
        float error = (float)s.left - (float)s.right;
        integral += error;
        float derivative = error - prev_error;
        prev_error = error;

        float pid = KP * error + KD * derivative;

        int32_t left_speed  = base_speed - pid;
        int32_t right_speed = base_speed + pid;

        Motor_SetSpeed(
            clamp_speed(left_speed),
            clamp_speed(right_speed)
        );
    }
    else
    {
        Motor_SetSpeed(base_speed, base_speed);
    }
}