#include "uart.h"
#include "systick.h"

/*
USART-2 
TX: 	PA2
RX: 	PA3
Baud: 9600
*/

int  n = 234;
char  c[10];

int main(void)
{
	systick_init();
	uart_init();
	
	while(1)
	{
		uart_tx_str("Converted data type");
		uart_tx('\n');
		int2char(n,c);
		uart_tx_str(c);
		uart_tx('\n');
		str_empty(c);
		delayms(500);
	}
}

