#include "gamepad.h"
#include "protocol.h"

void Gamepad_Init(Gamepad_t *gp,uint8_t joy_x, uint8_t joy_y, GPIO_TypeDef *mode_port, uint16_t mode_pin){
    Joystick_Init(&gp->joystick, joy_x, joy_y);
    Mode_Init(&gp->mode_button, mode_port, mode_pin);
}

void Gamepad_Update(Gamepad_t *gp){
    uint16_t x = Joystick_ReadX(&gp->joystick);
    uint16_t y = Joystick_ReadY(&gp->joystick);
    protocol_mode_t mode = Mode_Update(&gp->mode_button);
    protocol_cmd_t cmd = CMD_STOP;
    uint16_t speed = 0;
    if(mode == MODE_AUTO){
        cmd = CMD_FORWARD;
        speed = 700; 
    }
    else{
        cmd = Protocol_Encode(x, y);
        if(cmd == CMD_FORWARD || cmd == CMD_BACKWARD){
            speed = (y > 2048) ? (y - 2048) : (2048 - y);
        }
        else if(cmd == CMD_LEFT || cmd == CMD_RIGHT){
            speed = (x > 2048) ? (x - 2048) : (2048 - x);
        }
        speed /= 2;
    }
    Protocol_Send(mode, cmd, speed);
}