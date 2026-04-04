#include "uart.h"

void UART1_Init(uint32_t baudrate)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // PA9 = TX (AF Push Pull, 50MHz)
    GPIOA->CRH &= (uint16_t)~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    // PA10 = RX (Input floating)
    GPIOA->CRH &= (uint16_t)~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    USART1->BRR = (uint16_t)72000000 / baudrate;
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE;
    USART1->CR1 |= USART_CR1_UE;
}

void UART1_SendChar(char c)
{
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = c;
}

void UART1_SendString(const char *str)
{
    while (*str)
    {
        UART1_SendChar(*str++);
    }
}

void UART1_SendBuffer(uint8_t *data, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
        while (!(USART1->SR & USART_SR_TXE));
        USART1->DR = data[i];
    }
}

