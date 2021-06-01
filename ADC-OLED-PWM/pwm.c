#include "pwm.h"
#include "gpio.h"

// T2C1 TIM2 CH1 as PWM output: PA0
// T2C2 TIM2 CH2 as PWM output: PA1
// T3C3 TIM3 CH3 as PWM output: PB0
// T3C4 TIM3 CH4 as PWM output: PB1


/* T2C1 TIM2 CH1 as PWM output: PA0 */
void pwm_init_t2c1(void)
{
	initGPIO(PA,0,OUT50,OUT_AF_PP);				 	// Init PA0 as alternate function output at 50 MHz
	RCC  -> APB1ENR |= RCC_APB1ENR_TIM2EN; 	// Init clock for TIM2
	TIM2 -> CCER  	|= TIM_CCER_CC1E;			 	// Enable capture/compare
	TIM2 -> CR1   	|= TIM_CR1_ARPE;			 	// Enable auto-reload/preload
	TIM2 -> CCMR1 	|= TIM_CCMR1_OC1PE;		 	// Enable output compare preload
	TIM2 -> CCMR1 	|= TIM_CCMR1_OC1M_1;		// Enable output compare mode
	TIM2 -> CCMR1 	|= TIM_CCMR1_OC1M_2;	 	// Enable output compare mode
	TIM2 -> CCMR1 	&= ~TIM_CCMR1_CC1S;     // Enable channel output
	
	// Required freq. = 1KHz
	TIM2 -> PSC  = 72;	 									 	// Prescale value
	TIM2 -> ARR  = 1000; 										// ARR value FREQ
	TIM2 -> CCR1 = 500;	 									  // CCR value DUTY
	TIM2 -> EGR |= TIM_EGR_UG;  					 	// Update generation
	TIM2 -> CR1 |= TIM_CR1_CEN; 					 	// Enable Counter
}

/* T2C2 TIM2 CH2 as PWM output: PA1 */
void pwm_init_t2c2(void)
{
	initGPIO(PA,1,OUT50,OUT_AF_PP);				 	// Init PA1 as alternate function output at 50 MHz
	RCC  -> APB1ENR |= RCC_APB1ENR_TIM2EN; 	// Init clock for TIM2
	TIM2 -> CCER  	|= TIM_CCER_CC2E;			 	// Enable capture/compare
	TIM2 -> CR1   	|= TIM_CR1_ARPE;			 	// Enable auto-reload/preload
	TIM2 -> CCMR1 	|= TIM_CCMR1_OC2PE;		 	// Enable output compare preload
	TIM2 -> CCMR1 	|= TIM_CCMR1_OC2M_1;		// Enable output compare mode
	TIM2 -> CCMR1 	|= TIM_CCMR1_OC2M_2;	 	// Enable output compare mode
	TIM2 -> CCMR1 	&= ~TIM_CCMR1_CC2S;     // Enable channel output
	
	// Required freq. = 1KHz
	TIM2 -> PSC  = 72;	 									 	// Prescale value
	TIM2 -> ARR  = 1000; 										// ARR value FREQ
	TIM2 -> CCR2 = 500;	 									  // CCR value DUTY
	TIM2 -> EGR |= TIM_EGR_UG;  					 	// Update generation
	TIM2 -> CR1 |= TIM_CR1_CEN; 					 	// Enable Counter
}

/* T3C3 TIM3 CH3 as PWM output: PB0 */
void pwm_init_t3c3(void)
{
	initGPIO(PB,0,OUT50,OUT_AF_PP);				 	// Init PB0 as alternate function output at 50 MHz
	RCC  -> APB1ENR |= RCC_APB1ENR_TIM3EN; 	// Init clock for TIM3
	TIM3 -> CCER  	|= TIM_CCER_CC3E;			 	// Enable capture/compare
	TIM3 -> CR1   	|= TIM_CR1_ARPE;			 	// Enable auto-reload/preload
	TIM3 -> CCMR2 	|= TIM_CCMR2_OC3PE;		 	// Enable output compare preload
	TIM3 -> CCMR2 	|= TIM_CCMR2_OC3M_1;		// Enable output compare mode
	TIM3 -> CCMR2 	|= TIM_CCMR2_OC3M_2;	 	// Enable output compare mode
	TIM3 -> CCMR2 	&= ~TIM_CCMR2_CC3S;     // Enable channel output
	
	// Required freq. = 1KHz
	TIM3 -> PSC  = 72;	 									 	// Prescale value
	TIM3 -> ARR  = 1000; 										// ARR value FREQ
	TIM3 -> CCR3 = 500;	 									  // CCR value DUTY
	TIM3 -> EGR |= TIM_EGR_UG;  					 	// Update generation
	TIM3 -> CR1 |= TIM_CR1_CEN; 					 	// Enable Counter
}

/* T3C4 TIM3 CH4 as PWM output: PB1 */
void pwm_init_t3c4(void)
{
	initGPIO(PB,1,OUT50,OUT_AF_PP);				 	// Init PB1 as alternate function output at 50 MHz
	RCC  -> APB1ENR |= RCC_APB1ENR_TIM3EN; 	// Init clock for TIM3
	TIM3 -> CCER  	|= TIM_CCER_CC4E;			 	// Enable capture/compare
	TIM3 -> CR1   	|= TIM_CR1_ARPE;			 	// Enable auto-reload/preload
	TIM3 -> CCMR2 	|= TIM_CCMR2_OC4PE;		 	// Enable output compare preload
	TIM3 -> CCMR2 	|= TIM_CCMR2_OC4M_1;		// Enable output compare mode
	TIM3 -> CCMR2 	|= TIM_CCMR2_OC4M_2;	 	// Enable output compare mode
	TIM3 -> CCMR2 	&= ~TIM_CCMR2_CC4S;     // Enable channel output
	
	// Required freq. = 1KHz
	TIM3 -> PSC  = 72;	 									 	// Prescale value
	TIM3 -> ARR  = 1000; 										// ARR value FREQ
	TIM3 -> CCR4 = 500;	 									  // CCR value DUTY
	TIM3 -> EGR |= TIM_EGR_UG;  					 	// Update generation
	TIM3 -> CR1 |= TIM_CR1_CEN; 					 	// Enable Counter
}
