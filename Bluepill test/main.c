#include "stm32f10x.h"
//volatile int num = 250000;
void delay_ms(int num);
int main()
{
	int d = 50;
	// enable GPIO C clock
	RCC -> APB2ENR |= (1<<4);
	// configure GPIO C for output
	GPIOC -> CRH |= ((1<<20)|(1<<21));
	GPIOC -> CRH &= ~((1<<22)|(1<<23));
	
	
	while(1)
	{
		//set pin 13 high
		//GPIOC -> BSRR = (1<<13);
		// wait
		//for(volatile int i=0;i<num;i++);
		// set pin 13 low
		//GPIOC -> BSRR = 1<<(13 + 16);
		// wait
		//for(volatile int i=0;i<num;i++);
		GPIOC -> ODR |= 1<<13;
		delay_ms(d);
		GPIOC -> ODR &= ~(1<<13);
		delay_ms(d);
		
	}
	
}

void delay_ms(int num)
{
	volatile int j = num*2500;
	for(volatile int i=0;i<j;i++);
}

