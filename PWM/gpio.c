#include "gpio.h"

/*
This GPIO header in compatible with STM32F103C8 Bluepill board
*/

void initGPIO(unsigned short port, unsigned short pin, unsigned short dirn, unsigned short option)
{
	volatile unsigned long * CR;
	unsigned short tpin 	= pin;
	unsigned short offset	= 0x00;
	
	if(pin > 7)
	{
		tpin   = tpin - 8;
		offset = 0x01;
	}
	
	if (port == 1)
	{
		RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;
		CR           = (volatile unsigned long *) (&GPIO_A + offset);
		
	}
	else if (port == 2)
	{
		RCC_APB2ENR |= RCC_APB2ENR_IOPBEN;
		CR			     = (volatile unsigned long *) (&GPIO_B + offset);
		
	}
	else if (port == 3)
	{
		RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;
		CR			     = (volatile unsigned long *) (&GPIO_C + offset);
		
	}
	
	// clear pins before using
	*CR &= ~(0xFF << (tpin*4));
	
	// setting pins and modes
	*CR |= ((dirn << (tpin*4)) | (option << (tpin*4+2)));
	
}

int readGPIO(unsigned short port, unsigned short pin)
{
	volatile unsigned long * IDR;
	unsigned long offset = 0x02;
	int state;
	
	if(port == 1)
	{
		IDR = (volatile unsigned long *) (&GPIO_A + offset);
	}
	else if(port == 2)
	{
		IDR = (volatile unsigned long *) (&GPIO_B + offset);
	}
	else if(port == 3)
	{
		IDR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	
	state = ((*IDR & (1 << pin)) >> pin);
	return state;
}

void writeGPIO(unsigned short port, unsigned short pin, unsigned short state)
{
	volatile unsigned long * ODR;
	unsigned long offset = 0x03;
	
	if(port == 1)
	{
		ODR = (volatile unsigned long *) (&GPIO_A + offset);
	}
	else if(port == 2)
	{
		ODR = (volatile unsigned long *) (&GPIO_B + offset);
	}
	else if(port == 3)
	{
		ODR = (volatile unsigned long *) (&GPIO_C + offset);
	}
	
	state ? (*ODR |= (state << pin)) : (*ODR &= ~(1<<pin));
}

void toggleGPIO(unsigned short port, unsigned short pin)
{
	if(readGPIO(port,pin))
	{
		writeGPIO(port,pin,0);
	}
	else
	{
		writeGPIO(port,pin,1);
	}
}
