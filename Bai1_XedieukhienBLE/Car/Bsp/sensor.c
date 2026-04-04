/* sensor.c */
#include "sensor.h"

#define MAX_DIST        200     // cm
#define TRIGGER_PERIOD  35000   // us (35ms gi?a 2 l?n trigger)

#define FRONT 0
#define LEFT  1
#define RIGHT 2

static volatile uint16_t start[3] = {0};
static volatile uint16_t width[3] = {0};
static volatile uint8_t  state[3] = {0};   // 0: ch? rising, 1: ch? falling
static uint16_t dist[3] = {MAX_DIST, MAX_DIST, MAX_DIST};

static uint8_t step = 0;
static uint32_t lastTrig = 0;

static void SR05_Trigger(GPIO_TypeDef *port, uint16_t pin)
{
    GPIO_WritePin(port, pin, 1);
    Delay_us(10);
    GPIO_WritePin(port, pin, 0);
}

void Sensor_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    // Trigger pins
    GPIO_ConfigOutput(SR05_FRONT_TRIG_PORT, SR05_FRONT_TRIG_PIN);
    GPIO_ConfigOutput(SR05_LEFT_TRIG_PORT,  SR05_LEFT_TRIG_PIN);
    GPIO_ConfigOutput(SR05_RIGHT_TRIG_PORT, SR05_RIGHT_TRIG_PIN);
    GPIO_WritePin(SR05_FRONT_TRIG_PORT, SR05_FRONT_TRIG_PIN, 0);
    GPIO_WritePin(SR05_LEFT_TRIG_PORT,  SR05_LEFT_TRIG_PIN,  0);
    GPIO_WritePin(SR05_RIGHT_TRIG_PORT, SR05_RIGHT_TRIG_PIN, 0);

    // Echo pins - Pull Down t?t hon
    GPIO_InitTypeDef gpio = {0};
    gpio.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;
    gpio.GPIO_Mode  = GPIO_Mode_IPD;           // Pull-down
    GPIO_Init(GPIOA, &gpio);

    gpio.GPIO_Pin   = GPIO_Pin_0;
    GPIO_Init(GPIOB, &gpio);

    // Timer config (1us resolution)
    TIM_TimeBaseInitTypeDef tim = {0};
    tim.TIM_Prescaler     = 71;
    tim.TIM_Period        = 0xFFFF;
    tim.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &tim);

    // Input Capture cho 3 kênh
    TIM_ICInitTypeDef ic = {0};
    ic.TIM_ICPolarity   = TIM_ICPolarity_Rising;
    ic.TIM_ICSelection  = TIM_ICSelection_DirectTI;
    ic.TIM_ICPrescaler  = TIM_ICPSC_DIV1;
    ic.TIM_ICFilter     = 0;

    ic.TIM_Channel = TIM_Channel_1; TIM_ICInit(TIM3, &ic);
    ic.TIM_Channel = TIM_Channel_2; TIM_ICInit(TIM3, &ic);
    ic.TIM_Channel = TIM_Channel_3; TIM_ICInit(TIM3, &ic);

    TIM_ITConfig(TIM3, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3, ENABLE);

    NVIC_InitTypeDef nvic = {0};
    nvic.NVIC_IRQChannel = TIM3_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    TIM_Cmd(TIM3, ENABLE);
}

// Trigger luân phiên 3 c?m bi?n
void Sensor_Update(void)
{
    if (Micros() - lastTrig < TRIGGER_PERIOD) return;
    lastTrig = Micros();

    switch(step)
    {
        case 0: SR05_Trigger(SR05_FRONT_TRIG_PORT, SR05_FRONT_TRIG_PIN); break;
        case 1: SR05_Trigger(SR05_LEFT_TRIG_PORT,  SR05_LEFT_TRIG_PIN);  break;
        case 2: SR05_Trigger(SR05_RIGHT_TRIG_PORT, SR05_RIGHT_TRIG_PIN); break;
    }
    step = (step + 1) % 3;
}

void TIM3_IRQHandler(void)
{
    uint16_t val;

    // ================== CHANNEL 1 - FRONT (PA6) ==================
    if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
    {
        val = TIM_GetCapture1(TIM3);

        if (state[FRONT] == 0)          // Ðang ch? Rising edge
        {
            start[FRONT] = val;
            state[FRONT] = 1;

            // Ð?i sang b?t Falling edge
            TIM_ICInitTypeDef ic;
            ic.TIM_Channel     = TIM_Channel_1;
            ic.TIM_ICPolarity  = TIM_ICPolarity_Falling;
            ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
            ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
            ic.TIM_ICFilter    = 0;
            TIM_ICInit(TIM3, &ic);
        }
        else                            // Ðang ch? Falling edge
        {
            width[FRONT] = val - start[FRONT];
            dist[FRONT] = width[FRONT] / 58;
            if (dist[FRONT] > MAX_DIST || dist[FRONT] == 0)
                dist[FRONT] = MAX_DIST;

            state[FRONT] = 0;

            // Ð?i l?i sang Rising edge cho l?n sau
            TIM_ICInitTypeDef ic;
            ic.TIM_Channel     = TIM_Channel_1;
            ic.TIM_ICPolarity  = TIM_ICPolarity_Rising;
            ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
            ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
            ic.TIM_ICFilter    = 0;
            TIM_ICInit(TIM3, &ic);
        }
        TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
    }

    // ================== CHANNEL 2 - LEFT (PA7) ==================
    if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
    {
        val = TIM_GetCapture2(TIM3);

        if (state[LEFT] == 0)
        {
            start[LEFT] = val;
            state[LEFT] = 1;

            TIM_ICInitTypeDef ic;
            ic.TIM_Channel     = TIM_Channel_2;
            ic.TIM_ICPolarity  = TIM_ICPolarity_Falling;
            ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
            ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
            ic.TIM_ICFilter    = 0;
            TIM_ICInit(TIM3, &ic);
        }
        else
        {
            width[LEFT] = val - start[LEFT];
            dist[LEFT] = width[LEFT] / 58;
            if (dist[LEFT] > MAX_DIST || dist[LEFT] == 0)
                dist[LEFT] = MAX_DIST;

            state[LEFT] = 0;

            TIM_ICInitTypeDef ic;
            ic.TIM_Channel     = TIM_Channel_2;
            ic.TIM_ICPolarity  = TIM_ICPolarity_Rising;
            ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
            ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
            ic.TIM_ICFilter    = 0;
            TIM_ICInit(TIM3, &ic);
        }
        TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
    }

    // ================== CHANNEL 3 - RIGHT (PB0) ==================
    if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
    {
        val = TIM_GetCapture3(TIM3);

        if (state[RIGHT] == 0)
        {
            start[RIGHT] = val;
            state[RIGHT] = 1;

            TIM_ICInitTypeDef ic;
            ic.TIM_Channel     = TIM_Channel_3;
            ic.TIM_ICPolarity  = TIM_ICPolarity_Falling;
            ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
            ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
            ic.TIM_ICFilter    = 0;
            TIM_ICInit(TIM3, &ic);
        }
        else
        {
            width[RIGHT] = val - start[RIGHT];
            dist[RIGHT] = width[RIGHT] / 58;
            if (dist[RIGHT] > MAX_DIST || dist[RIGHT] == 0)
                dist[RIGHT] = MAX_DIST;

            state[RIGHT] = 0;

            TIM_ICInitTypeDef ic;
            ic.TIM_Channel     = TIM_Channel_3;
            ic.TIM_ICPolarity  = TIM_ICPolarity_Rising;
            ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
            ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
            ic.TIM_ICFilter    = 0;
            TIM_ICInit(TIM3, &ic);
        }
        TIM_ClearITPendingBit(TIM3, TIM_IT_CC3);
    }
}

// Getter
uint16_t Sensor_Front(void) { return dist[FRONT]; }
uint16_t Sensor_Left(void)  { return dist[LEFT]; }
uint16_t Sensor_Right(void) { return dist[RIGHT]; }