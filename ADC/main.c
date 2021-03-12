#include "stm32f10x.h"
#include "lcd.h"
#include <stdlib.h>
#include <string.h>

void ADC_wait(volatile int d);
void ADC_wait(volatile int d)
{
	for(volatile int i=0;i<d;i++);
}

int main()
{
	// Initialise LCD
	LCD_init();
	
	// start LCD
	LCD_start();
	
	//Initialise ADC
	
	// enable clock for GPIOA and ADC1
	RCC -> APB2ENR |= (1<<2) | (1<<9);
	
	// set GPIOA PA1 as analog input
	GPIOA -> CRL &= ~((1<<2) | (1<<3) | (1<<4) | (1<<5));
	
	// select Prescaler
	RCC -> CFGR &= ~(1<<14);
	RCC -> CFGR |= (1<<15);
	
	// select max sampling rate for channel 1
	ADC1 -> SMPR2 |= (1<<3) | (1<<4) | (1<<5);
	
	// select channel sequence
	ADC1 -> SQR3 |= (1<<0);
	ADC1 -> SQR3 &= ~((1<<1) | (1<<2) | (1<<3) | (1<<4));
	
	// enable ADC for 1 time
	ADC1 -> CR2 |= (1<<0);
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
	
	while(1)
	{
		// start conversion on regular channel
		ADC1 -> CR2 |= (1<<22);
		// wait till hardware clears the SWSTART bit
		while((ADC1 -> CR2 & ADC_CR2_SWSTART) != 0);
		
		// monitor EOC bit
		while(!(ADC1 -> SR & ADC_SR_EOC));
		
		// get data
		val = ADC1 -> DR;
		
		// print ADC value on LCD
		LCD_cmd(0x80);
		LCD_string("ADC value: ");
		LCD_cur_right(11);
		LCD_int(val,4);
		
		//some delay
		ADC_wait(300);
	}
	
	
}
