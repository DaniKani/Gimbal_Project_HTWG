#include "Gyr_Acc_Calibration.h"
#include <stdlib.h>
#include "uart_dma.h"
#include <math.h>
#include "Global_Variables.h"


float sum_x,sum_y,sum_z, offset;
uint8_t start =0, axis=0;
static uint16_t cnt_acc_measure_points;
uint8_t mode;



void Offset_Calibration_gyro(Offset_value_gyro* data, float gyro_x, float gyro_y, float gyro_z, uint16_t cnt_gyro_measure_points, uint16_t Measurement_cnt)
{
	switch (mode){

	case 0:
			mode=1;

//		if(!(GPIOC->IDR & BTN_PIN))	//Is Button pressed?
//			{
//				mode = 1;
//			}

	break;

	case 1:
			sum_x += gyro_x;
			sum_y += gyro_y;
			sum_z += gyro_z;

			cnt_gyro_measure_points++;

		if(cnt_gyro_measure_points == Measurement_cnt)
			{
				mode = 2;
			}

	break;

	case 2:

		 data->x_offset_gyro = sum_x/Measurement_cnt;
		 data->y_offset_gyro = sum_y/Measurement_cnt;
		 data->z_offset_gyro = sum_z/Measurement_cnt;
		 cnt_gyro_measure_points=0;
		 mode = 0;
		 sum_x=0;
		 sum_y=0;
		 sum_z=0;


	break;

	default:;


	}
}

void Offset_Calibration_acc(values_acc* data, Offset_Scale_value_acc* solution, float acc_x, float acc_y, float acc_z, uint16_t number_measure_points)
{
	switch(start)
	{
		case 0:
			if(!(GPIOC->IDR & BTN_PIN))
			{
				start = 1;
				cnt_acc_measure_points=0;

			}
			break;

		case 1:
			cnt_acc_measure_points++;

					switch(axis)
					{
							case 0:
								data->x1_data += acc_x ;

								if(cnt_acc_measure_points == number_measure_points)
								{
									axis = 1;
									start = 0;
									//printf("sd");
								}
								break;

							case 1:
								data->x2_data += acc_x ;

								if(cnt_acc_measure_points == number_measure_points)
								{
									axis = 2;
									start = 0;
								}
								break;

							case 2:
								data->y1_data += acc_y ;

								if(cnt_acc_measure_points == number_measure_points)
								{
									axis = 3;
									start = 0;
								}
								break;

							case 3:
								data->y2_data += acc_y ;

								if(cnt_acc_measure_points == number_measure_points)
								{
									axis = 4;
									start = 0;
								}
								break;

							case 4:
								data->z1_data += acc_z ;;

								if(cnt_acc_measure_points == number_measure_points)
								{
									axis = 5;
									start = 0;
								}
								break;

							case 5:
								data->z2_data += acc_z ;

								if(cnt_acc_measure_points == number_measure_points)
								{
									axis = 0;
									start = 2;
								}
								break;

							default:

								break;
					}

			break;

		case 2:
			solution->x_offset_acc = (data->x1_data + data->x2_data)/(2*number_measure_points);
			solution->y_offset_acc = (data->y1_data + data->y2_data)/(2*number_measure_points);
			solution->z_offset_acc = (data->z1_data + data->z2_data)/(2*number_measure_points);

			solution->x_scale_acc = (fabs(data->x1_data) + fabs(data->x2_data))/(2*number_measure_points);
			solution->y_scale_acc = (fabs(data->y1_data) + fabs(data->y2_data))/(2*number_measure_points);
			solution->z_scale_acc = (fabs(data->z1_data) + fabs(data->z2_data))/(2*number_measure_points);

			start =0;
			break;

		default:

			//do something
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

//	/*Set to open drain mode*/
//	GPIOC->OTYPER |= (1U<<13);
//
//	/*Set Pull-Down*/
//	GPIOC->PUPDR &=~(1U<<26);
//	GPIOC->PUPDR |= (1U<<27);
}





