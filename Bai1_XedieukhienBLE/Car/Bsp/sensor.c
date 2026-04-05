#include "sensor.h"
#include "gpio.h"

#define TRIG_FRONT_PORT GPIOA
#define TRIG_LEFT_PORT  GPIOA
#define TRIG_RIGHT_PORT GPIOA

#define TRIG_FRONT_PIN  0
#define TRIG_LEFT_PIN   1
#define TRIG_RIGHT_PIN  2

static volatile uint32_t rise_time[3];
static volatile uint16_t distance[3];

static void TIM4_Init_1us(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    TIM4->PSC = 72 - 1;     // 1MHz = 1us
    TIM4->ARR = 0xFFFF;
    TIM4->CNT = 0;
    TIM4->CR1 |= TIM_CR1_CEN;
}

static void EXTI_Config(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    /* PB6 PB7 PB8 input floating */
    GPIOB->CRL &= ~((0xF << 24) | (0xF << 28));
    GPIOB->CRL |=  ((0x4 << 24) | (0x4 << 28));

    GPIOB->CRH &= ~(0xF << 0);
    GPIOB->CRH |=  (0x4 << 0);

    /* map EXTI */
    AFIO->EXTICR[1] |= AFIO_EXTICR2_EXTI6_PB |
                       AFIO_EXTICR2_EXTI7_PB;

    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI8_PB;

    EXTI->IMR  |= EXTI_IMR_MR6 | EXTI_IMR_MR7 | EXTI_IMR_MR8;
    EXTI->RTSR |= EXTI_RTSR_TR6 | EXTI_RTSR_TR7 | EXTI_RTSR_TR8;
    EXTI->FTSR |= EXTI_FTSR_TR6 | EXTI_FTSR_TR7 | EXTI_FTSR_TR8;

    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void Sensor_Init(void)
{
    GPIO_Config_Output(TRIG_FRONT_PORT, TRIG_FRONT_PIN);
    GPIO_Config_Output(TRIG_LEFT_PORT, TRIG_LEFT_PIN);
    GPIO_Config_Output(TRIG_RIGHT_PORT, TRIG_RIGHT_PIN);

    TIM4_Init_1us();
    EXTI_Config();
}

void Sensor_Trigger_All(void)
{
    GPIO_Write_Pin(TRIG_FRONT_PORT, TRIG_FRONT_PIN, 1);
    GPIO_Write_Pin(TRIG_LEFT_PORT, TRIG_LEFT_PIN, 1);
    GPIO_Write_Pin(TRIG_RIGHT_PORT, TRIG_RIGHT_PIN, 1);

    for(volatile int i = 0; i < 200; i++); // ~10us

    GPIO_Write_Pin(TRIG_FRONT_PORT, TRIG_FRONT_PIN, 0);
    GPIO_Write_Pin(TRIG_LEFT_PORT, TRIG_LEFT_PIN, 0);
    GPIO_Write_Pin(TRIG_RIGHT_PORT, TRIG_RIGHT_PIN, 0);
}

void EXTI9_5_IRQHandler(void)
{
    uint32_t now = TIM4->CNT;

    /* FRONT PB6 */
    if(EXTI->PR & EXTI_PR_PR6)
    {
        if(GPIO_Read(GPIOB, 6))
        {
            rise_time[0] = now;
        }
        else
        {
            distance[0] = (now - rise_time[0]) / 58;
        }
        EXTI->PR = EXTI_PR_PR6;
    }

    /* LEFT PB7 */
    if(EXTI->PR & EXTI_PR_PR7)
    {
        if(GPIO_Read(GPIOB, 7))
        {
            rise_time[1] = now;
        }
        else
        {
            distance[1] = (now - rise_time[1]) / 58;
        }
        EXTI->PR = EXTI_PR_PR7;
    }

    /* RIGHT PB8 */
    if(EXTI->PR & EXTI_PR_PR8)
    {
        if(GPIO_Read(GPIOB, 8))
        {
            rise_time[2] = now;
        }
        else
        {
            distance[2] = (now - rise_time[2]) / 58;
        }
        EXTI->PR = EXTI_PR_PR8;
    }
}

sensor_data_t Sensor_GetData(void)
{
    sensor_data_t data;

    data.front = distance[0];
    data.left  = distance[1];
    data.right = distance[2];

    return data;
}