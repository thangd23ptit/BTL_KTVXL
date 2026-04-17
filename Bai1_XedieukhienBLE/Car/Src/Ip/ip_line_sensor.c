#include "ip_line_sensor.h"
#include "ip_gpio.h"

/* ================= CONFIG ================= */
#define SENSOR_MASK   0x1F

/* weight sensor (chu?n hon cho PID) */
static const int16_t weight[5] = {
    -200,  // trái ngoài
    -100,  // trái trong
      0,   // gi?a
     100,  // ph?i trong
     200   // ph?i ngoài
};

/* ================= STATE ================= */
static int16_t last_error = 0;
static int8_t last_dir = 1;   // 1 = ph?i, -1 = trái

/* ================= INIT ================= */
void Ip_LineSensor_Init(void)
{
    Ip_GPIO_Config_Input_PU(GPIOA, 3);
    Ip_GPIO_Config_Input_PU(GPIOA, 4);
    Ip_GPIO_Config_Input_PU(GPIOA, 5);
    Ip_GPIO_Config_Input_PU(GPIOB, 12);
    Ip_GPIO_Config_Input_PU(GPIOB, 13);
}

/* ================= READ RAW ================= */
uint8_t Ip_LineSensor_ReadRaw(void)
{
    uint8_t d = 0;

    d |= Ip_GPIO_Read(GPIOA, 3)  << 0;
    d |= Ip_GPIO_Read(GPIOA, 4)  << 1;
    d |= Ip_GPIO_Read(GPIOA, 5)  << 2;
    d |= Ip_GPIO_Read(GPIOB, 12) << 3;
    d |= Ip_GPIO_Read(GPIOB, 13) << 4;

    /* active low */
    return (~d) & SENSOR_MASK;
}

/* ================= GET ERROR ================= */
int16_t Ip_LineSensor_GetError(void)
{
    uint8_t s = Ip_LineSensor_ReadRaw();

    int32_t sum = 0;
    int16_t cnt = 0;

    /* tính tr?ng tâm line */
    for (int i = 0; i < 5; i++)
    {
        if (s & (1 << i))
        {
            sum += weight[i];
            cnt++;
        }
    }

    /* ================= M?T LINE ================= */
    if (cnt == 0)
    {
        /* tìm l?i theo hu?ng cu?i */
        return (last_dir > 0) ? 180: -180;
    }

    int16_t error = (int16_t)(sum / cnt);

    /* c?p nh?t tr?ng thái */
    last_error = error;

    if (error > 0) last_dir = 1;
    else if (error < 0) last_dir = -1;

    return error;
}

/* ================= SUPPORT ================= */
int8_t Ip_LineSensor_GetLastDir(void)
{
    return last_dir;
}

/* ================= RESET ================= */
void Ip_LineSensor_Reset(void)
{
    last_error = 0;
    last_dir = 1;
}