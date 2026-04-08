#include "system_init.h"
#include "timer.h"
#include "motor.h"
#include "sensor.h"
#include "control.h"
#include "app.h"
#include "bluetooth.h"

//ham khoi tao tong hop
void System_Init(void){
    TIM3_Init_1ms();
    Motor_Init();
    Control_Init();
    Sensor_Init();
		Bluetooth_Init(9600);
}