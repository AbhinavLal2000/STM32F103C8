/*
SPI-1 PINs setup

PA4 NSS
PA5	SCLK
PA6	MISO
PA7	MOSI
*/

void spi1_init(void);
void spi1_char(char tx_char);
void spi1_string(char str[]);
void systick_int_start(void);
