#include "ip_timer.h"

static volatile uint32_t g_tick_ms = 0;

/**
 * @brief Khoi tao TIM3 tao ngat moi 1ms
 * @param None
 * @retval None
 */
void Ip_TIM3_Init_1ms(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3->PSC = 7200 - 1;   // 72MHz / 7200 = 10kHz
    TIM3->ARR = 10 - 1;     // 10kHz / 10 = 1kHz (1ms)

    TIM3->CNT = 0;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1  |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM3_IRQn);
}

/**
 * @brief Ham xu ly ngat TIM3 moi 1ms
 * @param None
 * @retval None
 */
void TIM3_IRQHandler(void)
{
    if(TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF;
        g_tick_ms++;
    }
}

/**
 * @brief Lay thoi gian dem (ms)
 * @param None
 * @retval Gia tri thoi gian ms
 */
uint32_t Ip_GetTickMs(void){
    return g_tick_ms;
}

/**
 * @brief Delay theo mili giay
 * @param ms Thoi gian delay (ms)
 * @retval None
 */
void Ip_Delay_ms(uint32_t ms){
    uint32_t start = Ip_GetTickMs();
    while((Ip_GetTickMs() - start) < ms);
}

/**
 * @brief Khoi tao TIM4 dem micro giay
 * @param None
 * @retval None
 */
void Ip_TIM4_Init_1us(void){
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    TIM4->PSC = 72 - 1;     // 1MHz -> 1us
    TIM4->ARR = 0xFFFF;

    TIM4->CNT = 0;
    TIM4->CR1 |= TIM_CR1_CEN;
}

/**
 * @brief Delay theo micro giay
 * @param us Thoi gian delay (us)
 * @retval None
 */
void Ip_Delay_us(uint16_t us){
    TIM4->CNT = 0;
    while(TIM4->CNT < us);
}