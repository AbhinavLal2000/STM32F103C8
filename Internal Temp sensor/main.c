#include "stm32f10x.h"
#include "lcd.h"

void ADC_wait(volatile int d);
void ADC_wait(volatile int d)
{
	for(volatile int i=0;i<d;i++);
}

int main()
{
	// initialise LCD
	LCD_init();
	
	// start LCD
	LCD_start();
	
	// enable clock for GPIOA and ADC1
	RCC -> APB2ENR |= (1<<2) | (1<<9);
	
	// set GPIOA PA1 as analog input
	//GPIOA -> CRL &= ~((1<<2) | (1<<3) | (1<<4) | (1<<5));
	
	// select Prescaler
	RCC -> CFGR &= ~(1<<14);
	RCC -> CFGR |= (1<<15);
	
	// select max sampling rate for channel 1
	ADC1 -> SMPR2 |= (1<<3) | (1<<4) | (1<<5);
	
	// select sequence for channel 16
	ADC1 -> SQR3 |= 0x00000010;
	
	// enable ADC and temp sensor bit for 1 time 
	ADC1 -> CR2 |= (1<<0) | (1<<23);
	// wait to set
	ADC_wait(50);
	
	// enable ADC for 2 time
	ADC1 -> CR2 |= (1<<0);
	// wait to set
	ADC_wait(50);
	
	// enable calibration
	ADC1 -> CR2 |= (1<<2);
	// wait till hardware clears the CAL bit
	while((ADC1 -> CR2 & ADC_CR2_CAL) != 0);
	
	// set continuous conversion mode
	ADC1 -> CR2 |= (1<<1);
	
	// declare variable for analog value
	unsigned int val = 0;
	double temp = 0;
	
	while(1)	
	{
		ADC1 -> CR2 |= (1<<22);
		// wait till hardware clears the SWSTART bit
		while((ADC1 -> CR2 & ADC_CR2_SWSTART) != 0);
		
		// monitor EOC bit
		while(!(ADC1 -> SR & ADC_SR_EOC));
		
		// get data
		val = ADC1 -> DR;
		temp = ((1.43 - val) / 4.3) + 25;
		
		// print ADC value on LCD
		LCD_cmd(0x80);
		LCD_string("ADC value: ");
		LCD_cur_right(11);
		LCD_float(temp,3);
		
		//some delay
		ADC_wait(300);
	}
}
