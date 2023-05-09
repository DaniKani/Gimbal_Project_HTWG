#include "Gyr_Acc_Calibration.h"
#include "spi_dma.h"
#include "mpu9250.h"

//Defines
#define Buff_Size 1000
#define GPIOCEN	(1U<<2)
#define BTN_PIN	(1U<<13)




/***********Variables*************/
//global


//lokal
uint8_t mode = 0;
float sum_x,sum_y,sum_z;
float sum_x1,sum_x2,sum_y1,sum_y2, sum_z1,sum_z2;



void Offset_Calibration_gyro(Offset_value_gyro* data, float gyro_x, float gyro_y, float gyro_z, uint16_t* Measurement_cnt)
{

	switch (mode){

	case 0:

		if(!(GPIOC->IDR & BTN_PIN))
			{
				mode = 1;
			}

	break;

	case 1:
			sum_x += gyro_x;
			sum_y += gyro_y;
			sum_z += gyro_z;

			(*Measurement_cnt)++;

		if(*Measurement_cnt == Buff_Size)
			{
				mode = 2;
			}

	break;

	case 2:

		 data->x_offset_gyro = sum_x/Buff_Size;
		 data->y_offset_gyro = sum_y/Buff_Size;
		 data->z_offset_gyro = sum_z/Buff_Size;

		 *Measurement_cnt = 0;
		 sum_x = 0;
		 sum_y = 0;
		 sum_z = 0;
		 mode = 0;

	break;

	default: mode = 0;
	}
}

void Offset_Calibration_acc(Offset_value_acc* data, float acc_x, float acc_y, float acc_z, uint16_t* Measurement_cnt)
{
	switch(mode){

	case 0:

		if(!(GPIOC->IDR & BTN_PIN))
					{
						mode = 1;
					}
	break;

	case 1:	//Berechnung Durchschnitt X1

		sum_x1 += acc_x;

		(*Measurement_cnt)++;

		if(*Measurement_cnt == Buff_Size)
		{
			*Measurement_cnt = 0;
			mode = 2;
		}

	break;

	case 2:

		if(!(GPIOC->IDR & BTN_PIN))
					{
						mode = 3;
					}

	break;

	case 3: //Berechnung Durchschnitt X2 und Offset X und Scale X

		sum_x2 += acc_x;

		(*Measurement_cnt)++;

		if(*Measurement_cnt == Buff_Size)
		{
			data->x_offset_acc = ((sum_x1/Buff_Size)+(sum_x2/Buff_Size))/2;
			data->x_scale_acc = ((sum_x1/Buff_Size)-(sum_x2/Buff_Size))/2;
			*Measurement_cnt = 0;
			mode = 4;
		}

	break;

	case 4:

		if(!(GPIOC->IDR & BTN_PIN))
					{
						mode = 5;
					}
	break;

	case 5:	//Berechnung Durchschnitt Y1

		sum_y1 += acc_y;

		(*Measurement_cnt)++;

		if(*Measurement_cnt == Buff_Size)
		{
			*Measurement_cnt = 0;
			mode = 6;
		}

	break;

	case 6:

		if(!(GPIOC->IDR & BTN_PIN))
					{
						mode = 7;
					}

	break;

	case 7: //Berechnung Durchschnitt Y2 und Offset Y

		sum_y2 += acc_y;

		(*Measurement_cnt)++;

		if(*Measurement_cnt == Buff_Size)
		{
			data->y_offset_acc = ((sum_y1/Buff_Size)+(sum_y2/Buff_Size))/2;
			data->y_scale_acc = ((sum_y1/Buff_Size)-(sum_y2/Buff_Size))/2;
			*Measurement_cnt = 0;
			mode = 8;
		}

	break;

	case 8:

		if(!(GPIOC->IDR & BTN_PIN))
					{
						mode = 9;
					}
	break;

	case 9:	//Berechnung Durchschnitt Z1

		sum_z1 += acc_z;

		(*Measurement_cnt)++;

		if(*Measurement_cnt == Buff_Size)
		{
			*Measurement_cnt = 0;
			mode = 10;
		}

	break;

	case 10:

		if(!(GPIOC->IDR & BTN_PIN))
					{
						mode = 11;
					}

	break;

	case 11: //Berechnung Durchschnitt Z2 und Offset Z

		sum_z2 += acc_z;

		(*Measurement_cnt)++;

		if(*Measurement_cnt == Buff_Size)
		{
			data->z_offset_acc = ((sum_z1/Buff_Size)+(sum_z2/Buff_Size))/2;
			data->z_scale_acc = ((sum_z1/Buff_Size)-(sum_z2/Buff_Size))/2;
			*Measurement_cnt = 0;
			mode = 0;
		}

	break;

	}
}

void BTN_init(void)
{
	/*Set Peripheral bus AHB1*/
	RCC->AHB1ENR |= GPIOCEN;


	/*Set Pin13 as Input*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);
}







