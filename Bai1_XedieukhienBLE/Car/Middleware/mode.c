#include "mode.h"

static Mode_t currentmode = MODE_MANUAL;

void Mode_Set(Mode_t mode){
		currentmode = mode;
}

Mode_t Mode_Get(void){
	return currentmode;
}