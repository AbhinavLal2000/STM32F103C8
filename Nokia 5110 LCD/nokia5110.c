#include <stm32f10x.h>
#include "systick.h"
#include "spi.h"
#include "nokia5110.h"

/*
LCD PINs

PA0 RST
PA1 DC
PA2 BL
PA4 CE/SS
PA5 CLK
PA7 DIN/MOSI

3.3V VCC

*/

void nokia5110_init(void)
{
	// alternate funtion
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// GPIO-A clock enable
	RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// PA0 RST 50 MHz GP OP PP
	GPIOA -> CRL |= (1<<0 | 1<<1);
	GPIOA -> CRL &= ~(1<<2 | 1<<3);
	
	// RST HIGH ,LOW, HIGH
	//GPIOA -> ODR |= 1<<0;
	//delayms(10);
	GPIOA -> ODR &= ~(1<<0);
	delayms(10);
	GPIOA -> ODR |= 1<<0;
	
	// PA1 DC 50 MHz GP OP PP
	GPIOA -> CRL |= (1<<4 | 1<<5);
	GPIOA -> CRL &= ~(1<<6 | 1<<7);
	
	// set LOW DC 
	GPIOA -> ODR &= ~(1<<1);
	
	// PA2 BL 50 MHz GP OP PP
	GPIOA -> CRL |= (1<<8 | 1<<9);
	GPIOA -> CRL &= ~(1<<10 | 1<<11);
	
	// testing backlight PA2
	GPIOA -> ODR |= (1<<2);

	
	/****** LCD setup *****/
	
	// initialise SPI-1
	spi1_init();

	// extended instruction set PD = 0, V = 0, H = 1
	spi1_char(0x21);
	
	// temp. coefficient TC1 = 0, TC0 = 1
	spi1_char(0x06);
	
	// set bias
	spi1_char(0x17);
	
	// Vop contrast
	spi1_char(0x97);
	
	// basic instruction set PD = 0, V = 0, H = 0
	spi1_char(0x20);
	
	// display control: inverse mode D = 1, E = 0
	spi1_char(0x0C);
}

void nokia5110_print(short ypos, short xpos, char str[])
{
	int i = 0, j;
	
	// write string
	nokia5110_pos(ypos,xpos);
	GPIOA -> ODR |= (1<<1);
	while(str[i])
	{
		for(j=0;j<5;j++)
		{
			spi1_char(ASCII[str[i]-32][j]);
		}
		
		i++;
	}
	GPIOA -> ODR &= ~(1<<1);
}

void nokia5110_pos(short ypos, short xpos)
{
	GPIOA -> ODR &= ~(1<<1);
	spi1_char(0x20);
	spi1_char(0x40 | ypos);
	spi1_char(0x80 | xpos);
}

void nokia5110_clear(void)
{
	nokia5110_pos(0,0);
	GPIOA -> ODR |= (1<<1);
	for(int j=0;j<504;j++)
	{
		spi1_char(0x00);
	}
	GPIOA -> ODR &= ~(1<<1);
}

void nokia5110_clear_buffer(unsigned char screen_buffer[][84])
{
	int i,j;
	for(i=0;i<6;i++)
	{
		for(j=0;j<84;j++)
		{
			screen_buffer[i][j] = 0;
		}
	}
}

void nokia5110_print_buffer(unsigned char screen_buffer[][84])
{
	nokia5110_clear();
	nokia5110_pos(0,0);
	int i,j;
	
	GPIOA -> ODR |= (1<<1);
	for(i=0;i<6;i++)
	{
		for(j=0;j<84;j++)
		{
			spi1_char(screen_buffer[i][j]);
		}
	}
	GPIOA -> ODR &= ~(1<<1);
}

void nokia5110_update_buffer(ImgType img, unsigned short img_num, unsigned char screen_buffer[][84])
{
	int x_dir, y_dir, end_x, end_y, count;
	
	if((img.w + img.xpos) > 84)
	{
		end_x = 83;
	}
	else
	{
		end_x = img.w + img.xpos - 1;
	}
	if((img.h + img.ypos) > 5)
	{
		end_y = 5;
	}
	else
	{
		end_y = img.h + img.ypos - 1;
	}
	
	count = 0;
	
	for(y_dir = img.ypos;y_dir <= end_y;y_dir++)
	{
		for(x_dir = img.xpos;x_dir <= end_x;x_dir++)
		{
			count = (y_dir - img.ypos) * img.w + x_dir - img.xpos;
			screen_buffer[y_dir][x_dir] = img.image[img_num][count];
		}
	}
	
}

void nokia5110_update_str_buffer(short y_pos, short x_pos, char str[], unsigned char screen_buffer[][84])
{
	int i,j,count_col,count_row;
	
	count_col = x_pos;
	count_row = y_pos;
	i = 0;
	while(str[i])
	{
		if(count_row > 5)
		{
			break;
		}
		for(j = 0;j < 5;j++)
		{
			screen_buffer[count_row][count_col] = ASCII[str[i] - 32][j];
			if((count_col + 1) > 83)
			{
				if((count_row + 1) > 5)
				{
					break;
				}
				else
				{
					count_row++;
					count_col = x_pos;
					
				}
			}
			else
			{
				count_col++;
			}
		}
		i++;
	}
}

/*void walkman(void)
{
	int i,j;
	ImgType walkmen = {.h = walkmen_4_rows, .w = walkmen_4_cols, .xpos = 0, .ypos = 0};
	walkmen.image[0] = walkmen_0;
	walkmen.image[1] = walkmen_1;
	walkmen.image[2] = walkmen_2;
	walkmen.image[3] = walkmen_3;
	walkmen.image[4] = walkmen_4;
	
	nokia5110_clear();
	nokia5110_clear_buffer(nokia5110_buffer);
	
	for(i=0;i<83;i++)
		{
			walkmen.xpos = i;
			if(i == 32)
			{
				nokia5110_clear_buffer(nokia5110_buffer);
				nokia5110_update_buffer(walkmen,j,nokia5110_buffer);
				nokia5110_update_str_buffer(5,40,"Abhinav",nokia5110_buffer);
				nokia5110_print_buffer(nokia5110_buffer);
				delayms(2000);
			}
			else
			{
				for(j=0;j<4;j++)
				{
					nokia5110_clear_buffer(nokia5110_buffer);
					nokia5110_update_buffer(walkmen,j,nokia5110_buffer);
					nokia5110_print_buffer(nokia5110_buffer);
					delayms(50);
				}
			}
			
		}
}*/











