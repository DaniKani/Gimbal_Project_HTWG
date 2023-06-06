#ifndef GYR_ACC_CALIBRATION_H_
#define GYR_ACC_CALIBRATION_H_
#define GPIOCEN	(1U<<2)
#define BTN_PIN	(1U<<13)

#include <stm32f4xx.h>


//extern uint16_t cnt_measure_points;


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
}Offset_Scale_value_acc;

typedef struct
{
	float x1_data, x2_data;
	float y1_data, y2_data;
	float z1_data, z2_data;
}values_acc;

void BTN_init(void);
void Offset_Calibration_acc(values_acc* data, Offset_Scale_value_acc* solution, float gyro_x, float gyro_y, float gyro_z, uint16_t number_measure_points);
void Offset_Calibration_gyro(Offset_value_gyro* data, float gyro_x, float gyro_y, float gyro_z, uint16_t cnt_gyro_measure_points, uint16_t Measurement_cnt);
extern uint8_t mode;

#endif /* GYR_ACC_CALIBRATION_H_ */
