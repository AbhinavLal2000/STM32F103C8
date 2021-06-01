#include "pwm.h"
#include "systick.h"

// T2C1 TIM2 CH1 as PWM output: PA 0
// T2C2 TIM2 CH2 as PWM output: PA 1
// T3C3 TIM3 CH3 as PWM output: PB 0
// T3C4 TIM3 CH4 as PWM output: PB 1

int i = 0;

int main(void)
{
	systick_init();
	servo_init(PA,0);

	while(1)
	{
		for(i=0;i<=180;i++)
		{
			servo_write(i,PA,0);
			delayms(5);
		}
		
		delayms(30);
		
		for(i=180;i>=0;i--)
		{
			servo_write(i,PA,0);
			delayms(5);
		}
		delayms(30);
	}
}
