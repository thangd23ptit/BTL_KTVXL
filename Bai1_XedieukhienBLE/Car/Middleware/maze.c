#include "maze.h"
#include "line_sensor.h"
#include "sensor.h"
#include "motor.h"
#include "timer.h"

#define FRONT_LIMIT      10
#define TURN_SPEED       450

#define KP               35.0f
#define KD               15.0f

#define TURN_DELAY_90    180
#define UTURN_DELAY      350

#define TURN_TIMEOUT     600   

static float prev_error = 0;
static uint16_t clamp_speed(int32_t x){
    if(x < 0) return 0;
    if(x > 1000) return 1000;
    return (uint16_t)x;
}

static void Turn_Left_90(void){
    uint32_t start = GetTickMs();
    Motor_Left(TURN_SPEED);
    Delay_ms(TURN_DELAY_90);
    while(LineSensor_ReadRaw() == 0){
        Motor_Left(TURN_SPEED);
        if(GetTickMs() - start > TURN_TIMEOUT)
            break;
    }
}

static void Turn_Right_90(void){
    uint32_t start = GetTickMs();
    Motor_Right(TURN_SPEED);
    Delay_ms(TURN_DELAY_90);
    while(LineSensor_ReadRaw() == 0){
        Motor_Right(TURN_SPEED);
        if(GetTickMs() - start > TURN_TIMEOUT)
            break;
    }
}

static void Turn_Back(void){
    uint32_t start = GetTickMs();
    Motor_Right(TURN_SPEED);
    Delay_ms(UTURN_DELAY);
    while(LineSensor_ReadRaw() == 0){
        Motor_Right(TURN_SPEED);
        if(GetTickMs() - start > TURN_TIMEOUT)
            break;
    }
}

void Maze_Run(uint16_t base_speed){
    static uint32_t last_sr05 = 0;
    if(GetTickMs() - last_sr05 >= 60){
        Sensor_Trigger();
        last_sr05 = GetTickMs();
    }
    uint16_t front = Sensor_GetFront();
    uint8_t raw = LineSensor_ReadRaw();
    if(front > 0 && front < FRONT_LIMIT){
        if((raw & 0x03) == 0x03){
            Turn_Left_90();
        }
        else if((raw & 0x18) == 0x18){
            Turn_Right_90();
        }
        else{
            Turn_Back();
        }
        return;
    }
    if((raw & 0x1F) >= 0x0F){
        Turn_Left_90();
        return;
    }
    if((raw & 0x03) == 0x03){
        Turn_Left_90();
        return;
    }
    if((raw & 0x18) == 0x18){
        Turn_Right_90();
        return;
    }
    if(raw == 0){
        Motor_Stop();
        return;
    }
    int8_t error = LineSensor_GetError();
    float pid = KP * error + KD * (error - prev_error);
    prev_error = error;
    if(pid > 300) pid = 300;
    if(pid < -300) pid = -300;
    int32_t left  = base_speed - pid;
    int32_t right = base_speed + pid;
    Motor_SetSpeed(clamp_speed(left), clamp_speed(right));
}