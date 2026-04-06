#include "stm32f10x.h"
#include <stdint.h>

int main(void)
{
    uint8_t rx;

    /* Clock GPIOC + USART2 + GPIOA */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |
                           RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    GPIO_InitTypeDef gpio;
    USART_InitTypeDef uart;

    /* PC13 output LED */
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &gpio);

    /* PA2 TX */
    gpio.GPIO_Pin = GPIO_Pin_2;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    /* PA3 RX */
    gpio.GPIO_Pin = GPIO_Pin_3;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpio);

    /* USART2 config */
    uart.USART_BaudRate = 9600;
    uart.USART_WordLength = USART_WordLength_8b;
    uart.USART_StopBits = USART_StopBits_1;
    uart.USART_Parity = USART_Parity_No;
    uart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &uart);

    USART_Cmd(USART2, ENABLE);

    /* LED off */
    GPIO_SetBits(GPIOC, GPIO_Pin_13);

    while (1)
		{
				if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)
				{
						rx = USART_ReceiveData(USART2);

						USART_SendData(USART2, rx);
						while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

						if (rx == 'B')
						{
								GPIO_ResetBits(GPIOC, GPIO_Pin_13);
						}
						else if (rx == 'T')
						{
								GPIO_SetBits(GPIOC, GPIO_Pin_13);
						}
				}
		}
}