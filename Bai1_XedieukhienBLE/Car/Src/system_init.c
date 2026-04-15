#include "system_init.h"
#include "app_timer.h"
#include "app_control.h"
#include "app_motor.h"
#include "app_sensor.h"
#include "app_line_sensor.h"
#include "stm32f10x.h"

void System_Init(void)
{
    SystemInit();

    App_TIM3_Init_1ms();
    App_TIM4_Init_1us();

    App_Control_Init();
    App_Motor_Init();
    App_Sensor_Init();
    App_LineSensor_Init();
}