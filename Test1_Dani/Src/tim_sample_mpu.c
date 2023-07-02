#include "stm32f4xx.h"


#define TIM2EN	(1U<<0)
#define CR1_CEN	(1U<<0)
#define DIER_UIE (1U<<0)

float tim2_1hz_init(void)
{
	/*enable clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 1600-1;  // (clk_freq) 16 000 000 / (prescaler) 1600 = 10 000

	/*Set auto-reload value*/
	TIM2->ARR = 10000-1;  // 10 000 / 10 000 = 1

	/*Clear counter*/
	TIM2->CNT = 0;	// komplettes Register Null-setzen

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;

	/*Enable TIM interrupt*/
	TIM2->DIER |= DIER_UIE;

	/*Enable TIM interrupt in NVIC*/
	NVIC_EnableIRQ(TIM2_IRQn);


	return 1;
}


float tim2_1khz_interrupt_init(void)
{
	/*enable clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 16-1;  // (clk_freq) 16 000 000/ (prescaler) 16 = 1 000 000 (1MHz)

	/*Set auto-reload value*/
	TIM2->ARR = 1000-1;  // 1 000 / 1 000 000 = 1e-3s = 1 ms

	/*Clear counter*/
	TIM2->CNT = 0;	// komplettes Register Null-setzen

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;

	/*Enable TIM interrupt*/
	TIM2->DIER |= DIER_UIE;

	/*Enable TIM interrupt in NVIC*/
	NVIC_EnableIRQ(TIM2_IRQn);

	return 0.001;
}


float tim2_500hz_interrupt_init(void)
{
	/*enable clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 16-1;  // (clk_freq) 16 000 000/ (prescaler) 16 = 1 000 000 (1MHz)

	/*Set auto-reload value*/
	TIM2->ARR = 2000-1;  // 2 000 / 1 000 000 = 2e-3s = 2 ms -> 500Hz

	/*Clear counter*/
	TIM2->CNT = 0;	// komplettes Register Null-setzen

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;

	/*Enable TIM interrupt*/
	TIM2->DIER |= DIER_UIE;

	/*Enable TIM interrupt in NVIC*/
	NVIC_EnableIRQ(TIM2_IRQn);

	return 0.002;

}

float tim2_100hz_interrupt_init(void)
{
	/*enable clock access to tim2*/
	RCC->APB1ENR |= TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 16-1;  // (clk_freq) 16 000 000/ (prescaler) 16 = 1 000 000 (1MHz)

	/*Set auto-reload value*/
	TIM2->ARR = 10000-1;  // 10 000 / 1 000 000 = 10e-2s = 100ms -> 100Hz

	/*Clear counter*/
	TIM2->CNT = 0;	// komplettes Register Null-setzen

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;

	/*Enable TIM interrupt*/
	TIM2->DIER |= DIER_UIE;

	/*Enable TIM interrupt in NVIC*/
	NVIC_EnableIRQ(TIM2_IRQn);

	return 0.01;

}
