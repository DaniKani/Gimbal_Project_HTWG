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
#include "ITM.h"
#include "Global_Variables.h"


void static TIM2_OVF_Callback(mpu_data *data);


int main(void)
{
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
	TIM2_OVF_Callback(&Data);

	/*Kalibrierung Gyro*/
	//Offset_Calibration_gyro(&gyro_offset, gyro_x, gyro_y, gyro_z, &measurement_cnt);
	/*Kalibrierung Acc*/
	Offset_Calibration_acc(&acc_offset_scale, acc_x, acc_y, acc_z, &measurement_cnt);

	//after = SysTick->VAL;
	//time_taken = (before - after)*0.0000000625;		// f = 16MhZ => t = 62.5ns = 0.0000000625s
}

void static TIM2_OVF_Callback(mpu_data *data)
{
		/*Set NCS pin to low-level*/
		mpu9250_ncs_pin_reset();
		/*Update accel values*/
		mpu9250_accel_gyro_update();
		/*Set NCS pin to high-level*/
		mpu9250_ncs_pin_set();

		/*Get accel data*/
		data->acc_x =  (mpu9250_get_acc_x()+0.107058048f)*(9.81f/9.83666897f);
		acc_x = data->acc_x;
		data->acc_y =  mpu9250_get_acc_y()-0.0404653549f;
		acc_y = data->acc_y;
		data->acc_z =  mpu9250_get_acc_z()+0.145186901f;
		acc_z = data->acc_z;

		/*Get accel data*/
		data->gyro_x =  mpu9250_get_gyro_x()-0.13086614f;
		gyro_x = data->gyro_x;
		data->gyro_y =  mpu9250_get_gyro_y()-0.0155219417f;
		gyro_y = data->gyro_y;
		data->gyro_z =  mpu9250_get_gyro_z()-0.00171001512f;
		gyro_z = data->gyro_z;
}
