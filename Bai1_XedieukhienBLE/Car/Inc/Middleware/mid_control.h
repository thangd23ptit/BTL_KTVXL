#ifndef _MID_CONTROL_H
#define _MID_CONTROL_H

#include <stdint.h>

typedef struct
{
    char mode;
    char cmd;
    uint16_t speed;
} mid_control_data_t;

void Mid_Control_Init(void);
void Mid_Control_Run(void);
mid_control_data_t Mid_Control_GetData(void);
void Mid_Control_Execute(mid_control_data_t data);

#endif