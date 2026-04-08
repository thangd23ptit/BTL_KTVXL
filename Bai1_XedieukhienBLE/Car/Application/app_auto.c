#include "app_auto.h"
#include "control.h"
#include "maze.h"

//ham chay mode auto
void App_Auto_Run(void){
    control_data_t data = Control_GetData();
    Maze_Run(data.speed);
}