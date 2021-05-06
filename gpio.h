/*
This GPIO header in compatible with STM32F103C8 Bluepill board
*/

// RCC->APB2ENR base address
#define RCC_APB2ENR (*((volatile unsigned long *) 0x40021018))

// GPIO A,B and C base address 
#define GPIO_A		(*((volatile unsigned long *) 0x40010800))
#define GPIO_B		(*((volatile unsigned long *) 0x40010C00))
#define GPIO_C		(*((volatile unsigned long *) 0x40011000))

// port
#define PA				1
#define PB				2
#define PC				3

// dirn
#define IN				0 	// input
#define OUT10			1 	// output 10 MHz
#define OUT20			2 	// output 20 MHz
#define OUT50			3 	// output 50 MHz

// option
#define IN_AN			0	// analog input
#define IN_FL			1	// floating input
#define IN_PP			2 	// push-pull input
#define OUT_GP_PP		0 	// general purpose push-pull output
#define OUT_GP_OD		1 	// general purpose open-drain output
#define OUT_AF_PP		2 	// alternate function push-pull output
#define OUT_AF_OD		3 	// alternate function open-drain output

// status
#define LOW				0
#define HIGH			1

void initGPIO(unsigned short port, unsigned short pin, unsigned short dirn, unsigned short option);
int readGPIO(unsigned short port, unsigned short pin);
void writeGPIO(unsigned short port, unsigned short pin, unsigned short state);
void toggleGPIO(unsigned short port, unsigned short pin);


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

