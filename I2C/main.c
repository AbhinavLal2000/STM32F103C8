#include "oled.h"
#include "systick.h"
/*
OLED GM009605 v4.2 SSD1306
VDD 3.3V
*/

/*
I2C-2 pins
PB10 SCL
PB11 SDA
*/

int main(void)
{
	// init I2C
	oled_init();

	oled_clear();
	
	//oled_print("ABHINAV");

	for(int i=0;i<8;i++)
	{
		oled_print_pos(i,0,"Abhinav");
		oled_print_pos(i,36,"Abhinav");
		oled_print_pos(i,72,"Abhinav");
		oled_print_pos(i,108,"Lal");
		oled_print_pos(i,123,".");
	}
	
}

