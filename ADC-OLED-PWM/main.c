#include "adc.h"
#include "oled.h"
#include "pwm.h"

/*
	SCL 	 : PB10
	SDA  	 : PB11
	Analog : PA0
	PWM 	 : PA1
*/

int main(void)
{
	systick_init();
	adc_init(adc1,PA,0);
	pwm_init_t2c2();
	//pwm_init_t3c3();
	//pwm_init_t3c4();
	oled_init();
	oled_clear();
	
	unsigned int adc_val = 0;
	char c[2];
	
	while(1)
	{
		if(adc_check(1,PA,0))
		{
			adc_val = adc_read(adc1,PA,0);
			int2char(adc_val,c);
			oled_print_pos(0,0,c);
			TIM2 -> CCR2 = adc_val;
			//TIM3 -> CCR3 = adc_val;
			//TIM3 -> CCR4 = adc_val;
			str_empty(c);
			//delayms(500);
		}
	}
	
}
