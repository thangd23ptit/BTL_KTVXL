#include "pwm.h"

void PWM_Init(void)
{
    GPIO_InitTypeDef gpio;
    TIM_TimeBaseInitTypeDef tim;
    TIM_OCInitTypeDef oc;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    gpio.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    TIM_TimeBaseStructInit(&tim);
    tim.TIM_Prescaler = 72 - 1;      
    tim.TIM_Period = 1000 - 1;      
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &tim);

    TIM_OCStructInit(&oc);
    oc.TIM_OCMode = TIM_OCMode_PWM1;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_OCPolarity = TIM_OCPolarity_High;
    oc.TIM_Pulse = 0;   

    TIM_OC3Init(TIM2, &oc);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC4Init(TIM2, &oc);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_GenerateEvent(TIM2, TIM_EventSource_Update);
    TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetDuty_Left(uint16_t duty)
{
    if (duty > 999) duty = 999;
    TIM_SetCompare3(TIM2, duty);   
}

void PWM_SetDuty_Right(uint16_t duty)
{
    if (duty > 999) duty = 999;
    TIM_SetCompare4(TIM2, duty);   
}