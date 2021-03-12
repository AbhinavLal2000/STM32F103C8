#ifndef LCD_header
#define LCD_header

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

// pins in use: B12, B13, B14, B15, A8, A9, A10, A11, A12, B5

#define D0 12 // B12
#define GPIO_D0 GPIOB
#define D1 13 // B13
#define GPIO_D1 GPIOB
#define D2 14 // B14
#define GPIO_D2 GPIOB
#define D3 15 // B15
#define GPIO_D3 GPIOB
#define	D4 8 	// A8
#define GPIO_D4 GPIOA
#define	D5 9	// A9
#define GPIO_D5 GPIOA
#define	D6 10 // A10
#define GPIO_D6 GPIOA
#define	D7 11 // A11
#define GPIO_D7 GPIOA
#define EN 12 // A12
#define GPIO_EN GPIOA
#define RS 5 // B5
#define GPIO_RS GPIOB
#define w 80000

void LCD_bit(GPIO_TypeDef *gpio, unsigned int pin, uint8_t bitState);
void LCD_char(unsigned char a);
void LCD_init(void);
void LCD_cmd(unsigned char cmd);
void wait(volatile int d);
void LCD_data(unsigned char data);
void LCD_start(void);
void LCD_string(unsigned char *s);
void LCD_int(unsigned int i, unsigned int l);
void LCD_float(double i, unsigned int l);
void LCD_cur_right(int i);

void wait(volatile int d)
{
	for(volatile int i=0;i<d;i++);
}

void LCD_bit(GPIO_TypeDef *gpio, unsigned int pin, uint8_t bitState)
{
	if(bitState)
		gpio -> BSRR = (1<<pin);
	else
		gpio -> BRR = 1<<pin;
}


void LCD_char(unsigned char a)
{
	LCD_bit(GPIO_D0, D0, a & 0b00000001);
	LCD_bit(GPIO_D1, D1, a & 0b00000010);
	LCD_bit(GPIO_D2, D2, a & 0b00000100);
	LCD_bit(GPIO_D3, D3, a & 0b00001000);
	LCD_bit(GPIO_D4, D4, a & 0b00010000);
	LCD_bit(GPIO_D5, D5, a & 0b00100000);
	LCD_bit(GPIO_D6, D6, a & 0b01000000);
	LCD_bit(GPIO_D7, D7, a & 0b10000000);
	wait(w);
	GPIO_EN -> BRR = 1<<EN;
}

void LCD_init(void)
{
	// set clock for GPIOA and GPIOB
	RCC -> APB2ENR |= (1<<2) | (1<<3);
	
	// configure GPIOA for output
	
	// configuring for A8
	GPIOA -> CRH |= (1<<0) | (1<<1);
	GPIOA -> CRH &= ~((1<<2) | (1<<3));
	// configuring for A9
	GPIOA -> CRH |= (1<<4) | (1<<5);
	GPIOA -> CRH &= ~((1<<6) | (1<<7));
	// configuring for A10
	GPIOA -> CRH |= (1<<8) | (1<<9);
	GPIOA -> CRH &= ~((1<<10) | (1<<11));
	// configuring for A11
	GPIOA -> CRH |= (1<<12) | (1<<13);
	GPIOA -> CRH &= ~((1<<14) | (1<<15));
	// configuring for A12
	GPIOA -> CRH |= (1<<16) | (1<<17);
	GPIOA -> CRH &= ~((1<<18) | (1<<19));
	
	// configure GPIOB for output
	
	// configuring for B12
	GPIOB -> CRH |= (1<<16) | (1<<17);
	GPIOB -> CRH &= ~((1<<18) | (1<<19));
	// configuring for B13
	GPIOB -> CRH |= (1<<20) | (1<<21);
	GPIOB -> CRH &= ~((1<<22) | (1<<23));
	// configuring for B14
	GPIOB -> CRH |= (1<<24) | (1<<25);
	GPIOB -> CRH &= ~((1<<26) | (1<<27));
	// configuring for B15
	GPIOB -> CRH |= (1<<28) | (1<<29);
	GPIOB -> CRH &= ~((1<<30) | (1<<31));
	// configuring for B5
	GPIOB -> CRL |= (1<<20) | (1<<21);
	GPIOB -> CRL &= ~((1<<22) | (1<<23));
}

void LCD_cmd(unsigned char cmd)
{
	GPIO_RS -> BRR = 1<<RS;
	wait(w);
	GPIO_EN -> BSRR = 1<<EN;
	LCD_char(cmd);
}

void LCD_data(unsigned char data)
{
	GPIO_RS -> BSRR = 1<<RS;
	wait(w);
	GPIO_EN -> BSRR = 1<<EN;
	LCD_char(data);
}

void LCD_start(void)
{
	LCD_cmd(0x38);
	LCD_cmd(0x0E);
	LCD_cmd(0x01);
}

void LCD_string(unsigned char *s)
{
	while(*s)
	{
		LCD_data(*s++);
	}
}

void LCD_int(unsigned int i, unsigned int l)
{
	char str[l];
	sprintf(str,"%d",i);
	strcat(str," ");
	LCD_string(str);
}

void LCD_float(double i, unsigned int l)
{
	char str[l];
	snprintf(str,l+1,"%f",i);
	LCD_string(str);
}
void LCD_cur_right(int i)
{
	for(int j=0;j<=i;j++)
	{
		LCD_cmd(0x06);
	}
}

#endif
