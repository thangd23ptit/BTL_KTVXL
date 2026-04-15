#include "ip_mode.h"
#include "ip_control.h"

/**
 * @brief Lay che do hien tai (manual/auto)
 * @param None
 * @retval Gia tri che do (IP_MODE_MANUAL / IP_MODE_AUTO)
 */
ip_mode_t Ip_Mode_Get(void){
    return (ip_mode_t)Ip_Control_GetData().mode;
}