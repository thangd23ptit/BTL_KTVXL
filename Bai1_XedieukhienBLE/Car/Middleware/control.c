#include "control.h"

static uint16_t speed = 700;

void Control_Init(void)
{
    Bluetooth_Init();
    Motor_Init();
}

void Control_Run(void){
	while(Bluetooth_Available()){
		char cmd = Bluetooth_Read();
		switch(cmd){
			case 'F' : Motor_Forward(speed);break;
			case 'B' : Motor_Backward(speed);break;
			case 'L' : Motor_Left(speed);break;
			case 'R' : Motor_Right(speed);break;
			case 's' : Motor_Stop();break;
			
			case '0': speed = 0; break;
      case '1': speed = 100; break;
      case '2': speed = 200; break;
      case '3': speed = 300; break;
      case '4': speed = 400; break;
      case '5': speed = 500; break;
      case '6': speed = 600; break;
      case '7': speed = 700; break;
      case '8': speed = 800; break;
      case '9': speed = 900; break;
			
			case 'A' : Mode_Set(MODE_AUTO);break;
			case 'M' : Mode_Set(MODE_MANUAL); break;
			default : break;
		}
	}
}