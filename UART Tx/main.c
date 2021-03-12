#include "stm32f10x.h"

void delay_ms(int num);
char c = 'A';

int main(void)
{
	// init UART
	
	// init alternate function i/o clock
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// init clock for GPIOA
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// init USART2 
	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
	
	// setup i/o pins PA2:Tx = alternate function output; PA3:Rx = input mode
	// PA2
	GPIOA -> CRL |= (1<<8 | 1<<9 | 1<<11);
	GPIOA -> CRL &= ~(1<<10);
	// PA3
	GPIOA -> CRL |= 1<<15;
	GPIOA -> CRL &= ~(1<<12 | 1<<13 | 1<<14);
	
	// set baud rate = 9600 bps
	USART2 -> BRR = 0xEA6;
	
	// enable USART, Tx and Rx
	USART2 -> CR1 |= USART_CR1_UE;
	USART2 -> CR1 |= USART_CR1_TE;
	// USART2 -> CR1 |= USART_CR1_RE;
	
	while(1)
	{
		// transmit a char
		// wait until TXE gets free
		while((USART2 -> SR & 0x80) == 0x00);
		USART2 -> DR = c;
		delay_ms(1000);
		
	}
	
	

	
	
}

void delay_ms(int num)
{
	volatile int j = num*2500;
	for(volatile int i=0;i<j;i++);
}
