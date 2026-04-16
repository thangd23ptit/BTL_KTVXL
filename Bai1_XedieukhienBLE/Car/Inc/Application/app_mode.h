#ifndef _APP_MODE_H
#define _APP_MODE_H

typedef enum
{
    APP_MODE_MANUAL = 'M',
    APP_MODE_AUTO   = 'A',
} app_mode_t;

app_mode_t App_Mode_Get(void);

#endif