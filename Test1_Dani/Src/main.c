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

float temp;
float acc_x,acc_y,acc_z;
float gyro_x , gyro_y, gyro_z;

uint16_t i;
uint8_t tim = 0;

uint32_t a = 0;
uint32_t b = 0;

uint32_t before, after;
double time_taken;

/*For Calibration*/
Offset_Scale_value_acc Offset_Scale_acc;
values_acc	Values_acc;
Offset_value_gyro Offset_gyro;

uint16_t counter_pb =0;

//int16_t	int_gyro_x;
//int16_t	int_gyro_y;
//int16_t	int_gyro_z;

void uart_send_int16(int16_t value);
void static TIM2_OVF_Callback(void);

int main(void)
{
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

	/*WHO_AM_I*****START SPI**********************/
	/*Reset NCS pin*/
	mpu9250_ncs_pin_reset();

	/*Read WHO_AM_I*/
	mpu9250_WHO_AM_I();

	/*Set NCS pin to high-level*/
	mpu9250_ncs_pin_set();
	/**************END SPI**********************/

	/*Enable Timer 1kHz*/
	tim2_1khz_interrupt_init();


	/*Change Interrupt priority*/
	NVIC_SetPriority(DMA2_Stream2_IRQn,11);
	NVIC_SetPriority(DMA2_Stream3_IRQn,10);
	NVIC_SetPriority(TIM2_IRQn,13);


	while(1)
	{

		if(!(GPIOC->IDR & BTN_PIN))
		{
			counter_pb++;
		}

	/*print gyro_data*/
	uart_send_int16((int16_t)gyro_x);

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

	before = SysTick->VAL;
	TIM2_OVF_Callback();

	/*Calibration*/
	Offset_Calibration_gyro(&Offset_gyro, gyro_x, gyro_y, gyro_z, 1000);
	//Offset_Calibration_acc(&Values_acc, &Offset_Scale_acc, acc_x, acc_y, acc_z, 1000);
	after = SysTick->VAL;
	time_taken = (before - after)*0.0000000625;		// f = 16MhZ => t = 62.5ns = 0.0000000625s
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

