#include "adc.h"
#include "uart.h"

/*
ADC input: 	PA0
USART-2 TX: PA2
baud:				9600
*/

int  v = 0;
char n[10];

int main(void)
{
	systick_init();
	uart_init();
	adc_init(adc1,PA,0);
	uart_tx_str("Initialised");
	uart_tx('\n');
	
	while(1)
	{
		if(adc_check(adc1,PA,0))
		{
			v = adc_read(adc1,PA,0);
			int2char(v,n);
			uart_tx_str(n);
			str_empty(n);
			uart_tx('\n');
			delayms(500);
		}
	}
	
}
