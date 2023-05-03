#include "stm32f4xx.h"
#include <stdio.h>
#include "dma.h"
#include "adc_dma.h"
#include "mpu9250.h"
#include <string.h>
#include "uart.h"
#include "tim_sample_MPU.h"
#include "systick.h"
#include "Gyr_Acc_Calibration.h"

Offset_value_gyro gyro_offset;
Offset_value_acc acc_offset_scale;
uint16_t measurement_cnt = 0;

uint8_t tim = 0;

float acc_x,acc_y,acc_z;
float gyro_x,gyro_y,gyro_z;
uint32_t before, after;
double time_taken;

void static TIM2_OVF_Callback(void);


int main(void)
{
	NVIC_SetPriority(DMA2_Stream2_IRQn,1);
	NVIC_SetPriority(DMA2_Stream3_IRQn,2);
	NVIC_SetPriority(TIM2_IRQn,5);

	/*UART init*/
	uart2_tx_init();

	/*SysTick Timer init*/
	systick_counter_init();

	/*Btn init*/
	BTN_init();

	/*Enable SPI*/
	spi1_dma_init();

	/*Config NCS pin*/
	mpu9250_ncs_pin_config();

	/*Enable Floating Point Unit*/
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

	/*Enable tx stream*/
	dma2_stream3_spi_tx_init();

	/*Enable rx stream*/
	dma2_stream2_spi_rx_init();

	/*Reset NCS pin*/
	mpu9250_ncs_pin_reset();

	/*Config accel*/
	mpu9250_accel_config(ACC_FULL_SCALE_2_G);

	mpu9250_gyro_config(GYRO_FS_SEL_500dps);

	/*Timer2 OVF interrupt alle 1ms*/
	tim2_1khz_interrupt_init();

		while(1)
		{}

}


void TIM2_IRQHandler(void) // jede 1ms Interrupt

{	/*Clear update interrupt flag*/
	TIM2->SR &=~ SR_UIF;

	//before = SysTick->VAL;
	TIM2_OVF_Callback();

	/*Kalibrierung Gyro*/
	//Offset_Calibration_gyro(&gyro_offset, gyro_x, gyro_y, gyro_z, &measurement_cnt);
	/*Kalibrierung Acc*/
	Offset_Calibration_acc(&acc_offset_scale, acc_x, acc_y, acc_z, &measurement_cnt);

	//after = SysTick->VAL;
	//time_taken = (before - after)*0.0000000625;		// f = 16MhZ => t = 62.5ns = 0.0000000625s
}

void static TIM2_OVF_Callback(void)
{
		/*Set NCS pin to low-level*/
		mpu9250_ncs_pin_reset();
		/*Update accel values*/
		mpu9250_accel_gyro_update();
		/*Set NCS pin to high-level*/
		mpu9250_ncs_pin_set();

		/*Get accel data*/
		acc_x =  mpu9250_get_acc_x();
		acc_y =  mpu9250_get_acc_y();
		acc_z =  mpu9250_get_acc_z();

		/*Get accel data*/
		gyro_x =  mpu9250_get_gyro_x();
		gyro_y =  mpu9250_get_gyro_y();
		gyro_z =  mpu9250_get_gyro_z();
}
