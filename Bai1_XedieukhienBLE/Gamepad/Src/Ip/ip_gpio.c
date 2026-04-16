#include "ip_gpio.h"

/**
 * @brief Bat clock cho GPIO port
 * @param GPIOx Port GPIO (GPIOA, GPIOB,...)
 * @retval None
 */
static void Ip_GPIO_EnableClock(GPIO_TypeDef *GPIOx)
{
    if (GPIOx == GPIOA) RCC->APB2ENR |= (1 << 2);
    else if (GPIOx == GPIOB) RCC->APB2ENR |= (1 << 3);
    else if (GPIOx == GPIOC) RCC->APB2ENR |= (1 << 4);
    else if (GPIOx == GPIOD) RCC->APB2ENR |= (1 << 5);
}

/**
 * @brief Cau hinh che do GPIO
 * @param GPIOx Port GPIO
 * @param pin Chan GPIO can cau hinh
 * @param mode Che do hoat dong (input/output)
 * @retval None
 */
void Ip_GPIO_Config(GPIO_TypeDef *GPIOx, uint16_t pin, ip_gpio_mode_t mode)
{
    uint8_t pos = 0;

    Ip_GPIO_EnableClock(GPIOx);

    while (((pin >> pos) & 0x01) == 0)
        pos++;

    volatile uint32_t *config_reg;

    if (pos < 8)
        config_reg = &GPIOx->CRL;
    else
    {
        config_reg = &GPIOx->CRH;
        pos -= 8;
    }

    *config_reg &= ~(0xF << (pos * 4));

    switch (mode)
    {
        case IP_GPIO_MODE_OUTPUT_PP:
            *config_reg |= (0x3 << (pos * 4));
            break;

        case IP_GPIO_MODE_INPUT_PULLUP:
            *config_reg |= (0x8 << (pos * 4));
            GPIOx->ODR |= pin;
            break;

        case IP_GPIO_MODE_INPUT_FLOATING:
            *config_reg |= (0x4 << (pos * 4));
            break;
    }
}

/**
 * @brief Ghi trang thai ra chan GPIO
 * @param GPIOx Port GPIO
 * @param pin Chan GPIO
 * @param state Trang thai (1: HIGH, 0: LOW)
 * @retval None
 */
void Ip_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t state)
{
    if (state)
        GPIOx->BSRR = pin;
    else
        GPIOx->BRR = pin;
}

/**
 * @brief Doc trang thai chan GPIO
 * @param GPIOx Port GPIO
 * @param pin Chan GPIO
 * @retval 1 neu HIGH, 0 neu LOW
 */
uint8_t Ip_GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    return (GPIOx->IDR & pin) ? 1 : 0;
}

/**
 * @brief Dao trang thai chan GPIO
 * @param GPIOx Port GPIO
 * @param pin Chan GPIO
 * @retval None
 */
void Ip_GPIO_Toggle(GPIO_TypeDef *GPIOx, uint16_t pin)
{
    GPIOx->ODR ^= pin;
}