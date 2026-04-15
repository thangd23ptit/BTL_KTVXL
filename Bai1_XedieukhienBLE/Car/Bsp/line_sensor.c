#include "line_sensor.h"
#include "gpio.h"

void LineSensor_Init(void)
{
    GPIO_Config_Input_PU(GPIOA, 3);
    GPIO_Config_Input_PU(GPIOA, 4);
    GPIO_Config_Input_PU(GPIOA, 5);
    GPIO_Config_Input_PU(GPIOB, 12);
    GPIO_Config_Input_PU(GPIOB, 13);
}

uint8_t LineSensor_ReadRaw(void){
    uint8_t d = 0;
    d |= GPIO_Read(GPIOA, 3) << 0;
    d |= GPIO_Read(GPIOA, 4) << 1;
    d |= GPIO_Read(GPIOA, 5) << 2;
    d |= GPIO_Read(GPIOB,12) << 3;
    d |= GPIO_Read(GPIOB,13) << 4;
    d = ~d & 0x1F;
    return d;
}
int8_t LineSensor_GetError(void){
    uint8_t s = LineSensor_ReadRaw();

    int sum = 0;
    int cnt = 0;
    if(s & 0x01){ sum += -2; cnt++; }
    if(s & 0x02){ sum += -1; cnt++; }
    if(s & 0x04){ sum +=  0; cnt++; }
    if(s & 0x08){ sum +=  1; cnt++; }
    if(s & 0x10){ sum +=  2; cnt++; }
    static int8_t last_error = 0;
    if(cnt == 0){
        return last_error;  
    }
    int8_t new_error = sum / cnt;
    int8_t filtered = (last_error * 2 + new_error) / 3;
    last_error = filtered;
    return filtered;
}