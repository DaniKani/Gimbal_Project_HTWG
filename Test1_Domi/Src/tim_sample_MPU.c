#include "stm32f4xx.h"


#define TIM2EN	(1U<<0)
#define CR1_CEN	(1U<<0)
#define DIER_UIE (1U<<0)


void tim2_1khz_interrupt_init(void)
{
	/*enable clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 1600-1;  // (clk_freq) 16 000 000 / (prescaler) 16 00 = 10 000 Hz

	/*Set auto-reload value*/
	TIM2->ARR = 100-1;  // 10 / 10 000 = 0,010s

	/*Clear counter*/
	TIM2->CNT = 0;	// komplettes Register Null-setzen

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;

	/*Enable TIM interrupt*/
	TIM2->DIER |= DIER_UIE;

	/*Enable TIM interrupt in NVIC*/
	NVIC_EnableIRQ(TIM2_IRQn);
}
