#include <GY_511.h>
#include "stm32f4xx.h"
#include <stdio.h>
#include "dma.h"
#include "adc_dma.h"
#include <string.h>
#include <math.h>
#include "uart.h"

//globale Variablen
lsm303MagData MagnetometerData;
char test[] = "test";
char hello =5;

int main(void)
{
	uart2_tx_init();

	/*Enable I2C*/
	i2c1_init();

	/*Enable Floating Point Unit*/
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

	/*Enable tx stream*/
	dma1_stream6_i2c1_tx_init();

	/*Enable rx stream*/
	dma1_stream5_i2c1_rx_init();

	/*Config accel*/
	GY511_init(LSM303_CONTIMODE, LSM303_MAGGAIN_8_1, LSM303_MAGRATE_220);

	while(1)
	{
		hello++;
		GY_511_update(&MagnetometerData);
		sendString(test);
		uart2_write(MagnetometerData.Raw_Buffer[0]);
		uart2_write(MagnetometerData.Raw_Buffer[1]);
		uart2_write(MagnetometerData.Raw_Buffer[2]);
		uart2_write(MagnetometerData.Raw_Buffer[3]);
		uart2_write(MagnetometerData.Raw_Buffer[4]);
		uart2_write(MagnetometerData.Raw_Buffer[5]);
	}
}




