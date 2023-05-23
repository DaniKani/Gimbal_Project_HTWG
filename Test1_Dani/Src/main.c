#include "stm32f4xx.h"
#include <stdio.h>
#include "dma.h"
#include "adc_dma.h"
#include "mpu9250.h"
#include <string.h>
#include "uart_dma.h"
#include "tim_sample_mpu.h"
#include "systick.h"
#include "Gyr_Acc_Calibration.h"
#include "stdint.h"
#include "Global_Variables.h"
#include "EKF.h"

#define KALMAN_P_INIT 0.1f
#define KALMAN_Q 0.001f
#define KALMAN_R 0.001f		//3e-06f (vorschlag Chatgpt)	//0.011f


float temp;
float acc_x,acc_y,acc_z;
float gyro_x , gyro_y, gyro_z;

uint16_t i;
uint8_t tim = 0;

uint32_t a = 0;
uint32_t b = 0;

uint32_t before, after;
double time_taken;

uint8_t ii;
float roll_angle_up;
float pitch_angle_up;
float roll_angle_pr;	//phi
float pitch_angle_pr;	//theta

/*For Calibration*/
Offset_Scale_value_acc Offset_Scale_acc;
values_acc	Values_acc;
Offset_value_gyro Offset_gyro;

Offset_Scale_value_acc measurements_acc_mpu9250 ={
		.x_offset_acc	= 0.0132f,
		.x_scale_acc	= 1.0025f,
		.y_offset_acc	= 0.0072f,
		.y_scale_acc	= 1.0015f,
		.z_offset_acc	= 0.0251f,
		.z_scale_acc	= 1.0164f,
};

Offset_value_gyro measurements_gyro_mpu9250;

uint16_t cnt_gyro_cali = 0;
uint16_t counter_pb =0;
float delta_t_gyro;
void uart_send_int16(int16_t value);
void static get_camera_position(Offset_Scale_value_acc* acc_offset_scale, Offset_value_gyro* gyro_offset);
void static set_gyro_offset(uint16_t counter, uint16_t cyle_times);

EKF Start_Conditions;

int main(void)
{
	/*create start conditions for the Kalman-Filter*/
	float P[2]={KALMAN_P_INIT, KALMAN_P_INIT};			//Kovarianzmatrix
	float Q[2]={KALMAN_Q, KALMAN_Q}; 					//Kovarianzmatrix Prozessrauschen
	float R[3]={KALMAN_R,KALMAN_R,KALMAN_R};			//Kovarianzmatrix Messrauschen
	EKF_Init(&Start_Conditions, P, Q, R);

	/*local_Variables*/
	//Offset_value_gyro  measurements_gyro_mpu9250 = {-0.17926,0.06552,0.01092};
	//Offset_value_gyro  measurements_gyro_mpu9250 = {0,0,0};	//calibration gets executed at the beginning
	//Offset_Scale_value_acc measurements_acc_mpu9250 = {0.03552, 9.81508/9.81f,0.01730,9.82851/9.81f,0.08203,9.97796/9.81f};

	/*For Gyro calibration*/



	/*Enable User Button*/
	BTN_init();

	/*Enable UART*/
	uart2_rx_tx_init();

	/*SysTick Timer init*/
	systick_counter_init();

	/*Enable SPI*/
	spi1_dma_init();

	/*Enable Floating Point Unit*/
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

	/*Config NCS pin*/
	mpu9250_ncs_pin_config();

	/*Enable tx stream*/
	dma2_stream3_spi_tx_init();

	/*Enable rx stream*/
	dma2_stream2_spi_rx_init();

	/*ACCELEROMETER+Gyroskope****START SPI********/
	/*Reset NCS pin*/
	mpu9250_ncs_pin_reset();

	/*Config accel & gyro*/
	mpu9250_accel_config(ACC_FULL_SCALE_2_G);
	mpu9250_gyro_config(GYRO_FULL_SCALE_250);

	/*Set NCS pin to high-level*/
	mpu9250_ncs_pin_set();
	/**************END SPI************************/

//	/*WHO_AM_I*****START SPI**********************/
//	/*Reset NCS pin*/
//	mpu9250_ncs_pin_reset();
//
//	/*Read WHO_AM_I*/
//	mpu9250_WHO_AM_I();
//
//	/*Set NCS pin to high-level*/
//	mpu9250_ncs_pin_set();
//	/**************END SPI**********************/

	/*Enable Timer 1kHz*/
	delta_t_gyro = tim2_1khz_interrupt_init();
	// delta_t_gyro = tim2_500hz_interrupt_init();
//	delta_t_gyro = tim2_100hz_interrupt_init();


	/*Change Interrupt priority*/
	NVIC_SetPriority(DMA2_Stream2_IRQn,11);
	NVIC_SetPriority(DMA2_Stream3_IRQn,10);
	NVIC_SetPriority(TIM2_IRQn,13);



	while(1)
	{

	/*print gyro_data*/
	//uart_send_int16((int16_t)gyro_x);

	}


}



/*FUNCTIONS***********************************/
void uart_send_int16(int16_t value) {

    // Teile den int16_t-Wert in zwei 8-Bit-Werte auf
    uint8_t high_byte = (uint8_t)((value >> 8) & 0xFF);
    uint8_t low_byte = (uint8_t)(value & 0xFF);

    // Sende die Bytes über UART
    printf( "%c", high_byte);
    printf( "%c", low_byte);
}

/*INTERRUPTS**********************************/
void TIM2_IRQHandler(void) // jede 1ms Interrupt

{	/*Clear update interrupt flag*/
	TIM2->SR &=~ SR_UIF;

	tim=0;
	b++;

	uint16_t calibration_cycles = 1000;
	if(cnt_gyro_cali <= calibration_cycles)
	{
		set_gyro_offset(cnt_gyro_cali, calibration_cycles);
		cnt_gyro_cali++;
	}
	else
	{
		get_camera_position(&measurements_acc_mpu9250, &measurements_gyro_mpu9250);
	}

	//Calibration
	//Offset_Calibration_acc(&Values_acc, &Offset_Scale_acc, acc_x, acc_y, acc_z, 1000);

}

void static get_camera_position(Offset_Scale_value_acc* acc_offset_scale, Offset_value_gyro* gyro_offset)
{
		/*Set NCS pin to low-level*/
		mpu9250_ncs_pin_reset();
		/*Update accel values*/
		mpu9250_accel_gyro_update();
		/*Set NCS pin to high-level*/
		mpu9250_ncs_pin_set();

		/*Get accel data*/
		acc_x =  mpu9250_get_acc_x()*acc_offset_scale->x_scale_acc - acc_offset_scale->x_offset_acc;
		acc_y =  mpu9250_get_acc_y()*acc_offset_scale->y_scale_acc - acc_offset_scale->y_offset_acc;
		acc_z =  mpu9250_get_acc_z()*acc_offset_scale->z_scale_acc - acc_offset_scale->z_offset_acc;

		/*Get accel data*/
		gyro_x =  mpu9250_get_gyro_x()-gyro_offset->x_offset_gyro;
		gyro_y =  mpu9250_get_gyro_y()-gyro_offset->y_offset_gyro;
		gyro_z =  mpu9250_get_gyro_z()-gyro_offset->z_offset_gyro;

//		before = SysTick->VAL;
		EKF_Predict(&Start_Conditions, gyro_x, gyro_y, gyro_z, delta_t_gyro);
		roll_angle_pr	= Start_Conditions.roll_r 	*180/M_PI;
		pitch_angle_pr	= Start_Conditions.pitch_r 	*180/M_PI;
//		after = SysTick->VAL;
//		time_taken = (before - after)*0.0000000625;

		if (ii==50)
		{
			before = SysTick->VAL;
			EKF_Update(&Start_Conditions, acc_x, acc_y, acc_z);
			after = SysTick->VAL;
			roll_angle_up	= Start_Conditions.roll_r 	*180/M_PI;
			pitch_angle_up	= Start_Conditions.pitch_r 	*180/M_PI;
			time_taken = (before - after)*0.0000000625; // f = 16MhZ => t = 62.5ns = 0.0000000625s
			ii=0;
		}
		ii++;



}

void static set_gyro_offset(uint16_t counter, uint16_t cycle_times)
{
		/*Set NCS pin to low-level*/
		mpu9250_ncs_pin_reset();
		/*Update accel values*/
		mpu9250_accel_gyro_update();
		/*Set NCS pin to high-level*/
		mpu9250_ncs_pin_set();
		counter_pb++;
		/*Get accel data*/
		gyro_x =  mpu9250_get_gyro_x();
		gyro_y =  mpu9250_get_gyro_y();
		gyro_z =  mpu9250_get_gyro_z();
		Offset_Calibration_gyro(&measurements_gyro_mpu9250, gyro_x, gyro_y, gyro_z, counter, cycle_times);
}

