
#ifndef TIM_SAMPLE_MPU_H_
#define TIM_SAMPLE_MPU_H_


float tim2_1hz_init(void);
float tim2_1khz_interrupt_init(void);
float tim2_500hz_interrupt_init(void);
float tim2_100hz_interrupt_init(void);

#define SR_UIF	(1U<<0)
#endif /* TIM_SAMPLE_MPU_H_ */
