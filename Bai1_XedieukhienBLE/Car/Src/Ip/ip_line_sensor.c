#include "ip_line_sensor.h"
#include "ip_gpio.h"

void Ip_LineSensor_Init(void)
{
    Ip_GPIO_Config_Input_PU(GPIOA, 3);
    Ip_GPIO_Config_Input_PU(GPIOA, 4);
    Ip_GPIO_Config_Input_PU(GPIOA, 5);
    Ip_GPIO_Config_Input_PU(GPIOB, 12);
    Ip_GPIO_Config_Input_PU(GPIOB, 13);
}

uint8_t Ip_LineSensor_ReadRaw(void)
{
    uint8_t d = 0;

    d |= Ip_GPIO_Read(GPIOA, 3) << 0;
    d |= Ip_GPIO_Read(GPIOA, 4) << 1;
    d |= Ip_GPIO_Read(GPIOA, 5) << 2;
    d |= Ip_GPIO_Read(GPIOB, 12) << 3;
    d |= Ip_GPIO_Read(GPIOB, 13) << 4;

    return (~d) & 0x1F;   // active low
}

/* ================= PID ERROR ================= */
int8_t Ip_LineSensor_GetError(void)
{
    uint8_t s = Ip_LineSensor_ReadRaw();

    int sum = 0;
    int cnt = 0;

    if (s & 0x01) { sum += -4; cnt++; }
    if (s & 0x02) { sum += -2; cnt++; }
    if (s & 0x04) { sum +=  0; cnt++; }
    if (s & 0x08) { sum +=  2; cnt++; }
    if (s & 0x10) { sum +=  4; cnt++; }

    if (cnt == 0)
        return 0;

    return sum / cnt;
}