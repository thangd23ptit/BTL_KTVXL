#include "ip_pwm.h"

/**
 * @brief Khoi tao PWM su dung TIM1
 * @param None
 * @retval None
 */
void Ip_PWM_Init(void){
    // bat clock GPIOA va TIM1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // cau hinh PA8 (CH1) va PA11 (CH4) la AF push-pull
    GPIOA->CRH &= ~((0xF << 0) | (0xF << 12));
    GPIOA->CRH |=  ((0xB << 0) | (0xB << 12));

    // cau hinh timer
    TIM1->PSC = 72 - 1;      // 1 MHz
    TIM1->ARR = 1000 - 1;    // chu ky 1ms

    TIM1->CCMR1 = 0;
    TIM1->CCMR2 = 0;
    TIM1->CCER  = 0;

    // PWM mode 1 cho CH1 va CH4
    TIM1->CCMR1 |= (6 << 4) | (1 << 3);
    TIM1->CCMR2 |= (6 << 12) | (1 << 11);

    // enable output
    TIM1->CCER |= TIM_CCER_CC1E;
    TIM1->CCER |= TIM_CCER_CC4E;

    // duty ban dau
    TIM1->CCR1 = 0;
    TIM1->CCR4 = 0;

    // enable main output (TIM1 la advanced timer)
    TIM1->BDTR |= TIM_BDTR_MOE;

    TIM1->EGR = TIM_EGR_UG;
    TIM1->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;
}

/**
 * @brief Set duty PWM cho ben trai (CH1)
 * @param val Gia tri duty (0-1000)
 * @retval None
 */
void Ip_PWM_SetLeft(uint16_t val){
    if(val > 1000) val = 1000;
    TIM1->CCR1 = val;
}

/**
 * @brief Set duty PWM cho ben phai (CH4)
 * @param val Gia tri duty (0-1000)
 * @retval None
 */
void Ip_PWM_SetRight(uint16_t val){
    if(val > 1000) val = 1000;
    TIM1->CCR4 = val;
}