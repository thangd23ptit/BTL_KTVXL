#include "ip_bluetooth.h"
#include "ip_uart.h"

/**
 * @brief Khoi tao module Bluetooth (su dung UART1)
 * @param baudrate Toc do truyen UART
 * @retval None
 */
void Ip_Bluetooth_Init(uint32_t baudrate)
{
    Ip_UART1_Init(baudrate);
}

/**
 * @brief Gui 1 ky tu qua Bluetooth
 * @param c Ky tu can gui
 * @retval None
 */
void Ip_Bluetooth_SendChar(char c)
{
    Ip_UART1_SendChar(c);
}

/**
 * @brief Gui chuoi ky tu qua Bluetooth
 * @param str Chuoi null-terminated
 * @retval None
 */
void Ip_Bluetooth_SendString(char *str)
{
    Ip_UART1_SendString(str);
}

/**
 * @brief Kiem tra du lieu nhan Bluetooth
 * @param None
 * @retval 1 neu co du lieu, 0 neu khong
 */
uint8_t Ip_Bluetooth_Available(void)
{
    return Ip_UART1_Available();
}

/**
 * @brief Doc 1 ky tu tu Bluetooth
 * @param None
 * @retval Ky tu nhan duoc
 */
char Ip_Bluetooth_Read(void)
{
    return Ip_UART1_ReadBuffer();
}

/**
 * @brief Gui so nguyen qua Bluetooth
 * @param num So can gui
 * @retval None
 */
void Ip_Bluetooth_SendNum(int32_t num)
{
    Ip_UART1_SendNumber(num);
}