#include <stm32f10x.h>
#include "systick.h"
#include "uart.h"

/* 
UART PINs

UART1 PA9 	TX PA10 RX		72 MHz max clock
UART2 PA2 	TX PA3 	RX		36 MHz max clock
UART3 PB10 	TX PB11 RX		36 MHz max clock

*/

char c = 0;

int main(void)
{
	systick_init();
	uart_init(2,9600);
	
	while(1)
	{
		c = uart_rx(2);
		uart_tx(2,c);	
	}
}

