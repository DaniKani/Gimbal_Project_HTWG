/*
 * Global_Variables.h
 *
 *  Created on: 09.05.2023
 *      Author: Domin
 */

#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_


//from main
#define x_value_offset_gyro	7.26860428
#define y_value_offset_gyro	0.687759399
#define z_value_offset_gyro	0.792327881

#define x_value_offset_acc	-198.72998
#define y_value_offset_acc	57.7133789
#define z_value_offset_acc	-258.626465

#define x_value_scale_acc	16425.1211
#define y_value_scale_acc	16426.9902
#define z_value_scale_acc	16613.2539

mpu_data Data;

Offset_value_gyro gyro_offset;
Offset_value_acc acc_offset_scale;

uint16_t measurement_cnt = 0;

uint8_t tim = 0;

float acc_x,acc_y,acc_z;
float gyro_x,gyro_y,gyro_z;
uint32_t before, after;
double time_taken;





//from

#endif /* GLOBAL_VARIABLES_H_ */
