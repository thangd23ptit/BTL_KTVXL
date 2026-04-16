#include "ip_gamepad.h"
#include "ip_joystick.h"
#include "ip_protocol.h"

/**
 * @brief Khoi tao gamepad (joystick + mode button)
 * @param gp Con tro cau truc Gamepad
 * @param joy_x Kenh ADC truc X
 * @param joy_y Kenh ADC truc Y
 * @param mode_port GPIO port nut mode
 * @param mode_pin GPIO pin nut mode
 * @retval None
 */
void Ip_Gamepad_Init(Gamepad_t *gp, uint8_t joy_x, uint8_t joy_y,
                     GPIO_TypeDef *mode_port, uint16_t mode_pin)
{
    Ip_Joystick_Init(&gp->joystick, joy_x, joy_y);
    Ip_Mode_Init(&gp->mode_button, mode_port, mode_pin);
}

/**
 * @brief Cap nhat trang thai gamepad va gui du lieu dieu khien
 * @param gp Con tro cau truc Gamepad
 * @retval None
 */
void Ip_Gamepad_Update(Gamepad_t *gp)
{
    uint16_t x = Ip_Joystick_ReadX(&gp->joystick);
    uint16_t y = Ip_Joystick_ReadY(&gp->joystick);

    protocol_mode_t mode = Ip_Mode_Update(&gp->mode_button);
    protocol_cmd_t cmd = CMD_STOP;
    uint16_t speed = 0;

    if (mode == MODE_AUTO)
    {
        cmd = CMD_FORWARD;
        speed = 700;
    }
    else
    {
        cmd = Ip_Protocol_Encode(x, y);

        if (cmd == CMD_FORWARD || cmd == CMD_BACKWARD)
        {
            speed = (y > 2048) ? (y - 2048) : (2048 - y);
        }
        else if (cmd == CMD_LEFT || cmd == CMD_RIGHT)
        {
            speed = (x > 2048) ? (x - 2048) : (2048 - x);
        }

        speed /= 2;
    }

    Ip_Protocol_Send(mode, cmd, speed);
}