#include "uart.h"

static volatile char rx_buffer[UART_BUFFER_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;
void UART_Init(void)
{
    GPIO_InitTypeDef gpio;
    USART_InitTypeDef uart;
    NVIC_InitTypeDef nvic;

    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOA |
        RCC_APB2Periph_USART1 |
        RCC_APB2Periph_AFIO,
        ENABLE
    );

    //TX
    gpio.GPIO_Pin = GPIO_Pin_9;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    //RX
    gpio.GPIO_Pin = GPIO_Pin_10;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio);

    uart.USART_BaudRate = 9600;
    uart.USART_WordLength = USART_WordLength_8b;
    uart.USART_StopBits = USART_StopBits_1;
    uart.USART_Parity = USART_Parity_No;
    uart.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_Init(USART1, &uart);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    nvic.NVIC_IRQChannel = USART1_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        char data = USART_ReceiveData(USART1);

        uint8_t next = (rx_head + 1) % UART_BUFFER_SIZE;

        if(next != rx_tail) // tranh overflow
        {
            rx_buffer[rx_head] = data;
            rx_head = next;
        }
    }
}

uint8_t UART_Available(void)
{
    return (rx_head != rx_tail);
}

char UART_Read(void)
{
    char data = 0;

    if(rx_head == rx_tail) return 0;

    data = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % UART_BUFFER_SIZE;

    return data;
}

void UART_SendChar(char c)
{
    USART_SendData(USART1, c);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void UART_SendString(char *str)
{
    while(*str)
    {
        UART_SendChar(*str++);
    }
}