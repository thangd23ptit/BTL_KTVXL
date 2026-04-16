#include "ip_sensor.h"
#include "ip_gpio.h"
#include "ip_timer.h"

#define TRIG_PORT   GPIOA
#define TRIG_PIN    0

#define ECHO_PORT   GPIOB
#define ECHO_PIN    6

static volatile uint32_t rise_time = 0;
static volatile uint16_t distance_cm = 0;

/**
 * @brief Cau hinh EXTI cho chan ECHO
 * @param None
 * @retval None
 */
static void Ip_EXTI_Config(void){
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // PB6 input floating
    GPIOB->CRL &= ~(0xF << (6 * 4));
    GPIOB->CRL |=  (0x4 << (6 * 4));

    // map EXTI6 -> PB6
    AFIO->EXTICR[1] &= ~AFIO_EXTICR2_EXTI6;
    AFIO->EXTICR[1] |=  AFIO_EXTICR2_EXTI6_PB;

    // enable interrupt
    EXTI->IMR  |= EXTI_IMR_MR6;
    EXTI->RTSR |= EXTI_RTSR_TR6;
    EXTI->FTSR |= EXTI_FTSR_TR6;

    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

/**
 * @brief Khoi tao cam bien sieu am
 * @param None
 * @retval None
 */
void Ip_Sensor_Init(void){
    Ip_GPIO_Config_Output(TRIG_PORT, TRIG_PIN);
    Ip_GPIO_Write_Pin(TRIG_PORT, TRIG_PIN, 0);

    Ip_TIM4_Init_1us();
    Ip_EXTI_Config();
}

/**
 * @brief Phat xung trigger 10us
 * @param None
 * @retval None
 */
void Ip_Sensor_Trigger(void){
    Ip_GPIO_Write_Pin(TRIG_PORT, TRIG_PIN, 1);
    Ip_Delay_us(10);
    Ip_GPIO_Write_Pin(TRIG_PORT, TRIG_PIN, 0);
}

/**
 * @brief Lay khoang cach truoc (cm)
 * @param None
 * @retval Khoang cach (cm)
 */
uint16_t Ip_Sensor_GetFront(void){
    return distance_cm;
}

/**
 * @brief Xu ly ngat EXTI cho ECHO
 * @param None
 * @retval None
 */
void EXTI9_5_IRQHandler(void){
    if(EXTI->PR & EXTI_PR_PR6){
        uint32_t now = TIM4->CNT;

        if(Ip_GPIO_Read(ECHO_PORT, ECHO_PIN)){
            // canh len
            rise_time = now;
        }
        else{
            // canh xuong
            uint32_t pulse_width;

            if(now >= rise_time) pulse_width = now - rise_time;
            else pulse_width = (0xFFFF - rise_time) + now;

            // doi sang cm
            distance_cm = pulse_width / 58;
        }

        EXTI->PR = EXTI_PR_PR6;
    }
}