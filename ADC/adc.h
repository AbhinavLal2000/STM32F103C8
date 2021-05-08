#include "gpio.h"
#include "systick.h"

#define adc1 1
#define adc2 2

char adc_init(char adc, short port, short pin);
char adc_check(char adc, short port, short pin);
int adc_read(char adc, short port, short pin);

