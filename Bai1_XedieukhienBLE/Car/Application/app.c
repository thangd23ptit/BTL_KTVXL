#include "app.h"

void App_Init(void)
{
    Sensor_Init();
    Control_Init();
    Maze_Init();
    Mode_Set(MODE_MANUAL);
}

void App_Run(void)
{
    Sensor_Update();
		Control_Run();
    if(Mode_Get() == MODE_MANUAL)
    {
        App_Control_Run();
    }
    else
    {
        App_Auto_Run();
    }
}