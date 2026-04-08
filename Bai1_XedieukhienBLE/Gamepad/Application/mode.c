#include "mode.h"
#include "gpio.h"
#include "tim.h"

void Mode_Init(Mode_t *mode, GPIO_TypeDef *port, uint16_t pin){
    mode->port = port;
    mode->pin = pin;
    mode->current_mode = MODE_MANUAL;
    mode->last_state = 1;
    GPIO_Config(port, pin, GPIO_MODE_INPUT_PULLUP);
}

protocol_mode_t Mode_Update(Mode_t *mode){
    uint8_t current_state = GPIO_Read(mode->port, mode->pin);
    if(mode->last_state == 1 && current_state == 0){
        Delay_ms(20);
        while(GPIO_Read(mode->port, mode->pin) == 0);
        if(mode->current_mode == MODE_MANUAL)
            mode->current_mode = MODE_AUTO;
        else
            mode->current_mode = MODE_MANUAL;
    }
    mode->last_state = current_state;
    return mode->current_mode;
}