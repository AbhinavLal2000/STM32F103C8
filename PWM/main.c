#include "pwm.h"
#include "systick.h"

// T2C1 TIM2 CH1 as PWM output: PA0
// T2C2 TIM2 CH2 as PWM output: PA1
// T3C3 TIM3 CH3 as PWM output: PB0
// T3C4 TIM3 CH4 as PWM output: PB1

int main(void)
{
	systick_init();
	pwm_init_t2c1();
	pwm_init_t2c2();
	pwm_init_t3c3();
	pwm_init_t3c4();

	while(1)
	{
		for(int i=0;i<=700;i++)
		{
			TIM2 -> CCR1 = i;
			TIM2 -> CCR2 = i;
			TIM3 -> CCR3 = i;
			TIM3 -> CCR4 = i;
			delayms(5);
		}
		for(int i=700;i>=0;i--)
		{
			TIM2 -> CCR1 = i;
			TIM2 -> CCR2 = i;
			TIM3 -> CCR3 = i;
			TIM3 -> CCR4 = i;
			delayms(5);
		}
	}
}
