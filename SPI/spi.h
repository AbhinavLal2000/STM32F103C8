#include <stm32f10x.h>
/*
SPI-1 PINs setup

PA4 NSS
PA5	SCLK
PA6	MISO
PA7	MOSI

*/
void systick_init(void);
void delaymillis(void);
void delayms(unsigned long t);

void spi1_init(void);
void spi1_char(char tx_char);
void spi1_string(char str[]);



void spi1_init(void)
{
	// alternate funtion
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
			
	// SPI-1 enable
	RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
			
	// GPIO-A clock enable
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
			
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
	delayms(50);
	GPIOA -> ODR &= ~(1<<4);
	SPI1 -> DR = tx_char;
	while(SPI1 -> SR & 0x80);
	GPIOA -> ODR |= (1<<4);
}

void spi1_string(char str[])
{
	int i = 0;
	delayms(50);
	GPIOA -> ODR &= ~(1<<4);
	while(str[i])
	{
		SPI1 -> DR = str[i];
		while(SPI1 -> SR & SPI_SR_BSY){}
		i++;
	}
	GPIOA -> ODR |= (1<<4);
}

void systick_init(void)
{
	SysTick -> CTRL = 0;
	SysTick -> LOAD = 0x00FFFFFF;
	SysTick -> VAL = 0;
	SysTick -> CTRL = 5;
}

void delaymillis(void)
{
	SysTick -> LOAD = 72000 - 1;
	SysTick -> VAL = 0;
	while((SysTick -> CTRL & 0x00010000) == 0);
}

void delayms(unsigned long t)
{
	for(;t>0;t--)
	{
		delaymillis();
	}
}

