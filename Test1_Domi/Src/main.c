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
#include "EKF.h"
#include <Math.h>

float phi_grad;

#define KALMAN_Q 0.001f
#define KALMAN_R 0.011f

float R[3] = {0.011f, 0.011f, 0.011f};
float Q[2] = {0.001f, 0.001f};
float P[2] = {0.1f, 0.1f};

float phiHat_deg;
float thetaHat_deg;

void static TIM2_OVF_Callback(mpu_data *data);

uint8_t i=0;

/*Instanziieren eines EKF Structs*/
EKF ekf;
EKF* ekf_ptr = &ekf;

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

	/*Initialisieren des EKF*/
	EKF_Init(&ekf,P,Q,R);

	/*Timer2 OVF interrupt alle 1ms*/
	tim2_1khz_interrupt_init();

		while(1)
		{
			//time_taken = (before - after)*0.0000000625;		// f = 16MhZ => t = 62.5ns = 0.0000000625s
		}


}


void TIM2_IRQHandler(void) // jede 1ms Interrupt

{	/*Clear update interrupt flag*/
	TIM2->SR &=~ SR_UIF;

	TIM2_OVF_Callback(&Data);
	EKF_Predict(&ekf,gyro_x,gyro_y,gyro_z, 0.001);

	//after = SysTick->VAL;

	if(i == 10){
	EKF_Update(&ekf, acc_x, acc_y, acc_z);
	i= 0;
	}
	i++;

	phi_grad = ekf.phi_r * 180.0f / M_PI *5;




	//phiHat_deg = atanf(acc_y/acc_z);
	//thetaHat_deg = asinf(acc_x/9.81f);

	/*Kalibrierung Gyro*/
	//Offset_Calibration_gyro(&gyro_offset, gyro_x, gyro_y, gyro_z, &measurement_cnt);
	/*Kalibrierung Acc*/
	//Offset_Calibration_acc(&acc_offset_scale, acc_x, acc_y, acc_z, &measurement_cnt);


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
		data->acc_x =  (mpu9250_get_acc_x()+0.0966596603f)*(9.81f/9.84315014f);
		acc_x = data->acc_x;
		data->acc_y =  (mpu9250_get_acc_y()-0.0352840424f)*(9.81f/9.8381424f);
		acc_y = data->acc_y;
		data->acc_z =  (mpu9250_get_acc_z()+0.104623795f)*(9.81f/9.92811012f);
		acc_z = data->acc_z;

		/*Get gyro data*/
		data->gyro_x =  mpu9250_get_gyro_x()-0.13086614f;
		gyro_x = data->gyro_x;
		data->gyro_y =  mpu9250_get_gyro_y()-0.0155219417f;
		gyro_y = data->gyro_y;
		data->gyro_z =  mpu9250_get_gyro_z()-0.00171001512f;
		gyro_z = data->gyro_z;
}
