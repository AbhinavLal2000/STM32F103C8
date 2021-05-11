#include "stm32f10x.h"

#define i2c_FM 0x2D
#define i2c_SM 0xB4

void i2c2_init(unsigned short speed);
void i2c2_start(void);
void i2c2_address(char address, char rw);
void i2c2_data(char data);
void i2c2_stop(void);
void i2c2_write(char address, char data[]);
