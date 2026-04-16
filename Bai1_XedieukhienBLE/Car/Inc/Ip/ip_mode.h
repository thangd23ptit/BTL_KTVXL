#ifndef _IP_MODE_H
#define _IP_MODE_H

typedef enum
{
    IP_MODE_MANUAL = 'M',
    IP_MODE_AUTO   = 'A',
} ip_mode_t;

ip_mode_t Ip_Mode_Get(void);

#endif