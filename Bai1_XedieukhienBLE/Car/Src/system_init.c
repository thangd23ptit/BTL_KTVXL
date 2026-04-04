#include "system_init.h"

void System_Init(void){
	UART_Init();
	PWM_Init();
	Sensor_Init();
	Motor_Init();
	Timer_Init();
}