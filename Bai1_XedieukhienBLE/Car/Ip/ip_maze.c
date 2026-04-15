#include "ip_maze.h"
#include "ip_line_sensor.h"
#include "ip_sensor.h"
#include "ip_motor.h"
#include "ip_timer.h"

#define FRONT_LIMIT      10
#define TURN_SPEED       450
#define KP               20.0f
#define KD               8.0f

static float prev_error = 0;

// detect path
#define PATH_RIGHT(raw)     ((raw & 0x03) == 0x03)  
#define PATH_LEFT(raw)      ((raw & 0x18) == 0x18)   
#define PATH_STRAIGHT(raw)  ((raw & 0x04) != 0)
#define PATH_L_RIGHT(raw)   ((raw & 0x07) == 0x07)
#define PATH_L_LEFT(raw)    ((raw & 0x1C) == 0x1C)

/**
 * @brief Gioi han toc do PWM
 * @param x Gia tri dau vao
 * @retval Gia tri 0-1000
 */
static uint16_t Ip_ClampSpeed(int32_t x){
    if(x < 0) return 0;
    if(x > 1000) return 1000;
    return (uint16_t)x;
}

/**
 * @brief Doc cam bien line on dinh
 * @param None
 * @retval Gia tri raw
 */
static uint8_t Ip_StableRead(){
    uint8_t a = Ip_LineSensor_ReadRaw();
    Ip_Delay_ms(2);
    uint8_t b = Ip_LineSensor_ReadRaw();
    return (a == b) ? a : a;
}

/**
 * @brief Re trai 90 do
 * @param None
 * @retval None
 */
static void Ip_Turn_Left_90(void){
    while(1){
        Ip_Motor_Left(TURN_SPEED);
        uint8_t s = Ip_LineSensor_ReadRaw();
        if(s & 0x04) break; 
    }
}

/**
 * @brief Re phai 90 do
 * @param None
 * @retval None
 */
static void Ip_Turn_Right_90(void){
    while(1){
        Ip_Motor_Right(TURN_SPEED);
        uint8_t s = Ip_LineSensor_ReadRaw();
        if(s & 0x04) break;
    }
}

/**
 * @brief Quay dau
 * @param None
 * @retval None
 */
static void Ip_Turn_Back(void){
    uint8_t hit = 0;

    while(1){
        Ip_Motor_Right(TURN_SPEED);
        uint8_t s = Ip_LineSensor_ReadRaw();

        if(s & 0x04){
            hit++;
            if(hit >= 2) break; 
        }
    }
}

/**
 * @brief Thuat toan maze + line + tranh vat can
 * @param base_speed Toc do co ban
 * @retval None
 */
void Ip_Maze_Run(uint16_t base_speed){
    static uint32_t last_sr05 = 0;

    // trigger sieu am moi 60ms
    if(Ip_GetTickMs() - last_sr05 >= 60){
        Ip_Sensor_Trigger();
        last_sr05 = Ip_GetTickMs();
    }

    uint16_t front = Ip_Sensor_GetFront();
    uint8_t raw = Ip_StableRead();

    // tranh vat can
    if(front > 0 && front < FRONT_LIMIT){
        Ip_Turn_Back();
        return;
    }

    // uu tien L-shape
    if(PATH_L_LEFT(raw)){
        Ip_Turn_Left_90();
        return;
    }

    if(PATH_L_RIGHT(raw)){
        Ip_Turn_Right_90();
        return;
    }

    uint8_t left     = PATH_LEFT(raw);
    uint8_t right    = PATH_RIGHT(raw);
    uint8_t straight = PATH_STRAIGHT(raw);

    if(left){
        Ip_Turn_Left_90();
        return;
    }
    else if(right){
        Ip_Turn_Right_90();
        return;
    }
    else{
        Ip_Turn_Back();
        return;
    }

    // PID follow line (khong toi duoc do return tren)
    int8_t error = Ip_LineSensor_GetError();

    if(error == 0){
        Ip_Motor_SetSpeed(base_speed, base_speed);
        prev_error = 0;
        return;
    }

    float pid = KP * error + KD * (error - prev_error);
    prev_error = error;

    if(pid > 200) pid = 200;
    if(pid < -200) pid = -200;

    int32_t left_motor  = base_speed - pid;
    int32_t right_motor = base_speed + pid;

    Ip_Motor_SetSpeed(Ip_ClampSpeed(left_motor),
                      Ip_ClampSpeed(right_motor));
}