#include "stm32f10x.h"

/*
GPIO header for STM32F103C8 Bluepill board
*/

// RCC->APB2ENR base address
#define RCC_APB2ENR (*((volatile unsigned long *) 0x40021018))

// GPIO A,B and C base address 
#define GPIO_A			(*((volatile unsigned long *) 0x40010800))
#define GPIO_B			(*((volatile unsigned long *) 0x40010C00))
#define GPIO_C			(*((volatile unsigned long *) 0x40011000))

// port
#define PA					1
#define PB					2
#define PC					3

// dirn
#define IN					0 	// input
#define OUT10				1 	// output 10 MHz
#define OUT20				2 	// output 20 MHz
#define OUT50				3 	// output 50 MHz

// option
#define IN_AN				0		// analog input
#define IN_FL				1		// floating input
#define IN_PP				2 	// push-pull input
#define OUT_GP_PP		0 	// general purpose push-pull output
#define OUT_GP_OD		1 	// general purpose open-drain output
#define OUT_AF_PP		2 	// alternate function push-pull output
#define OUT_AF_OD		3 	// alternate function open-drain output

// status
#define LOW					0
#define HIGH				1

void initGPIO(unsigned short port, unsigned short pin, unsigned short dirn, unsigned short option);
int readGPIO(unsigned short port, unsigned short pin);
void writeGPIO(unsigned short port, unsigned short pin, unsigned short state);
void toggleGPIO(unsigned short port, unsigned short pin);
