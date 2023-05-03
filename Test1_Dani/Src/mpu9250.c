#include "mpu9250.h"


/**@PINOUT

 *	PA5 :  SPI1_SCK
 *	PA6 :  SPI1_MISO
 *	PA7 :  SPI1_MOSI

  MPU--------------> STM32
	VCC        -       3.3V
	GND        -       GND
	NCS				 - PA0		(A0)
	SCL				 - SCK/PA5	(D13)
	SDI/SDA    -       MOSI/PA7	(D11)
	SDO/ADO    -       MISO/PA6	(D12)
*/


#define SPI_DATA_BUFF_LEN			2

#define USER_CTRL_I2C_IF_DIS		(1U<<4)
#define MAX_TRANSFER_LEN			14
#define READ_FLAG					0x80

#define GPIOAEN						(1U<<0)

uint8_t dummy_buff[MAX_TRANSFER_LEN + 1];
uint8_t accel_gyro_buff[MAX_TRANSFER_LEN + 1];
uint8_t Array_len_accel;
uint8_t Array_len_dummy;
uint8_t Who_am_i_reg[3];
uint8_t Who_am_i_value[3];

uint8_t MPU9250_read_addr[MAX_TRANSFER_LEN + 1];
uint8_t MPU9250_value_addr[MAX_TRANSFER_LEN + 1];

uint8_t spi_data_buff[SPI_DATA_BUFF_LEN];
uint8_t g_tx_cmplt=0;
uint8_t g_rx_cmplt=0;

uint16_t data_tx = 0; 	//Counter of successfully data transfers
uint16_t data_rx = 0; 	//Counter of successfully data transfers

uint8_t error_tx =0;	//Counter of transmit errors
uint8_t error_rx =0;	//Counter of transmit errors

double g_accel_range;
double g_gyro_range;



void mpu9250_ncs_pin_config(void)
{
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA0 as output pin*/
	GPIOA->MODER |= (1U<<0);
	GPIOA->MODER &= ~(1U<<1);
}

void mpu9250_ncs_pin_set(void)
{
	GPIOA->ODR |=(1U<<0);
}

void mpu9250_ncs_pin_reset(void)
{
	GPIOA->ODR &= ~(1U<<0);
}

void mpu9250_WHO_AM_I(void)
{
	Who_am_i_reg[0] =   (0x75) | READ_FLAG;

	dma2_stream3_spi_transfer((uint32_t) Who_am_i_reg, (uint32_t)(3));

	dma2_stream2_spi_receive((uint32_t) Who_am_i_value,(uint32_t)(3));

	/*Wait for reception completion*/
	while(!g_rx_cmplt){}

	/*Reset flag*/
	g_rx_cmplt = 0;

}

void mpu9250_read_addr(uint32_t addr)
{	/*This function is used to read the value of the defined register addr*/

	MPU9250_read_addr[0] =   addr | READ_FLAG;

	dma2_stream3_spi_transfer((uint32_t) MPU9250_read_addr, (uint32_t)(MAX_TRANSFER_LEN + 1));

	dma2_stream2_spi_receive((uint32_t) MPU9250_value_addr,(uint32_t)(MAX_TRANSFER_LEN + 1));

	/*Wait for reception completion*/
	while(!g_rx_cmplt){}

	/*Reset flag*/
	g_rx_cmplt = 0;

}


/******************ACCEL**********************/
void mpu9250_accel_config(uint8_t mode)
{

	switch(mode)
	{
		case ACC_FULL_SCALE_2_G:
			g_accel_range = 2.0;
			break;

		case ACC_FULL_SCALE_4_G:
			g_accel_range = 4.0;
			break;

		case ACC_FULL_SCALE_8_G:
			g_accel_range = 8.0;
			break;

		case ACC_FULL_SCALE_16_G:
			g_accel_range = 16.0;
			break;
		default:
			break;
	}
	/************************************/
		//Ab hier eingefügter CODE

		/*H_RESET: Reset the PWR_MGMT_1 Register */
		spi_data_buff[0] = 0x6B;
		spi_data_buff[1] = (1U<<7);

		dma2_stream3_spi_transfer((uint32_t) spi_data_buff, (uint32_t) SPI_DATA_BUFF_LEN);

		/*Wait for transfer completion*/
		while(!g_tx_cmplt){}

		/*Reset flag*/
		g_tx_cmplt = 0;

		/*Disable Sleep Mode */
		spi_data_buff[0] = 0x6B;
		spi_data_buff[1] &= ~(1U<<6);

		dma2_stream3_spi_transfer((uint32_t) spi_data_buff, (uint32_t) SPI_DATA_BUFF_LEN);

		/*Wait for transfer completion*/
		while(!g_tx_cmplt){}

		/*Reset flag*/
		g_tx_cmplt = 0;
	/************************************/

	/*Set to SPI mode only*/
	spi_data_buff[0] = MPU9250_ADDR_USER_CTRL;
	spi_data_buff[1] = USER_CTRL_I2C_IF_DIS;

	dma2_stream3_spi_transfer((uint32_t) spi_data_buff, (uint32_t) SPI_DATA_BUFF_LEN);

	/*Wait for transfer completion*/
	while(!g_tx_cmplt){}

	/*Reset flag*/
	g_tx_cmplt = 0;


	/*Configure the ACCEL Range*/
	spi_data_buff[0] = MPU9250_ADDR_ACCELCONFIG;
	spi_data_buff[1] = mode;

	dma2_stream3_spi_transfer((uint32_t) spi_data_buff, (uint32_t) SPI_DATA_BUFF_LEN);

	/*Wait for transfer completion*/
	while(!g_tx_cmplt){}

	/*Reset flag*/
	g_tx_cmplt = 0;
}

void mpu9250_accel_gyro_update(void)
{
	dummy_buff[0] =  MPU9250_ACCEL_XOUT_H |READ_FLAG;

	dma2_stream3_spi_transfer((uint32_t) dummy_buff, (uint32_t)(MAX_TRANSFER_LEN + 1));

	dma2_stream2_spi_receive((uint32_t)accel_gyro_buff,(uint32_t)(MAX_TRANSFER_LEN + 1));

	Array_len_accel = sizeof(accel_gyro_buff)/sizeof(uint8_t);
	Array_len_dummy =  sizeof(dummy_buff)/sizeof(uint8_t);

	/*Wait for reception completion*/
	while(!g_rx_cmplt){}

	/*Reset flag*/
	g_rx_cmplt = 0;
}

float mpu9250_accel_gyro_get(uint8_t high_idx, uint8_t low_idx)
{
	int16_t rslt;

	rslt  =  accel_gyro_buff[high_idx] << 8 | accel_gyro_buff[low_idx];

	//for accelerometer
	if( (rslt!=0.0) && (high_idx <=5) )
	{
		return ((float)- rslt) * g_accel_range / (float)0x8000;
	}
	//for temperatur
	else if( (rslt!=0.0) && (high_idx <=7) )
	{
		return rslt;
	}
	//for gyroskop
	else if( (rslt!=0.0) && (high_idx <=15) )
	{
		return ((float)- rslt) * g_gyro_range / (float)0x8000;
	}
	//rest
	else
	{
		return 0.0;
	}
}

float mpu9250_get_acc_x(void)
{
	return mpu9250_accel_gyro_get(1,2);
}

float mpu9250_get_acc_y(void)
{
	return mpu9250_accel_gyro_get(3,4);
}

float mpu9250_get_acc_z(void)
{
	return mpu9250_accel_gyro_get(5,6);
}
/********************************************/

float mpu9250_get_temp(void)
{
	return mpu9250_accel_gyro_get(7,8);
}

/******************GYRO**********************/
void mpu9250_gyro_config(uint8_t mode)
{

	switch(mode)
	{
		case GYRO_FULL_SCALE_250:
			g_gyro_range = 250;
			break;

		case GYRO_FULL_SCALE_500:
			g_gyro_range = 500;
			break;

		case GYRO_FULL_SCALE_1000:
			g_gyro_range = 1000;
			break;

		case GYRO_FULL_SCALE_2000:
			g_gyro_range = 2000;
			break;
		default:
			break;
	}
	/*Configure the GYRO Range*/
	spi_data_buff[0] = MPU9250_ADDR_GYROCONFIG;
	spi_data_buff[1] = mode;

	dma2_stream3_spi_transfer((uint32_t) spi_data_buff, (uint32_t) SPI_DATA_BUFF_LEN);

	/*Wait for transfer completion*/
	while(!g_tx_cmplt){}

	/*Reset flag*/
	g_tx_cmplt = 0;

}

void mpu9250_gyro_update(void)
{
	dummy_buff[0] = MPU9250_GYRO_XOUT_H |READ_FLAG;

	dma2_stream3_spi_transfer((uint32_t) dummy_buff, (uint32_t)(MAX_TRANSFER_LEN + 1));

	dma2_stream2_spi_receive((uint32_t)accel_gyro_buff,(uint32_t)(MAX_TRANSFER_LEN + 1));

	/*Wait for reception completion*/
	while(!g_rx_cmplt){}

	/*Reset flag*/
	g_rx_cmplt = 0;

	Array_len_accel = sizeof(accel_gyro_buff)/sizeof(uint8_t);
	Array_len_dummy =  sizeof(dummy_buff)/sizeof(uint8_t);

}

float mpu9250_get_gyro_x(void)
{
	return mpu9250_accel_gyro_get(9,10);
}

float mpu9250_get_gyro_y(void)
{
	return mpu9250_accel_gyro_get(11,12);
}

float mpu9250_get_gyro_z(void)
{
	return mpu9250_accel_gyro_get(13,14);
}

/********************************************/

/*****************ISR************************/
void DMA2_Stream3_IRQHandler(void)
{
	if((DMA2->LISR) & LISR_TCIF3)
	{
		//do something...
		g_tx_cmplt = 1;
		//DMA2_Stream3->CR &= ~DMA_SxCR_EN;
		//Clear the flag
		DMA2->LIFCR |=LIFCR_CTCIF3;
		data_tx++;

	}
	else if((DMA2->LISR) & LISR_TEIF3)
	{
        //do something...
		error_tx++;
		//Clear the flag
		DMA2->LIFCR |=LIFCR_CTEIF3;
	}
}

void DMA2_Stream2_IRQHandler(void)
{
	if((DMA2->LISR) & LISR_TCIF2)
	{
		//do something...
		g_rx_cmplt = 1;
		//DMA2_Stream2->CR&=~DMA_SxCR_EN;
		//Clear the flag
		DMA2->LIFCR |=LIFCR_CTCIF2;
		data_rx++;
	}
	else if((DMA2->LISR) & LISR_TEIF2)
	{
        //do something...
		error_rx++;
		//Clear the flag
		DMA2->LIFCR |=LIFCR_CTEIF2;
	}
}
/********************************************/
