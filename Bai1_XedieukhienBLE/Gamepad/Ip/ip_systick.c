#include "ip_systick.h"

/**
 * @brief Delay theo don vi micro giay bang SysTick
 * @param us So micro giay can delay
 * @retval None
 */
void Ip_SysTick_DelayUs(uint32_t us)
{
    SysTick->LOAD = 72 * us - 1;
    SysTick->VAL  = 0;
    SysTick->CTRL = (1 << 2) | (1 << 0);

    while ((SysTick->CTRL & (1 << 16)) == 0);

    SysTick->CTRL = 0;
}

/**
 * @brief Delay theo don vi mili giay bang SysTick
 * @param ms So mili giay can delay
 * @retval None
 */
void Ip_SysTick_DelayMs(uint32_t ms)
{
    while (ms--)
    {
        Ip_SysTick_DelayUs(1000);
    }
}