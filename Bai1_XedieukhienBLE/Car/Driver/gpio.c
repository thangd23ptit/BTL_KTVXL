#include "gpio.h"

//bat clock 
static void GPIO_EnableClock(GPIO_TypeDef *GPIOx){
    if(GPIOx == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    else if(GPIOx == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    else if(GPIOx == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
}

//config gpio la output 50MHz
void GPIO_Config_Output(GPIO_TypeDef *GPIOx, uint16_t pin){
    GPIO_EnableClock(GPIOx);
    uint16_t pos = pin;
    if(pos < 8){
        GPIOx->CRL &= ~(0xF << (pos * 4));
        GPIOx->CRL |=  (0x3 << (pos * 4));
    }
    else{
        pos -= 8;
        GPIOx->CRH &= ~(0xF << (pos * 4));
        GPIOx->CRH |=  (0x3 << (pos * 4));
    }
}

//config gpio input pull up 50MHz
void GPIO_Config_Input_PU(GPIO_TypeDef *GPIOx, uint16_t pin){
    GPIO_EnableClock(GPIOx);
    uint16_t pos = pin;
    if(pos < 8){
        GPIOx->CRL &= ~(0xF << (pos * 4));
        GPIOx->CRL |=  (0x8 << (pos * 4));
    }
    else{
        pos -= 8;
        GPIOx->CRH &= ~(0xF << (pos * 4));
        GPIOx->CRH |=  (0x8 << (pos * 4));
    }
    GPIOx->ODR |= (1 << pin);
}

//ham ghi ra chan pin gpio
void GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state){
    if(state) GPIOx->BSRR = (1 << pin);
    else GPIOx->BRR = (1 << pin);
}

//ham doc chan pin gpio
uint8_t GPIO_Read(GPIO_TypeDef *GPIOx, uint16_t pin){
    return (GPIOx->IDR & (1 << pin)) ? 1 : 0;
}

