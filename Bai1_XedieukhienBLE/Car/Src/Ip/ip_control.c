#include "ip_control.h"
#include "ip_bluetooth.h"
#include "ip_motor.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Bien luu trang thai dieu khien
 * mode: M (manual), A (auto)
 * cmd : F/B/L/R/S
 * speed: toc do
 */
static ip_control_data_t g_control = {'M', 'S', 700};

/**
 * @brief Khoi tao Bluetooth
 * @param None
 * @retval None
 */
void Ip_Control_Init(void){
    Ip_Bluetooth_Init(9600);
}

/**
 * @brief Xu ly frame du lieu tu Bluetooth
 * dinh dang: $mode,cmd,speed#
 * @param None
 * @retval None
 */
void Ip_Control_Run(void){
    static char frame[20];
    static uint8_t idx = 0;

    while(Ip_Bluetooth_Available()){
        char c = Ip_Bluetooth_ReadChar();

        if(c == '$') idx = 0;

        if(idx < sizeof(frame) - 1)
            frame[idx++] = c;

        if(c == '#'){
            frame[idx] = '\0';
            idx = 0;

            char mode, cmd;
            uint16_t speed;

            if(sscanf(frame, "$%c,%c,%hu#", &mode, &cmd, &speed) == 3){
                g_control.mode = mode;
                g_control.cmd = cmd;
                g_control.speed = speed;
            }
        }
    }
}

/**
 * @brief Lay du lieu dieu khien hien tai
 * @param None
 * @retval Struct control
 */
ip_control_data_t Ip_Control_GetData(void){
    return g_control;
}

/**
 * @brief Thuc thi lenh dieu khien (manual mode)
 * @param data Du lieu dieu khien
 * @retval None
 */
void Ip_Control_Execute(ip_control_data_t data){
    switch(data.cmd){
        case 'F': Ip_Motor_Forward(data.speed); break;
        case 'B': Ip_Motor_Backward(data.speed); break;
        case 'L': Ip_Motor_Left(data.speed); break;
        case 'R': Ip_Motor_Right(data.speed); break;
        default : Ip_Motor_Stop(); break;
    }
}