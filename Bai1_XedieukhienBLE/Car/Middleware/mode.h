#ifndef MODE_H
#define MODE_H

typedef enum{
	MODE_MANUAL = 0,
	MODE_AUTO
}Mode_t;

void Mode_Set(Mode_t mode);
Mode_t Mode_Get(void);

#endif

