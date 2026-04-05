#include "uart.h"

#define UART_RX_BUFFER_SIZE 64

static volatile uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;

void UART1_Init(uint32_t baudrate)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    /* PA9 TX */
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    /* PA10 RX */
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    USART1->BRR = SystemCoreClock / baudrate;

    USART1->CR1 = 0;
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;
    USART1->CR1 |= USART_CR1_RXNEIE;   // enable RX interrupt
    USART1->CR1 |= USART_CR1_UE;

    NVIC_EnableIRQ(USART1_IRQn);
}

void UART1_SendChar(char c)
{
    while(!(USART1->SR & USART_SR_TXE));
    USART1->DR = c;
}

void UART1_SendString(const char *str)
{
    while(*str)
    {
        UART1_SendChar(*str++);
    }

    while(!(USART1->SR & USART_SR_TC));
}

void UART1_SendBuffer(uint8_t *data, uint16_t len)
{
    for(uint16_t i = 0; i < len; i++)
    {
        UART1_SendChar(data[i]);
    }

    while(!(USART1->SR & USART_SR_TC));
}

uint8_t UART1_Available(void)
{
    return (rx_head != rx_tail);
}

char UART1_ReadChar(void)
{
    char c = 0;

    if(rx_head != rx_tail)
    {
        c = rx_buffer[rx_tail];
        rx_tail = (rx_tail + 1) % UART_RX_BUFFER_SIZE;
    }

    return c;
}

void USART1_IRQHandler(void)
{
    if(USART1->SR & USART_SR_RXNE)
    {
        uint8_t data = USART1->DR;
        uint8_t next = (rx_head + 1) % UART_RX_BUFFER_SIZE;

        if(next != rx_tail)
        {
            rx_buffer[rx_head] = data;
            rx_head = next;
        }
    }
}