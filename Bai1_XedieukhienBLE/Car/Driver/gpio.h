#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

//L298 
#define L_IN1 GPIO_Pin_10
#define L_IN2 GPIO_Pin_11
#define R_IN1 GPIO_Pin_12
#define R_IN2 GPIO_Pin_13

#define MOTOR_PORT GPIOB

//SR05
#define SR05_FRONT_TRIG_PORT   GPIOA
#define SR05_FRONT_TRIG_PIN    GPIO_Pin_0
#define SR05_LEFT_TRIG_PORT    GPIOA
#define SR05_LEFT_TRIG_PIN     GPIO_Pin_1
#define SR05_RIGHT_TRIG_PORT   GPIOA
#define SR05_RIGHT_TRIG_PIN    GPIO_Pin_4

//API
void GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t pin, uint8_t state);
uint8_t GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t pin);
void GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t pin);
void GPIO_ConfigOutput(GPIO_TypeDef* port, uint16_t pin);
void GPIO_ConfigInput(GPIO_TypeDef* port, uint16_t pin);
#endif