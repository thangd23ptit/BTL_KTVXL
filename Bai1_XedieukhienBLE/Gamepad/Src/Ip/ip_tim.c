#include "ip_tim.h"

/**
 * @brief Khoi tao TIM2 tao tre 1ms
 * @param None
 * @retval None
 */
void Ip_TIM2_Init_1ms(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    TIM2->PSC = 7200 - 1;
    TIM2->ARR = 10 - 1;
    TIM2->CNT = 0;

    TIM2->EGR |= TIM_EGR_UG;
    TIM2->SR &= ~TIM_SR_UIF;
    TIM2->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief Delay theo don vi mili giay bang TIM2
 * @param ms So mili giay can delay
 * @retval None
 */
void Ip_Delay_ms(uint16_t ms)
{
    while(ms--)
    {
        TIM2->CNT = 0;
        TIM2->SR &= ~TIM_SR_UIF;

        while(!(TIM2->SR & TIM_SR_UIF));
    }
}