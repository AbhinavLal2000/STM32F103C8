#include "i2c.h"
#include "systick.h"

void systick_init(void)
{
	SysTick -> CTRL = 0;
	SysTick -> LOAD = 0x00FFFFFF;
	SysTick -> VAL = 0;
	SysTick -> CTRL |= 5;
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

void systick_int_start(void)
{
	__disable_irq();
	SysTick -> CTRL = 0;
	SysTick -> LOAD = 7200000;
	SysTick -> VAL = 0;
	SysTick -> CTRL |= 7;
	__enable_irq();
}

