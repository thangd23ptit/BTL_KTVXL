#include "ip_mode.h"
#include "ip_gpio.h"
#include "ip_tim.h"
#include "ip_systick.h"

/**
 * @brief Khoi tao che do hoat dong (Mode)
 * @param mode Con tro cau truc Mode
 * @param port GPIO port nut nhan
 * @param pin GPIO pin nut nhan
 * @retval None
 */
void Ip_Mode_Init(Mode_t *mode, GPIO_TypeDef *port, uint16_t pin)
{
    mode->port = port;
    mode->pin = pin;
    mode->current_mode = MODE_MANUAL;
    mode->last_state = 1;

    Ip_GPIO_Config(port, pin, IP_GPIO_MODE_INPUT_PULLUP);
}

/**
 * @brief Cap nhat trang thai mode (nhan nut de toggle)
 * @param mode Con tro cau truc Mode
 * @retval Trang thai mode hien tai (MANUAL/AUTO)
 */
protocol_mode_t Ip_Mode_Update(Mode_t *mode)
{
    uint8_t current_state = Ip_GPIO_Read_Pin(mode->port, mode->pin);

		if (Ip_GPIO_Read_Pin(mode->port, mode->pin) == 0)
		{
				Ip_SysTick_DelayMs(20);

				if (Ip_GPIO_Read_Pin(mode->port, mode->pin) == 0)
				{
						mode->current_mode =
								(mode->current_mode == MODE_MANUAL) ? MODE_AUTO : MODE_MANUAL;

						while (Ip_GPIO_Read_Pin(mode->port, mode->pin) == 0);
				}
		}

		mode->last_state = current_state;
    return mode->current_mode;
}