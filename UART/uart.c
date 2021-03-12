#include <stm32f10x.h>
#include "uart.h"

/* UART PINs

UART2 PA2 TX PA3 RX,		36 MHz max clock
UART1 PA9 TX PA10 RX,		72 MHz max clock
UART3 PB10 TX PB11 RX,	36 MHz max clock

*/

void uart_init(unsigned short uart, unsigned long BR)
{
	// alternate function clock
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// baud rate
	unsigned long BR_cal;
	BR_cal = uart_brr_cal(uart,BR);
	
	if(uart == 1)
	{
		// GPIO-A clock
		RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
		
		// USART-1 clock
		RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
		
		// PA9 TX 50 MHz AF OP PP
		GPIOA -> CRH |= (1<<4 | 1<<5 | 1<<7);
		GPIOA -> CRH &= ~(1<<6);
		
		// PA10 RX IP PP
		GPIOA -> CRL |= 1<<11;
		GPIOA -> CRL &= ~(1<<8 | 1<<9 | 1<<10);
		
		// set baud rate = 9600 bps
		USART1 -> BRR = BR_cal;
		
		// enable USART
		USART1 -> CR1 |= USART_CR1_UE;
		
		// enable TX
		USART1 -> CR1 |= USART_CR1_TE;
		
		// enable RX
		USART1 -> CR1 |= USART_CR1_RE;
		
	}
	else if(uart == 2)
	{
		// GPIO-A clock
		RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
		
		// USART-2 clock
		RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
		
		// PA2 TX 50 MHz AF OP PP
		GPIOA -> CRL |= (1<<8 | 1<<9 | 1<<11);
		GPIOA -> CRL &= ~(1<<10);
		
		// PA3 RX IP PP
		GPIOA -> CRL |= 1<<15;
		GPIOA -> CRL &= ~(1<<12 | 1<<13 | 1<<14);
		
		// set baud rate = 9600 bps
		USART2 -> BRR = BR_cal;
		
		// enable USART
		USART2 -> CR1 |= USART_CR1_UE;
		
		// enable TX
		USART2 -> CR1 |= USART_CR1_TE;
		
		// enable RX
		USART2 -> CR1 |= USART_CR1_RE;
	
	}
	else if(uart == 3)
	{
		// GPIO-B clock
		RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
		
		// USART-3 clock
		RCC -> APB1ENR |= RCC_APB1ENR_USART3EN;
		
		// PB10 TX 50 MHz AF OP PP
		GPIOB -> CRH |= (1<<9 | 1<<8);
		GPIOB -> CRH &= ~(1<<10 | 1<<11);
		
		// PB11 RX IP PP
		GPIOB -> CRH |= (1<<15);
		GPIOB -> CRH &= ~(1<<12 | 1<<13 | 1<<14);
		
		// set baud rate = 9600 bps
		USART3 -> BRR = BR_cal;
		
		// enable USART
		USART3 -> CR1 |= USART_CR1_UE;
		
		// enable TX
		USART3 -> CR1 |= USART_CR1_TE;
		
		// enable RX
		USART3 -> CR1 |= USART_CR1_RE;
		
	}
	
}

unsigned long uart_brr_cal(unsigned short uart, unsigned long BR)
{
	unsigned long div = 36000000;
	double frac = 36000000.00;
	unsigned long dec;
	double frac2 = 1.00;
	unsigned long final;
	
	if(uart == 1)
	{
		div = 72000000;
		frac = 72000000.00;
	}
	
	div = div / (BR * 16);
	frac = 16 * ((frac / (BR * 16)) - div);
	dec = frac;
	frac2 = 100 * (frac - div);
	
	if(frac2 > 50)
	{
		dec++;
		if(dec == 16)
		{
			dec = 0;
			div++;
		}
	}
	
	final = (div<<4);
	final += dec;
	
	return final;
	
}

char uart_rx(unsigned short uart)
{
	char c;
	
	if(uart == 1)
	{
		while((USART1 -> SR & 0x20) == 0x00);
		c = USART1 -> DR;
	}
	else if(uart == 2)
	{
		while((USART2 -> SR & 0x20) == 0x00);
		c = USART2 -> DR;
	}
	else if(uart == 3)
	{
		while((USART3 -> SR & 0x20) == 0x00);
		c = USART3 -> DR;
	}
	
	return c;
}

void uart_tx(unsigned short uart, char c)
{
	if(uart == 1)
	{
		while((USART1 -> SR & 0x80) == 0x00);
		USART1 -> DR = c;
	}
	else if(uart == 2)
	{
		while((USART2 -> SR & 0x80) == 0x00);
		USART2 -> DR = c;
	}
	else if(uart == 3)
	{
		while((USART3 -> SR & 0x80) == 0x00);
		USART3 -> DR = c;
	}
}

void uart_string(unsigned short uart, char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		uart_tx(uart,str[i]);
		i++;
	}
}

void uart_str_empty(char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
}

int uart_length_str(char str[])
{
	int length = 0;
	while(str[length] != '\0')
	{
		length++;
	}
	
	// excluding the NULL character
	return (length - 1);
}




