#include "sensor.h"
#include "gpio.h"
#include "timer.h"

/* ================= PIN CONFIG ================= */
#define TRIG_PORT   GPIOA
#define TRIG_PIN    0

#define ECHO_PORT   GPIOB
#define ECHO_PIN    6

/* ================= PRIVATE VAR ================= */
static volatile uint32_t rise_time = 0;
static volatile uint16_t distance_cm = 0;

/* ================= EXTI CONFIG ================= */
static void EXTI_Config(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    /* PB6 input floating */
    GPIOB->CRL &= ~(0xF << (6 * 4));
    GPIOB->CRL |=  (0x4 << (6 * 4));

    /* EXTI6 -> PB6 */
    AFIO->EXTICR[1] &= ~AFIO_EXTICR2_EXTI6;
    AFIO->EXTICR[1] |=  AFIO_EXTICR2_EXTI6_PB;

    /* rising + falling */
    EXTI->IMR  |= EXTI_IMR_MR6;
    EXTI->RTSR |= EXTI_RTSR_TR6;
    EXTI->FTSR |= EXTI_FTSR_TR6;

    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

/* ================= PUBLIC ================= */
void Sensor_Init(void)
{
    GPIO_Config_Output(TRIG_PORT, TRIG_PIN);
    GPIO_Write_Pin(TRIG_PORT, TRIG_PIN, 0);

    TIM4_Init_1us();
    EXTI_Config();
}

/* trigger 10us pulse */
void Sensor_Trigger(void)
{
    GPIO_Write_Pin(TRIG_PORT, TRIG_PIN, 1);
    Delay_us(10);
    GPIO_Write_Pin(TRIG_PORT, TRIG_PIN, 0);
}

uint16_t Sensor_GetFront(void)
{
    return distance_cm;
}

/* ================= INTERRUPT ================= */
void EXTI9_5_IRQHandler(void)
{
    if(EXTI->PR & EXTI_PR_PR6)
    {
        uint32_t now = TIM4->CNT;

        if(GPIO_Read(ECHO_PORT, ECHO_PIN))
        {
            /* rising edge */
            rise_time = now;
        }
        else
        {
            /* falling edge */
            uint32_t pulse_width;

            if(now >= rise_time)
                pulse_width = now - rise_time;
            else
                pulse_width = (0xFFFF - rise_time) + now;

            distance_cm = pulse_width / 58;
        }

        EXTI->PR = EXTI_PR_PR6;
    }
}