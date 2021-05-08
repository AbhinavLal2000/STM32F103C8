#include "uart.h"

/*
USART-2 Library 
TX: 	PA2
RX: 	PA3
Baud: 9600
*/

void uart_init(void)
{
	// init alternate function i/o clock
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// init USART2 
	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;
	
	// init pin PA2 TX 
	initGPIO(PA,2,OUT50,OUT_AF_PP);
	
	// init pin PA3 RX
	initGPIO(PA,3,IN,IN_PP);
	
	// set baud rate = 9600 bps
	USART2 -> BRR = 0xEA6;
	
	// enable USART, Tx and Rx
	USART2 -> CR1 |= USART_CR1_UE;
	USART2 -> CR1 |= USART_CR1_TE;
	USART2 -> CR1 |= USART_CR1_RE;
}

void uart_tx(char c)
{
		while((USART2 -> SR & 0x80) == 0x00);
		USART2 -> DR = c;
}

char uart_rx(void)
{
	char c;
	
	while((USART2 -> SR & 0x20) == 0x00);
	c = USART2 -> DR;
	
	return c;
}

void int2char(int num, char str[])
{
	char lstr[30];
	int  cnt = 	 0;
	int  div = 	10;
	int  j   = 	 0;
	int  neg = 	 0;
	
	if(num < 0)
	{
		num =-num;
		neg = 1;
	}

	while( num >= div)
	{
		lstr[cnt] = num % div + 0x30;
		num /= 10;
		cnt++;
	}

	lstr[cnt] = num + 0x30;

	if(neg)
	{
		cnt++;
		lstr[cnt] = '-';
	}
	
	for(j= cnt ; j >=0;j--)
	{
		str[cnt-j] = lstr[j];
	}

}

void uart_tx_str(char str[])
{
	int i = 0;
	
	while(str[i] != '\0')
	{
		uart_tx(str[i]);
		i++;
	}
}

void str_empty(char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
	
}
