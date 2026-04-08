#include "stm32f10x.h"
#include "system_init.h"
#include "control.h"
#include "sensor.h"
#include "app.h"
#include "timer.h"
#include "bluetooth.h"

int main(void){
    SystemInit();// config system 72MHz
    System_Init();
    while(1){
        Control_Run();//doc frame tu bluetooth 
        Sensor_Trigger_All();//khoi tao tat ca sensor 
        Delay_ms(50);
        App_Run();//bat dau 
    }
}