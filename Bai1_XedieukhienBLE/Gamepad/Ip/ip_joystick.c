#include "ip_joystick.h"
#include "ip_adc.h"

/**
 * @brief Khoi tao joystick
 * @param joy Con tro cau truc joystick
 * @param x_channel Kenh ADC truc X
 * @param y_channel Kenh ADC truc Y
 * @retval None
 */
void Ip_Joystick_Init(Joystick_t *joy, uint8_t x_channel, uint8_t y_channel)
{
    joy->x_channel = x_channel;
    joy->y_channel = y_channel;
    joy->center = 2048;
}

/**
 * @brief Doc gia tri truc X joystick
 * @param joy Con tro cau truc joystick
 * @retval Gia tri ADC truc X
 */
uint16_t Ip_Joystick_ReadX(Joystick_t *joy)
{
    Ip_ADC1_Init_Single(joy->x_channel);
    return Ip_ADC1_Read();
}

/**
 * @brief Doc gia tri truc Y joystick
 * @param joy Con tro cau truc joystick
 * @retval Gia tri ADC truc Y
 */
uint16_t Ip_Joystick_ReadY(Joystick_t *joy)
{
    Ip_ADC1_Init_Single(joy->y_channel);
    return Ip_ADC1_Read();
}

/**
 * @brief Lay do lech truc X so voi tam
 * @param joy Con tro cau truc joystick
 * @retval Do lech X (co the am hoac duong)
 */
int16_t Ip_Joystick_GetXOffset(Joystick_t *joy)
{
    return (int16_t)Ip_Joystick_ReadX(joy) - joy->center;
}

/**
 * @brief Lay do lech truc Y so voi tam
 * @param joy Con tro cau truc joystick
 * @retval Do lech Y (co the am hoac duong)
 */
int16_t Ip_Joystick_GetYOffset(Joystick_t *joy)
{
    return (int16_t)Ip_Joystick_ReadY(joy) - joy->center;
}