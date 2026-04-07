#include "stm32f10x.h"
#include <stdio.h>

// ================= UART SEND =================
void UART_SendString(char *str)
{
    while(*str)
    {
        USART_SendData(USART1, *str++);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}

// ================= SEND FRAME =================
void Send_Frame(char dir, uint16_t speed)
{
    char tx_buffer[30];
    sprintf(tx_buffer, "$M,%c,%d#", dir, speed);
    UART_SendString(tx_buffer);
}

// ================= DELAY =================
void delay_ms(uint32_t ms)
{
    for(uint32_t i = 0; i < ms * 8000; i++)
        __NOP();
}

// ================= USART1 =================
void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                           RCC_APB2Periph_USART1, ENABLE);

    // PA9 TX
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // PA10 RX
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStruct);
    USART_Cmd(USART1, ENABLE);
}

// ================= ADC =================
void ADC_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    ADC_InitTypeDef ADC_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                           RCC_APB2Periph_ADC1, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfChannel = 1;

    ADC_Init(ADC1, &ADC_InitStruct);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));

    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

uint16_t ADC_Read(uint8_t channel)
{
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_55Cycles5);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

    return ADC_GetConversionValue(ADC1);
}

// ================= MODE SWITCH PA2 =================
void Mode_Switch_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// ================= SPEED CURVE =================
uint16_t Calculate_Speed(uint16_t adc)
{
    uint16_t diff;

    diff = (adc > 2048) ? (adc - 2048) : (2048 - adc);

    // dead zone
    if(diff < 300) return 0;

    diff -= 300;

    if(diff > 1300) diff = 1300;

    // curve m?m
    return (diff * diff * 1000) / (1300 * 1300);
}

// ================= MAIN =================
int main(void)
{
    uint16_t x_val, y_val, speed;

    USART1_Config();
    ADC_Config();
    Mode_Switch_Config();

    while(1)
    {
        // ===== AUTO MODE =====
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == Bit_RESET)
        {
            Send_Frame('S', 0);
            Delay_ms(100);
            continue;
        }

        // ===== CONTROL MODE =====
        x_val = ADC_Read(ADC_Channel_0);
        y_val = ADC_Read(ADC_Channel_1);

        if(y_val > 2350)
        {
            speed = Calculate_Speed(y_val);
            Send_Frame('F', speed);
        }
        else if(y_val < 1750)
        {
            speed = Calculate_Speed(y_val);
            Send_Frame('B', speed);
        }
        else if(x_val > 2350)
        {
            speed = Calculate_Speed(x_val);
            Send_Frame('R', speed);
        }
        else if(x_val < 1750)
        {
            speed = Calculate_Speed(x_val);
            Send_Frame('L', speed);
        }
        else
        {
            Send_Frame('S', 0);
        }

        delay_ms(50);
    }
}