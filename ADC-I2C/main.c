#include "adc.h"
#include "oled.h"

/*
ADC input: 	PA0
*/

int v = 0;
char c[5];

int main(void)
{
	systick_init();
	oled_init();
	oled_clear();
	adc_init(adc1,PA,0);
	
	while(1)
	{
		if(adc_check(adc1,PA,0))
		{
			v = adc_read(adc1,PA,0);
			int2char(v,c);
			oled_print_pos(0,0,"ADC: ");
			oled_print_pos(0,22,c);
			delayms(500);
		}
	}
	
}
