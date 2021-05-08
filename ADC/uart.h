#include "gpio.h"

/*
USART-2 Library 
TX: 	PA2
RX: 	PA3
Baud: 9600
*/

void uart_init(void);
void uart_tx(char c);
char uart_rx(void);
void int2char(int num, char str[]);
void uart_tx_str(char str[]);
void str_empty(char str[]);
