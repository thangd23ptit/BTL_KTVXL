#ifndef _APP_CONTROL_H
#define _APP_CONTROL_H

#include <stdint.h>

typedef struct
{
    char mode;
    char cmd;
    uint16_t speed;
} app_control_data_t;

void App_Control_Init(void);
void App_Control_Run(void);
app_control_data_t App_Control_GetData(void);
void App_Control_Execute(app_control_data_t data);

#endif