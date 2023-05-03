#include "systick.h"

#define SYSTICK_LOAD_VAL	3200

#define CTRL_ENABLE		(1U<<0)
#define CTRL_TICKINT	(1U<<1)
#define CTRL_CLKSRC		(1U<<2)

void systick_counter_init(void)
{
	/*Disable systick before setup*/
	SysTick->CTRL = 0;

	/*Load Systick reload register with maximum value*/
	SysTick->LOAD = 0x00FFFFFF;

	/*Clear Systick current value register*/
	SysTick->VAL = 0;

	/*Select internal clock source and enable SysTick*/
	SysTick->CTRL = CTRL_CLKSRC | CTRL_ENABLE;


}

