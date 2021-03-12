#include <stm32f10x.h>
#include "systick.h"
#include "spi.h"
#include "nokia5110.h"

/*
SPI-1 PINs

PA4 NSS
PA5	SCLK
PA6	MISO
PA7	MOSI

LCD PINs

PA0 RST
PA1 DC
PA2 BL
PA4 CE/SS
PA5 CLK
PA7 DIN/MOSI
3.3V VCC
*/

// declaring LCD buffer for further use
unsigned char nokia5110_buffer[6][84];

int main()
{
	//initialise systick
	systick_init();
	
	// initialise nokia LCD
	nokia5110_init();
	
	nokia5110_clear();
	nokia5110_clear_buffer(nokia5110_buffer);
	nokia5110_update_str_buffer(0,25,"Abhinav",nokia5110_buffer);
	nokia5110_print_buffer(nokia5110_buffer);
	delayms(2000);
	nokia5110_clear();
	nokia5110_print(2,7,"Nokia 5110 LCD");
	nokia5110_print(4,7,"    PCD8544   ");

	
}
