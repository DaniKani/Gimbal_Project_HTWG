#include "stm32f4xx.h"
#include <stdio.h>
#include "dma.h"
#include "adc_dma.h"
#include "mpu9250.h"
#include <string.h>



float temp;
float acc_x,acc_y,acc_z;
float gyro_x , gyro_y, gyro_z;
uint16_t i;


int main(void)
{
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

	/*ACCELEROMETER**********START SPI******************/
	/*Reset NCS pin*/
	mpu9250_ncs_pin_reset();

	/*Config accel*/
	mpu9250_accel_config(ACC_FULL_SCALE_2_G);
	/*Set NCS pin to high-level*/
	mpu9250_ncs_pin_set();
	/**************END SPI**********************/

	for(i = 0; i < 10000; i++){}
			i=0;

	/*GYROSKOP***********START SPI**********************/
	/*Reset NCS pin*/
	mpu9250_ncs_pin_reset();

	/*Config accel*/
	mpu9250_gyro_config(GYRO_FULL_SCALE_250);

	/*Set NCS pin to high-level*/
	mpu9250_ncs_pin_set();
	/**************END SPI**********************/

	/*WHO_AM_I*****START SPI**********************/
	/*Reset NCS pin*/
	mpu9250_ncs_pin_reset();

	/*Read WHO_AM_I*/
	mpu9250_WHO_AM_I();

	/*Set NCS pin to high-level*/
	mpu9250_ncs_pin_set();
	/**************END SPI**********************/

	while(1)
	{
		/*Set NCS pin to low-level*/
		mpu9250_ncs_pin_reset();

        /*Update accel values*/
		mpu9250_accel_update();

		/*Set NCS pin to high-level*/
		mpu9250_ncs_pin_set();

		/*Get accel data*/
		acc_x =  mpu9250_get_acc_x();
		acc_y =  mpu9250_get_acc_y();
		acc_z =  mpu9250_get_acc_z();

		/*Get Temp*/
		temp = mpu9250_get_temp()/333.87 + 21; //RegisterMap (P.12); 333.87 LSB/°C; Offset Room Temp. 21°C

		/*Get gyro data*/
		gyro_x =  mpu9250_get_gyro_x();
		gyro_y =  mpu9250_get_gyro_y();
		gyro_z =  mpu9250_get_gyro_z();

		/*Sendeverzögerung, bringt nichts*/
		for(i = 0; i < 10000; i++){}
		i=0;
	}

}




