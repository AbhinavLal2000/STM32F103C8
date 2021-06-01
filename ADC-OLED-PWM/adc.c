#include "adc.h"

/*
PA0 ADC12_IN0
PA1 ADC12_IN1
PA2 ADC12_IN2
PA3 ADC12_IN3
PA4 ADC12_IN4
PA5 ADC12_IN5
PA6 ADC12_IN6
PA7 ADC12_IN7

PB0 ADC12_IN8
PB1 ADC12_IN9

PC0 ADC12_IN10
PC1 ADC12_IN11
PC2 ADC12_IN12
PC3 ADC12_IN13
PC4 ADC12_IN14
PC5 ADC12_IN15

ADC12_IN16 internal temperature sensor
*/

// initialising ADC
char adc_init(char adc, short port, short pin)
{
	char channel;
	char result = 0;
	
	if (port == PA)
	{
		if (pin < 8)
		{
			result  = 1;
			channel = pin;
		}
	}
	
	else if (port == PB)
	{
		if (pin < 2)
		{
			result  = 1;
			channel = 8 + pin;
		}
	}
	
	else if (port == PC)
	{
		if (pin < 6)
		{
			result  = 1;
			channel = 10 + pin;
		}
	}
	
	if(result)
	{
		initGPIO(port,pin,IN,IN_AN);
		
		if(adc == adc1)
		{
			RCC  -> APB2ENR |= RCC_APB2ENR_ADC1EN;
			ADC1 -> CR2			 = 0;
			ADC1 -> SQR3		 = channel;
			ADC1 -> CR2			|= ADC_CR2_ADON;
			delayms(100);
			ADC1 -> CR2			|= ADC_CR2_ADON;
			ADC1 -> CR2			|= ADC_CR2_CONT;
			
		}
		
		else if(adc == adc2)
		{
			RCC  -> APB2ENR |= RCC_APB2ENR_ADC2EN;
			ADC2 -> CR2			 = 0;
			ADC2 -> SQR3		 = channel;
			ADC2 -> CR2			|= ADC_CR2_ADON;
			delayms(100);
			ADC2 -> CR2			|= ADC_CR2_ADON;
			delayms(100);
			ADC2 -> CR2			|= ADC_CR2_CONT;
		}
		
	}
	
	return result;
}

char adc_check(char adc, short port, short pin)
{
	char check = 0;
	
	if(adc == adc1)
	{
		if(ADC1 -> SR & 2)
		{
			check = 1;
		}
	}
	else if(adc == adc2)
	{
		if(ADC2 -> SR & 2)
		{
			check = 1;
		}
	}
	
	return check;
}

int adc_read(char adc, short port, short pin)
{
	int value = 0;
	int data	= 0;
	
	if(adc == adc1)
	{
		data = ADC1 -> DR;
	}
	else if(adc == adc2)
	{
		data = ADC2 -> DR;
	}
	
	value = (data*1000)/0xFFF;
	
	return value;
}
