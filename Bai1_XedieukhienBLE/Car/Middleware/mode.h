#ifndef __MODE_H
#define __MODE_H

typedef enum
{
    MODE_MANUAL = 'M',
    MODE_AUTO   = 'A',
} mode_t;

mode_t Mode_Get(void);

#endif