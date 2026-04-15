#ifndef _MID_MODE_H
#define _MID_MODE_H

typedef enum
{
    MID_MODE_MANUAL = 'M',
    MID_MODE_AUTO   = 'A',
} mid_mode_t;

mid_mode_t Mid_Mode_Get(void);

#endif