#include "system_init.h"
#include "app_control.h"
#include "app_motor.h"
#include "app_maze.h"

int main(void)
{
    System_Init();

    while(1)
    {
        App_Control_Run();

        app_control_data_t data = App_Control_GetData();

        if(data.mode == 'M')
        {
            App_Control_Execute(data);
        }
        else if(data.mode == 'A')
        {
            App_Maze_Run(data.speed);
        }
        else
        {
            App_Motor_Stop();
        }
    }
}