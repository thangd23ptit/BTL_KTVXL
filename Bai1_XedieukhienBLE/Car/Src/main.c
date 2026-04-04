#include "system_init.h"
#include "app.h"

int main(void)
{
    System_Init();
		App_Init();
		while(1){
			App_Run();
		}
}