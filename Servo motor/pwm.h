#include "stm32f10x.h"
void pwm_init_t2c1(void);
void pwm_init_t2c2(void);
void pwm_init_t3c3(void);
void pwm_init_t3c4(void);
void servo_init(unsigned short port, unsigned short pin);
unsigned int map(unsigned int x, unsigned int in_min, unsigned int in_max, unsigned int out_min, unsigned int out_max);
void servo_write(unsigned int angle, unsigned short port, unsigned short pin);
