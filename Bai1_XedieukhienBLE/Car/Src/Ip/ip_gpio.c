#include "ip_gpio.h"

/**
 * @brief Bat clock cho GPIO
 * @param GPIOx Con tro toi port GPIO (GPIOA, GPIOB, GPIOC)
 * @retval None
 */
static void Ip_GPIO_EnableClock(GPIO_TypeDef *GPIOx){
    if(GPIOx == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    else if(GPIOx == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    else if(GPIOx == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
}

/**
 * @brief Cau hinh GPIO o che do Output push-pull toc do 50MHz
 * @param GPIOx Port GPIO
 * @param pin So chan (0-15)
 * @retval None
 */
void Ip_GPIO_Config_Output(GPIO_TypeDef *GPIOx, uint16_t pin){
    Ip_GPIO_EnableClock(GPIOx);
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

/**
 * @brief Cau hinh GPIO Input Pull-Up
 * @param GPIOx Port GPIO
 * @param pin So chan (0-15)
 * @retval None
 */
void Ip_GPIO_Config_Input_PU(GPIO_TypeDef *GPIOx, uint16_t pin){
    Ip_GPIO_EnableClock(GPIOx);
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

/**
 * @brief Ghi trang thai ra chan GPIO
 * @param GPIOx Port GPIO
 * @param pin So chan (0-15)
 * @param state Trang thai (0: LOW, 1: HIGH)
 * @retval None
 */
void Ip_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state){
    if(state) GPIOx->BSRR = (1 << pin);
    else GPIOx->BRR = (1 << pin);
}

/**
 * @brief Doc trang thai chan GPIO
 * @param GPIOx Port GPIO
 * @param pin So chan (0-15)
 * @retval 1 neu HIGH, 0 neu LOW
 */
uint8_t Ip_GPIO_Read(GPIO_TypeDef *GPIOx, uint16_t pin){
    return (GPIOx->IDR & (1 << pin)) ? 1 : 0;
}

/**
 * @brief Cau hinh GPIO Input Floating
 * @param GPIOx Port GPIO
 * @param pin So chan (0-15)
 * @retval None
 */
void Ip_GPIO_Config_Input(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    Ip_GPIO_EnableClock(GPIOx);

    uint16_t pos = pin;

    if(pos < 8)
    {
        GPIOx->CRL &= ~(0xF << (pos * 4));
        GPIOx->CRL |=  (0x4 << (pos * 4));   // input floating
    }
    else
    {
        pos -= 8;
        GPIOx->CRH &= ~(0xF << (pos * 4));
        GPIOx->CRH |=  (0x4 << (pos * 4));   // input floating
    }
}