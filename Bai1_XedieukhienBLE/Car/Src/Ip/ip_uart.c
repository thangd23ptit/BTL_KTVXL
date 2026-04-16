#include "ip_uart.h"

#define UART_RX_BUFFER_SIZE 64

static volatile uint8_t rx_buffer[UART_RX_BUFFER_SIZE];
static volatile uint8_t rx_head = 0;
static volatile uint8_t rx_tail = 0;

/**
 * @brief Khoi tao UART1 che do RX interrupt
 * @param baudrate Toc do baud (vd: 9600, 115200)
 * @retval None
 */
void Ip_UART1_Init(uint32_t baudrate){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // PA9 TX (AF push-pull), PA10 RX (input floating)
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    USART1->BRR = SystemCoreClock / baudrate;

    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;

    // enable interrupt USART1
    NVIC->IP[USART1_IRQn] = (1 << 4);
    NVIC->ISER[USART1_IRQn >> 5] = (1 << (USART1_IRQn & 0x1F));

    rx_head = 0;
    rx_tail = 0;
}

/**
 * @brief Gui 1 ky tu qua UART1
 * @param c Ky tu can gui
 * @retval None
 */
void Ip_UART1_SendChar(char c){
    while(!(USART1->SR & USART_SR_TXE));
    USART1->DR = (uint8_t)c;
}

/**
 * @brief Gui 1 chuoi qua UART1
 * @param str Con tro toi chuoi
 * @retval None
 */
void Ip_UART1_SendString(const char *str){
    while(*str){
        Ip_UART1_SendChar(*str++);
    }
}

/**
 * @brief Kiem tra buffer co du lieu khong
 * @param None
 * @retval 1 neu co du lieu, 0 neu khong
 */
uint8_t Ip_UART1_Available(void){
    return (rx_head != rx_tail);
}

/**
 * @brief Doc 1 ky tu tu buffer UART
 * @param None
 * @retval Ky tu doc duoc
 */
char Ip_UART1_ReadChar(void){
    char c = 0;

    if(rx_head != rx_tail){
        c = rx_buffer[rx_tail];
        rx_tail = (rx_tail + 1) % UART_RX_BUFFER_SIZE;
    }

    return c;
}

/**
 * @brief Ham xu ly ngat UART1 RX
 * @param None
 * @retval None
 */
void USART1_IRQHandler(void){
    if(USART1->SR & USART_SR_RXNE){
        uint8_t data = (uint8_t)USART1->DR;

        uint8_t next = (rx_head + 1) % UART_RX_BUFFER_SIZE;
        if(next != rx_tail){
            rx_buffer[rx_head] = data;
            rx_head = next;
        }
    }

    // xu ly overrun
    if(USART1->SR & USART_SR_ORE){
        volatile uint8_t dummy = USART1->DR;
        (void)dummy;
    }
}

/**
 * @brief Gui so nguyen duong qua UART
 * @param num Gia tri can gui
 * @retval None
 */
void Ip_UART1_SendNum(uint16_t num)
{
    char buf[6];
    int i = 0;

    if(num == 0)
    {
        Ip_UART1_SendChar('0');
        return;
    }

    while(num > 0)
    {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    while(i--)
    {
        Ip_UART1_SendChar(buf[i]);
    }
}