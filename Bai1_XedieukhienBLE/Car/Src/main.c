#include "stm32f10x.h"
#include "system_init.h"
#include "control.h"
#include "sensor.h"
#include "app.h"
#include "timer.h"
#include "bluetooth.h"

int main(void)
{
    SystemInit();      // 72MHz
    System_Init();
    Sensor_Init();

    uint32_t sensor_tick = 0;
    uint8_t sensor_id = 0;

    while(1)
    {
        // 1) luôn d?c bluetooth tru?c
        Control_Run();

        // 2) d?c t?ng SR05 m?i 20ms
        if(GetTickMs() - sensor_tick >= 20)
        {
            sensor_tick = GetTickMs();

            Sensor_Trigger_All(sensor_id);
            sensor_id++;
            if(sensor_id >= 3)
                sensor_id = 0;
        }

        // 3) x? lý app
        App_Run();
    }
}