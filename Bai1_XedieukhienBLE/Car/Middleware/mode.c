#include "mode.h"
#include "control.h"

mode_t Mode_Get(void)
{
    return (mode_t)Control_GetData().mode;
}