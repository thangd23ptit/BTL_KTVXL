#include "app_control.h"
#include "control.h"

//ham chay app control
void App_Control_Run(void){
    control_data_t data = Control_GetData();
    Control_Execute(data);
}