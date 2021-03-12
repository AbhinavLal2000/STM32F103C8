void uart_init(unsigned short uart, unsigned long BR);
unsigned long uart_brr_cal(unsigned short uart, unsigned long BR);
char uart_rx(unsigned short uart);
void uart_tx(unsigned short uart, char c);
void uart_string(unsigned short uart, char str[]);
void uart_str_empty(char str[]);
int uart_length_str(char str[]);



