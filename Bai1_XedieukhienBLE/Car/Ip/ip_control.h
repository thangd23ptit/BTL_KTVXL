#ifndef _IP_CONTROL_H
#define _IP_CONTROL_H

#include <stdint.h>

typedef struct
{
    char mode;
    char cmd;
    uint16_t speed;
} ip_control_data_t;

void Ip_Control_Init(void);
void Ip_Control_Run(void);
ip_control_data_t Ip_Control_GetData(void);
void Ip_Control_Execute(ip_control_data_t data);

#endif