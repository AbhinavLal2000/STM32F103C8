#include "stm32f10x.h"

void wait(volatile int d)
{
	volatile int i = 0;
	for(i;i<d;i++);
}
int main()
{
	// enable GPIO C and GPIO B clock
	RCC -> APB2ENR |= (1<<4) | (1<<3);
	// configure GPIO C for output
	GPIOC -> CRH |= ((1<<20) | (1<<21));
	GPIOC -> CRH &= ~((1<<22) | (1<<23));
	// configure GPIO B for input
	GPIOB -> CRH &= ~((1<<12) | (1<<13));
	GPIOB -> CRH &= ~(1<<14);
	GPIOB -> CRH |= (1<<15);
	
	while(1)
	{
		if(GPIOB -> IDR & (1<<11))
		{
			GPIOC -> BSRR = (1<<13);
		}
		else
		{
			GPIOC -> BSRR = 1<<(13 + 16);
		}
	}
	
	
	
}
