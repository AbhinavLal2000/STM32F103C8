#include "gpio.h"

int main(void)
{
	systick_init();
	initGPIO(PC,13,OUT50,OUT_GP_PP);
	
	while(1)
	{
		writeGPIO(PC,13,1);
		delayms(1000);
		writeGPIO(PC,13,0);
		delayms(1000);
	}
}	
