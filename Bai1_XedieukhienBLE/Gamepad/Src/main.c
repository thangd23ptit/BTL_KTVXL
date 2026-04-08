#include "main.h"
Gamepad_t gamepad;

int main(void){
    UART1_Init(9600);
    TIM2_Init_1ms();
    Gamepad_Init(&gamepad, 0, 1,GPIOB,(1 << 0));     
    while(1){
        Gamepad_Update(&gamepad);
        Delay_ms(100);
    }
}