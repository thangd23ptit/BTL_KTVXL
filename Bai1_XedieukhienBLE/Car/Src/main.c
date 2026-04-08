#include "stm32f10x.h"
#include "system_init.h"
#include "control.h"
#include "sensor.h"
#include "app.h"
#include "timer.h"
#include "bluetooth.h"

int main(void)
{
    SystemInit();
    System_Init();

    Bluetooth_SendString("CAR START\r\n");

    while(1)
    {
        /* 1. d?c d? li?u BLE */
        Control_Run();

        /* 2. kích toàn b? SR05 */
        Sensor_Trigger_All();

        /* 3. ch? sensor c?p nh?t */
        Delay_ms(50);

        /* 4. ch?y app theo mode */
        App_Run();
    }
}