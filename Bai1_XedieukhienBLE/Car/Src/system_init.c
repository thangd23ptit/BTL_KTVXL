#include "system_init.h"
#include "timer.h"
#include "motor.h"
#include "sensor.h"
#include "control.h"
#include "app.h"

void System_Init(void)
{
    /* system tick 1ms */
    TIM3_Init_1ms();

    /* motor + pwm */
    Motor_Init();

    /* bluetooth middleware */
    Control_Init();

    /* 3 SR05 */
    Sensor_Init();

    /* application */
    App_Init();
}