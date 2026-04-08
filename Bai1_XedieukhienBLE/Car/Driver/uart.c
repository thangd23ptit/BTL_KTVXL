#include "uart.h"

#define UART_RX_BUFFER_SIZE 64

static volatile uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;
//fix cung ham khoi tao uart doc theo ngat 
void UART1_Init(uint32_t baudrate){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);
    USART1->BRR = SystemCoreClock / baudrate;
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;
    NVIC_SetPriority(USART1_IRQn, 1);
    NVIC_EnableIRQ(USART1_IRQn);
    rx_head = 0;
    rx_tail = 0;
}
//ham gui 1 ky tu
void UART1_SendChar(char c){
    while(!(USART1->SR & USART_SR_TXE));
    USART1->DR = (uint8_t)c;
}
//ham gui 1 chuoi
void UART1_SendString(const char *str){
    while(*str){
        UART1_SendChar(*str++);
    }
}
//ham kiem tra xem con ki tu duoc gui khong
uint8_t UART1_Available(void){
    return (rx_head != rx_tail);
}
// ham doc ki tu 
char UART1_ReadChar(void){
    char c = 0;
    if(rx_head != rx_tail){
        c = rx_buffer[rx_tail];
        rx_tail = (rx_tail + 1) % UART_RX_BUFFER_SIZE;
    }
    return c;
}
// khoi tao ngat doc ki tu
void USART1_IRQHandler(void){
    if(USART1->SR & USART_SR_RXNE){
        uint8_t data = (uint8_t)USART1->DR;
        uint8_t next = (rx_head + 1) % UART_RX_BUFFER_SIZE;
        if(next != rx_tail){
            rx_buffer[rx_head] = data;
            rx_head = next;
        }
    }
    if(USART1->SR & USART_SR_ORE){
        volatile uint8_t dummy = USART1->DR;
        (void)dummy;
    }
}