/*
 * tim.h
 *
 *  Created on: 29.03.2023
 *      Author: Domin
 */

#ifndef TIM_SAMPLE_MPU_H_
#define TIM_SAMPLE_MPU_H_


void tim2_1hz_init(void);
void tim2_1khz_interrupt_init(void);


#define SR_UIF	(1U<<0)
#endif /* TIM_SAMPLE_MPU_H_ */
