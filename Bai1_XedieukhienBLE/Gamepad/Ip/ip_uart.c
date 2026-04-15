#include "ip_uart.h"

/**
 * @brief RX ring buffer UART1
 */
static volatile char uart1_rx_buffer[IP_UART_RX_BUFFER_SIZE];
static volatile uint8_t uart1_rx_head = 0;
static volatile uint8_t uart1_rx_tail = 0;

/**
 * @brief Khoi tao UART1
 * @param baudrate Toc do truyen UART (vd: 9600, 115200)
 * @retval None
 */
void Ip_UART1_Init(uint32_t baudrate)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    USART1->BRR = 72000000 / baudrate;

    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;

    USART1->CR1 |= USART_CR1_RXNEIE;
    NVIC_EnableIRQ(USART1_IRQn);

    USART1->CR1 |= USART_CR1_UE;
}

/**
 * @brief Ham ngat UART1 nhan du lieu RX
 * @param None
 * @retval None
 */
void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE)
    {
        char data = (char)USART1->DR;

        uint8_t next_head = (uart1_rx_head + 1) % IP_UART_RX_BUFFER_SIZE;

        if (next_head != uart1_rx_tail)
        {
            uart1_rx_buffer[uart1_rx_head] = data;
            uart1_rx_head = next_head;
        }
    }
}

/**
 * @brief Kiem tra du lieu trong buffer RX
 * @param None
 * @retval 1 neu co du lieu, 0 neu khong
 */
uint8_t Ip_UART1_Available(void)
{
    return (uart1_rx_head != uart1_rx_tail);
}

/**
 * @brief Doc 1 byte tu buffer RX UART1
 * @param None
 * @retval Ky tu nhan duoc, 0 neu rong
 */
char Ip_UART1_ReadBuffer(void)
{
    char data = 0;

    if (uart1_rx_head != uart1_rx_tail)
    {
        data = uart1_rx_buffer[uart1_rx_tail];
        uart1_rx_tail = (uart1_rx_tail + 1) % IP_UART_RX_BUFFER_SIZE;
    }

    return data;
}

/**
 * @brief Gui 1 ky tu qua UART1
 * @param c Ky tu can gui
 * @retval None
 */
void Ip_UART1_SendChar(char c)
{
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = c;
}

/**
 * @brief Gui chuoi ky tu qua UART1
 * @param str Chuoi null-terminated
 * @retval None
 */
void Ip_UART1_SendString(char *str)
{
    while (*str)
    {
        Ip_UART1_SendChar(*str++);
    }
}

/**
 * @brief Gui so nguyen 32-bit qua UART1
 * @param num So can gui
 * @retval None
 */
void Ip_UART1_SendNumber(int32_t num)
{
    char buffer[12];
    uint8_t i = 0;

    if (num == 0)
    {
        Ip_UART1_SendChar('0');
        return;
    }

    if (num < 0)
    {
        Ip_UART1_SendChar('-');
        num = -num;
    }

    while (num > 0)
    {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i > 0)
    {
        Ip_UART1_SendChar(buffer[--i]);
    }
}