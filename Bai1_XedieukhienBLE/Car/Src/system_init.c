
#include "timer.h"
#include "bluetooth.h"
#include "motor.h"
#include "sensor.h"
#include "line_sensor.h"
#include "system_init.h"

void System_Init(void)
{
    SystemInit();

    /* core drivers */
    TIM3_Init_1ms();
		TIM4_Init_1us();
    Bluetooth_Init(9600);

    /* bsp */
    Motor_Init();
    Sensor_Init();        // SR05 front
    LineSensor_Init();    // 5 line

    /* sensor startup stable */
    Delay_ms(300);

    Bluetooth_SendString("=== SYSTEM INIT OK ===\r\n");
}