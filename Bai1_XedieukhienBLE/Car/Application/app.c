#include "app.h"
#include "system_init.h"
#include "control.h"
#include "app_control.h"
#include "app_auto.h"
#include "motor.h"
#include "timer.h"
#include "bluetooth.h"

static app_mode_t g_mode = APP_MODE_MANUAL;
static uint32_t last_rx_time = 0;

void App_Init(void){
    System_Init();
    Control_Init();   
}

void App_Run(void){
    Control_Run();
    control_data_t data = Control_GetData();
    g_mode = (app_mode_t)data.mode;
    if(Bluetooth_Available()){
        last_rx_time = GetTickMs();
    }
    if(GetTickMs() - last_rx_time > 1000){
        Motor_Stop();
        return;
    }
    switch(g_mode){
        case APP_MODE_MANUAL:
            App_Control_Run();
            break;
        case APP_MODE_AUTO:
            App_Auto_Run();
            break;
        default:
            Motor_Stop();
            break;
    }
}