#include "oled.h"
/*
OLED GM009605 v4.2 SSD1306
VDD 3.3V
*/

/*
I2C-2 pins
PB10 SCL
PB11 SDA
*/


void oled_cmd_1byte(char data)
{
	i2c2_start();

	i2c2_address(0x78,0);
	
	// 0x00 for command
	i2c2_data(0x00);
	
	i2c2_data(data);
	
	i2c2_stop();
}

void oled_cmd_2byte(char data[])
{
	i2c2_start();

	i2c2_address(0x78,0);
	
	// 0x00 for command
	i2c2_data(0x00);
	
	for(int i=0;i<2;i++)
	{
		i2c2_data(data[i]);
	}
	
	i2c2_stop();
}

void oled_init(void)
{
	i2c2_init(i2c_FM);
	
	// set mux ratio
	char cmd[] = {0xA8,0x3F};
	oled_cmd_2byte(cmd);
	
	// set display offset
	char cmd1[] = {0xD3,0x00};
	oled_cmd_2byte(cmd1);
	
	// set display start line
	oled_cmd_1byte(0x40);
	
	// set segment re-map A0/A1
	oled_cmd_1byte(0xA1);
	
	// set COM output scan direction C0/C8
	oled_cmd_1byte(0xC8);
	
	// set COM pins hardware config
	char cmd2[] = {0xDA,0x12};
	oled_cmd_2byte(cmd2);
	
	// set contrast
	char cmd3[] = {0x81,0x7F};
	oled_cmd_2byte(cmd3);
	
	// disable entire display on
	oled_cmd_1byte(0xA4);
	
	// set normal display
	oled_cmd_1byte(0xA6);
	
	// set osc freq.
	char cmd4[] = {0xD5,0x80};
	oled_cmd_2byte(cmd4);
	
	// enable charge pump reg.
	char cmd5[] = {0x8D,0x14};
	oled_cmd_2byte(cmd5);
	
	// display ON
	oled_cmd_1byte(0xAF);
	
	// sampling direction
	char cmd6[] = {0x20,0x10};
	oled_cmd_2byte(cmd6);
	
}

void oled_data(char data)
{
	i2c2_start();

	i2c2_address(0x78,0);
	
	// 0x40 for data
	i2c2_data(0x40);
	
	i2c2_data(data);
	
	i2c2_stop();
}

void oled_pos(char ypos, char xpos)
{
	oled_cmd_1byte(0x00 + (0x0F & xpos));
	oled_cmd_1byte(0x10 + (0x0F & (xpos >> 4)));
	oled_cmd_1byte(0xB0 + ypos);
}

void oled_clear(void)
{
	oled_pos(0,0);
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<128;j++)
		{
			oled_data(0x00);
		}
	}
	oled_pos(0,0);
}

void oled_print(char str[])
{
	int i=0;
	while(str[i])
	{
		for(int j=0;j<5;j++)
		{
			oled_data(ASCII[(str[i] - 32)][j]);
		}
		i++;
	}
}

void oled_print_pos(char ypos, char xpos,char str[])
{
	oled_pos(ypos,xpos);
	oled_print(str);
}
