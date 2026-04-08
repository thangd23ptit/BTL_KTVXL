#include "mode.h"
#include "control.h"
// ham de doi mode
mode_t Mode_Get(void){
    return (mode_t)Control_GetData().mode;
}