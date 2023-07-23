#include <math.h>
#include <stdlib.h>
#include "EKF.h"
#include <GY_511.h>

/**@PINOUT

 *	PB8 :  SCL
 *	PB9 :  SDA
*/


#define GY511_addr		0x1E

#define I2C_DATA_BUFF_LEN    3

#define USER_CTRL_I2C_IF_DIS		(1U<<4)
#define MAX_TRANSFER_LEN			6
#define READ_FLAG					0x80

#define GPIOAEN					(1U<<0)
float Mag_y_raw;

uint8_t magnetometer_buff[MAX_TRANSFER_LEN+1];
uint8_t DRDY;
uint8_t i2c_data_buff[I2C_DATA_BUFF_LEN];


static float Mag_Gauss_LSB_XY; // Varies with gain
static float Mag_Gauss_LSB_Z;   // Varies with gain
lsm303MagData raw;

float magOffset_mT[3];
float yaw_offset_kompensiert;


void GY511_init(uint8_t mode, uint8_t gain, uint8_t rate)
{
	switch(gain)
	{
		case LSM303_MAGGAIN_1_3:
			Mag_Gauss_LSB_XY = 1100.0f;
			Mag_Gauss_LSB_Z = 980.0f;
			break;

		case LSM303_MAGGAIN_1_9:
			Mag_Gauss_LSB_XY = 855.0f;
			Mag_Gauss_LSB_Z = 760.0f;
			break;

		case LSM303_MAGGAIN_2_5:
			Mag_Gauss_LSB_XY = 670.0f;
			Mag_Gauss_LSB_Z = 600.0f;
			break;

		case LSM303_MAGGAIN_4_0:
			Mag_Gauss_LSB_XY = 450.0f;
			Mag_Gauss_LSB_Z = 400.0f;
			break;

		case LSM303_MAGGAIN_4_7:
			Mag_Gauss_LSB_XY = 400.0f;
			Mag_Gauss_LSB_Z = 355.0f;
			break;

		case LSM303_MAGGAIN_5_6:
			Mag_Gauss_LSB_XY = 330.0f;
			Mag_Gauss_LSB_Z = 295.0f;
			break;

		case LSM303_MAGGAIN_8_1:
			Mag_Gauss_LSB_XY = 230.0f;
			Mag_Gauss_LSB_Z = 205.0f;
			break;

		default:
			break;
	}

	/*Magneto Config*/
	i2c_data_buff[0] = CRA_REG_M;
	i2c_data_buff[1] = rate;
	i2c_dma_write(GY511_addr,i2c_data_buff,I2C_DATA_BUFF_LEN);

	i2c_data_buff[0] = CRB_REG_M;
	i2c_data_buff[1] = gain;
	i2c_dma_write(GY511_addr,i2c_data_buff,I2C_DATA_BUFF_LEN);

	i2c_data_buff[0] = MR_REG_M;
	i2c_data_buff[1] = mode;
	i2c_dma_write(GY511_addr,i2c_data_buff,I2C_DATA_BUFF_LEN);
}


void GY_511_update(lsm303MagData *data, int8_t *Offset)
{

	// Data Ready Bit
	i2c_dma_read(GY511_addr,SR_REG_Mg,&DRDY,I2C_DATA_BUFF_LEN);



	if(DRDY & 0x01)
	{
		i2c_dma_read(GY511_addr,GY_511_MAGNETO_OUT_X_H_M,(uint8_t *)magnetometer_buff,MAX_TRANSFER_LEN);
	}

	else
	{
		return;
	}


	data->Raw_Buffer16[0] = ((int16_t)((magnetometer_buff[0] << 8) | magnetometer_buff[1]))- (int16_t)Offset[0]-(int16_t)4;		//x-Wert
	data->Raw_Buffer16[1] = ((int16_t)((magnetometer_buff[2] << 8) | magnetometer_buff[3]))- (int16_t)Offset[2];//-(int16_t)84;		//z-Wert
	data->Raw_Buffer16[2] = ((int16_t)((magnetometer_buff[4] << 8) | magnetometer_buff[5]))- (int16_t)Offset[1]-(int16_t)6;		//y-Wert


	data->x = ((float)data->Raw_Buffer16[0] / Mag_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA);//-0.0297826082f;
	data->z = ((float)data->Raw_Buffer16[1] / Mag_Gauss_LSB_Z * SENSORS_GAUSS_TO_MICROTESLA);
	data->y = ((float)data->Raw_Buffer16[2] / Mag_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA);//-0.00478260964f;
	//Mag_y_raw = ((float)((int16_t)((magnetometer_buff[4] << 8) | magnetometer_buff[5])) / Mag_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA);

	magOffset_mT[0] =Offset_Kalibrierung(&data->x);
//	magOffset_mT[1] =Offset_Kalibrierung(&data->y);
//	magOffset_mT[2] =Offset_Kalibrierung(&data->z);
	float yawAngle = atan2f(data->y, data->x) * 180.0f / M_PI;
//
	// Yaw-Winkel auf den Bereich von 0 bis 360 Grad anpassen
	if (yawAngle < 0)
	{
		yawAngle += 360.0f;
	}

	yaw_offset_kompensiert = yawAngle;
}

float Offset_Kalibrierung(float *data)
{
	float Data_new = 0;
	static float Data_max;
	static float Data_min;
	float Offset;

	Data_new = *data;

	if(Data_new > Data_max){
		Data_max = Data_new;
	}
	if(Data_new < Data_min){
		Data_min = Data_new;
	}

	return Offset = (Data_max + Data_min)/2;
}


float YAW_Init_Mag(lsm303MagData *data, int8_t *Offset)
{
	static float yaw_sum;

	i2c_dma_read(GY511_addr,SR_REG_Mg,&DRDY,I2C_DATA_BUFF_LEN);


		if(DRDY & 0x01)
		{
			i2c_dma_read(GY511_addr,GY_511_MAGNETO_OUT_X_H_M,(uint8_t *)magnetometer_buff,MAX_TRANSFER_LEN);
		}

		else
		{

		}


		data->Raw_Buffer16[0] = ((int16_t)((magnetometer_buff[0] << 8) | magnetometer_buff[1]))- (int16_t)Offset[0]-(int16_t)4;		//x-Wert
		data->Raw_Buffer16[1] = ((int16_t)((magnetometer_buff[2] << 8) | magnetometer_buff[3]))- (int16_t)Offset[2]+(int16_t)0;		//z-Wert
		data->Raw_Buffer16[2] = ((int16_t)((magnetometer_buff[4] << 8) | magnetometer_buff[5]))- (int16_t)Offset[1]-(int16_t)6;		//y-Wert



		data->x = ((float)data->Raw_Buffer16[0] / Mag_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA);
		data->z = ((float)data->Raw_Buffer16[1] / Mag_Gauss_LSB_Z * SENSORS_GAUSS_TO_MICROTESLA);
		data->y = ((float)data->Raw_Buffer16[2] / Mag_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA);



		float yawAngle = (atan2f((float)data->Raw_Buffer16[2], (float)data->Raw_Buffer16[0]));// * 180.0f) / M_PI;

		// Yaw-Winkel auf den Bereich von 0 bis 360 Grad anpassen
		if (yawAngle < 0)
		{
			yawAngle += 2*M_PI;
		}

		yaw_sum += yawAngle;

		return yaw_sum;
}


