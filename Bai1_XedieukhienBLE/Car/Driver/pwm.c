#include "pwm.h"

void PWM_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    /* PA8 CH1, PA11 CH4 */
    GPIOA->CRH &= ~((0xF << 0) | (0xF << 12));
    GPIOA->CRH |=  ((0xB << 0) | (0xB << 12));

    TIM1->PSC = 72 - 1;
    TIM1->ARR = 1000 - 1;

    TIM1->CCMR1 = 0;
    TIM1->CCMR2 = 0;
    TIM1->CCER  = 0;

    /* CH1 */
    TIM1->CCMR1 |= (6 << 4) | (1 << 3);

    /* CH4 */
    TIM1->CCMR2 |= (6 << 12) | (1 << 11);

    TIM1->CCER |= TIM_CCER_CC1E;
    TIM1->CCER |= TIM_CCER_CC4E;

    TIM1->CCR1 = 0;
    TIM1->CCR4 = 0;

    TIM1->BDTR |= TIM_BDTR_MOE;
    TIM1->EGR = TIM_EGR_UG;
    TIM1->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;
}

void PWM_SetLeft(uint16_t duty)
{
    if(duty > 1000) duty = 1000;
    TIM1->CCR1 = duty;
}

void PWM_SetRight(uint16_t duty)
{
    if(duty > 1000) duty = 1000;
    TIM1->CCR4 = duty;
}