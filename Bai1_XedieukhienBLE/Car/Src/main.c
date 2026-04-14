#include "stm32f10x.h"
#include <stdio.h>

#include "system_init.h"
#include "app.h"

int main(void)
{
    System_Init();

    while(1)
    {
        App_Run();
    }
}