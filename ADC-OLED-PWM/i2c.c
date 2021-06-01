#include "i2c.h"

/*
I2C-2 pins
PB10 SCL
PB11 SDA
*/

void i2c2_init(unsigned short speed)
{
	// Enable AFIO clock
	RCC -> APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	// Enable PORT-B clock
	RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
	
	// Enable I2C-2 clock
	RCC -> APB1ENR |= RCC_APB1ENR_I2C2EN;
		
	// Pin B10 OUT 50MHz AF open-drain
	GPIOB -> CRH |= (1<<8 | 1<<9 | 1<<10 | 1<<11);
		
	// Pin B11 OUT 50MHz AF open-drain
	GPIOB -> CRH |= (1<<12 | 1<<13 | 1<<14 | 1<<15);
		
	
	// I2C-2 setup
		
	// SWRST
	I2C2 -> CR1 |= I2C_CR1_SWRST;
	I2C2 -> CR1 &= ~(I2C_CR1_SWRST);
		
	// FREQ
	I2C2 -> CR2 |= 0x8; // 0b00001000
		
	// Speed mode
	I2C2 -> CCR |= speed;
		
	// TRISE
	I2C2 -> TRISE |= 0x9;
		
	// Enable I2C peripheral
	I2C2 -> CR1 |= I2C_CR1_PE;
	
}

void i2c2_start(void)
{
	// Set START bit in CR1
	I2C2 -> CR1 |= I2C_CR1_START;
		
	// wait until SB gets clear
	while (!(I2C2 -> SR1 & I2C_SR1_SB)){};
}

void i2c2_address(char address, char rw)
{
	volatile int tmp;

	I2C2 -> DR = (address | rw);
	while((I2C2 -> SR1 & I2C_SR1_ADDR) == 0){};
	while((I2C2 -> SR1 & I2C_SR1_ADDR))
	{
		tmp = I2C2 -> SR1;
		tmp = I2C2 -> SR2;
		if((I2C2 -> SR1 & I2C_SR1_ADDR) == 0)
		{
			break;
		}
	}
	
}

void i2c2_data(char data)
{
	while((I2C2 -> SR1 & I2C_SR1_TXE) == 0){}
	I2C2 -> DR = data;
	while((I2C2 -> SR1 & I2C_SR1_TXE) == 0){}
}

void i2c2_stop(void)
{
	volatile int tmp;
	tmp = I2C2 -> SR1;
	tmp = I2C2 -> SR2;
	I2C2 -> CR1 |= I2C_CR1_STOP;
}

void i2c2_write(char address, char data[])
{
	int i = 0;
	i2c2_start();
	i2c2_address(address,0);
	while(data[i])
	{
		i2c2_data(data[i]);
		i++;
	}
	i2c2_stop();
	
}
