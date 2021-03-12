#include <stm32f10x.h>
#include "systick.h"
#include "spi.h"

/*
SPI-1 PINs setup

PA4 NSS
PA5	SCLK
PA6	MISO
PA7	MOSI
*/

void spi1_init(void)
{
	// SPI-1 enable
	RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
			
	// set PIN A4 50 MHz OP GP PP
	GPIOA -> CRL |= (1<<16 | 1<<17);
	GPIOA -> CRL &= ~(1<<18 | 1<<19);
			
	// set PIN A5 50 MHz OP AF PP
	GPIOA -> CRL |= (1<<20 | 1<<21 | 1<<23);
	GPIOA -> CRL &= ~(1<<22);
			
	// set PIN A6 INPUT PU-PD
	GPIOA -> CRL &= ~(1<<24 | 1<<25 | 1<<26);
	GPIOA -> CRL |= (1<<27);
			
	// set PIN A7 50 MHz OP AF PP
	GPIOA -> CRL |= (1<<28 | 1<<29 | 1<<31);
	GPIOA -> CRL &= ~(1<<30);
			
	// SPI-1 setup
			
	// set MASTER mode
	SPI1 -> CR1 |= SPI_CR1_MSTR;
			
	// set baud rate as fPCLK/256
	SPI1 -> CR1 |= 0x38;
			
	// set SS output enable
	SPI1 -> CR2 |= SPI_CR2_SSOE;
			
	// enable SPI
	SPI1 -> CR1 |= SPI_CR1_SPE;
			
	// make PA4 HIGH
	GPIOA -> ODR |= (1<<4);
	
}


void spi1_char(char tx_char)
{
	GPIOA -> ODR &= ~(1<<4);
	SPI1 -> DR = tx_char;
	while(SPI1 -> SR & 0x80){}
	GPIOA -> ODR |= (1<<4);
}

void spi1_string(char str[])
{
	int i = 0;
	GPIOA -> ODR &= ~(1<<4);
	while(str[i])
	{
		SPI1 -> DR = str[i];
		while(SPI1 -> SR & SPI_SR_BSY){}
		i++;
	}
	GPIOA -> ODR |= (1<<4);
}

