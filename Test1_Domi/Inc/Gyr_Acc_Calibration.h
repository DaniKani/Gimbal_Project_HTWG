/*
 * Gyr_Acc_Calibration.h
 *
 *  Created on: 02.05.2023
 *      Author: Domin
 */

#ifndef GYR_ACC_CALIBRATION_H_
#define GYR_ACC_CALIBRATION_H_
#include <stdint.h>
#include "mpu9250.h"


typedef struct
{
	float x_offset_gyro;
	float y_offset_gyro;
	float z_offset_gyro;
}Offset_value_gyro;

typedef struct
{
	float x_offset_acc, x_scale_acc;
	float y_offset_acc, y_scale_acc;
	float z_offset_acc, z_scale_acc;
}Offset_value_acc;

void Offset_Calibration_gyro(Offset_value_gyro* data, float gyro_x, float gyro_y, float gyro_z, uint16_t* Measurement_cnt);
void Offset_Calibration_acc(Offset_value_acc* data, float acc_x, float acc_y, float acc_z, uint16_t* Measurement_cnt);
void BTN_init(void);


#include <stm32f4xx.h>
#include <stdint.h>

#endif /* GYR_ACC_CALIBRATION_H_ */
