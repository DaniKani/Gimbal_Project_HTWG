#include "Gyr_Acc_Calibration.h"



float sum_x,sum_y,sum_z, offset;


#define GPIOCEN	(1U<<2)
#define BTN_PIN	(1U<<13)

typedef struct
{
	double x_offset_gyro;
	double y_offset_gyro;
	double z_offset_gyro;
}Offset_value_gyro;

typedef struct
{
	double x_offset_acc, x_scale_acc;
	double y_offset_acc, y_scale_acc;
	double z_offset_acc, z_scale_acc;
}Offset_value_acc;

void Offset_Calibration_gyro(Offset_value_gyro* data, float gyro_x, float gyro_y, float gyro_z, uint16_t Measurement_cnt)
{
	switch (mode){

	case 0:

		if(GPIOC->IDR & BTN_PIN)
			{
				mode = 1;
			}

	break;

	case 1:
			sum_x += gyro_x;
			sum_y += gyro_y;
			sum_z += gyro_z;

			Measurement_cnt++;

		if(Measurement_cnt == 1000)
			{
				mode = 2;
			}

	break;

	case 2:

		 data->x_offset_gyro = sum_x/Measurement_cnt;
		 data->y_offset_gyro = sum_y/Measurement_cnt;
		 data->z_offset_gyro = sum_z/Measurement_cnt;

	break;

	default: 0;
	}
}

void Offset_Calibration_acc()
{

}


void BTN_init(void)
{
	/*Set Peripheral bus AHB1*/
	RCC->AHB1ENR |= GPIOCEN;

	/*Set Pin13 as Input*/
	GPIOA->MODER &=~(1U<<26);
	GPIOA->MODER &=~(1U<<27);
}


/*into main*/
Offset_value_gyro gyro_offset;




