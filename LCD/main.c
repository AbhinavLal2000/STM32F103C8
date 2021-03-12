#include "stm32f10x.h"
#include "lcd.h"

int main()
{
	LCD_init();
	LCD_start();
	for(unsigned int i = 0;i<5000;i++)
	{
		LCD_cmd(0x80);
		LCD_int(i,4);
	}
	
	
	while(1)
	{
	}
	
	
}

