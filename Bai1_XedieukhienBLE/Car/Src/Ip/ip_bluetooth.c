#include "ip_bluetooth.h"
#include "ip_uart.h"

/**
 * @brief Khoi tao Bluetooth (su dung UART1)
 * @param baudrate Toc do baud
 * @retval None
 */
void Ip_Bluetooth_Init(uint32_t baudrate){
    Ip_UART1_Init(baudrate);
}

/**
 * @brief Kiem tra co du lieu tu Bluetooth khong
 * @param None
 * @retval 1 neu co du lieu, 0 neu khong
 */
uint8_t Ip_Bluetooth_Available(void){
    return Ip_UART1_Available();
}

/**
 * @brief Doc 1 ky tu tu Bluetooth
 * @param None
 * @retval Ky tu doc duoc
 */
char Ip_Bluetooth_ReadChar(void){
    return Ip_UART1_ReadChar();
}

/**
 * @brief Gui 1 ky tu qua Bluetooth
 * @param c Ky tu can gui
 * @retval None
 */
void Ip_Bluetooth_SendChar(char c){
    Ip_UART1_SendChar(c);
}

/**
 * @brief Gui 1 chuoi qua Bluetooth
 * @param str Chuoi can gui
 * @retval None
 */
void Ip_Bluetooth_SendString(const char *str){
    while(*str){
        Ip_UART1_SendChar(*str++);
    }
}