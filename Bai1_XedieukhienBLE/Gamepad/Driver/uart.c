#include "uart.h"

static volatile char rx_buffer[UART_RX_BUFFER_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;

void UART1_Init(uint32_t baudrate){
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

void USART1_IRQHandler(void){
    if(USART1->SR & USART_SR_RXNE){
        char data = USART1->DR;
        uint8_t next = (rx_head + 1) % UART_RX_BUFFER_SIZE;
        if(next != rx_tail){
            rx_buffer[rx_head] = data;
            rx_head = next;
        }
    }
}

uint8_t UART1_Available(void){
    return (rx_head != rx_tail);
}

char UART1_ReadBuffer(void){
    char data = 0;
    if(rx_head != rx_tail){
        data = rx_buffer[rx_tail];
        rx_tail = (rx_tail + 1) % UART_RX_BUFFER_SIZE;
    }
    return data;
}

void UART1_SendChar(char c){
    while(!(USART1->SR & USART_SR_TXE));
    USART1->DR = c;
}

void UART1_SendString(char *str){
    while(*str){
        UART1_SendChar(*str++);
    }
}

void UART1_SendNumber(int32_t num){
    char buffer[12];
    uint8_t i = 0;
    if (num == 0){
        UART1_SendChar('0');
        return;
    }
    if (num < 0){
        UART1_SendChar('-');
        num = -num;
    }
    while (num > 0){
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }
    while (i > 0){
        UART1_SendChar(buffer[--i]);
    }
}