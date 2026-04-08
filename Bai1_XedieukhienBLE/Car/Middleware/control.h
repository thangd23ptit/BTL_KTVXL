#ifndef __CONTROL_H
#define __CONTROL_H

#include <stdint.h>

typedef struct
{
    char mode;
    char cmd;
    uint16_t speed;
} control_data_t;

void Control_Init(void);
void Control_Run(void);
control_data_t Control_GetData(void);
void Control_Execute(control_data_t data);

#endif