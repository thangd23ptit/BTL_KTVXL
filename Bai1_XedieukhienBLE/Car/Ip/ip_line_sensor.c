#include "ip_line_sensor.h"
#include "ip_gpio.h"

/**
 * @brief Khoi tao cac chan cam bien line (input pull-up)
 * @param None
 * @retval None
 */
void Ip_LineSensor_Init(void)
{
    Ip_GPIO_Config_Input_PU(GPIOA, 3);   
    Ip_GPIO_Config_Input_PU(GPIOA, 4);   
    Ip_GPIO_Config_Input_PU(GPIOA, 5);   
    Ip_GPIO_Config_Input_PU(GPIOB, 12); 
    Ip_GPIO_Config_Input_PU(GPIOB, 13);  
}

/**
 * @brief Doc gia tri raw tu cam bien (5 bit)
 * @param None
 * @retval Gia tri bit (bit0 -> bit4)
 */
uint8_t Ip_LineSensor_ReadRaw(void){
    uint8_t d = 0;

    d |= Ip_GPIO_Read(GPIOA, 3) << 0;  
    d |= Ip_GPIO_Read(GPIOA, 4) << 1;  
    d |= Ip_GPIO_Read(GPIOA, 5) << 2;   
    d |= Ip_GPIO_Read(GPIOB,12) << 3;   
    d |= Ip_GPIO_Read(GPIOB,13) << 4;   

    // dao muc (vi cam bien line thuong active low)
    d = (~d) & 0x1F;

    return d;
}

/**
 * @brief Doc gia tri on dinh (2 lan)
 * @param None
 * @retval Gia tri on dinh
 */
static uint8_t Ip_LineSensor_ReadStable(void){
    uint8_t a = Ip_LineSensor_ReadRaw();

    for(volatile int i = 0; i < 2000; i++); 

    uint8_t b = Ip_LineSensor_ReadRaw();

    return (a == b) ? a : a;
}

/**
 * @brief Tinh sai so vi tri line
 * @param None
 * @retval Gia tri error (-4 -> 4)
 */
int8_t Ip_LineSensor_GetError(void){
    uint8_t s = Ip_LineSensor_ReadStable();

    int sum = 0;
    int cnt = 0;

    if(s & 0x01){ sum += -4; cnt++; }   
    if(s & 0x02){ sum += -2; cnt++; }   
    if(s & 0x04){ sum +=  0; cnt++; }   
    if(s & 0x08){ sum +=  2; cnt++; }   
    if(s & 0x10){ sum +=  4; cnt++; }   

    static int8_t last_error = 0;

    if(cnt == 0){
        return last_error;
    }

    int8_t new_error = sum / cnt;

    // loc trung binh
    int8_t filtered = (last_error + new_error) / 2;

    last_error = filtered;

    return filtered;
}