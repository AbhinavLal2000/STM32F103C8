#include <stm32f10x.h>
#include "spi.h"

int main()
{
	systick_init();
	spi1_init();
	
	while(1)
	{
		spi1_char(0x2F);
	}
	
}
