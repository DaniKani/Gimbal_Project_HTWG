#ifndef __MPU9250_H__
#define __MPU9250_H__

#include <stdint.h>
#include "spi_dma.h"

#define ACC_FULL_SCALE_2_G       0x00
#define ACC_FULL_SCALE_4_G       0x08
#define ACC_FULL_SCALE_8_G       0x10
#define ACC_FULL_SCALE_16_G      0x18

#define GYRO_FS_SEL_250dps     	 0x00 // 0000 0000 = 0x00
#define GYRO_FS_SEL_500dps       0x04 // 0000 0100 = 0x04
#define GYRO_FS_SEL_1000dps      0x08 // 0000 1000 = 0x08
#define GYRO_FS_SEL_2000dps      0x0C // 0000 1100 = 0x0C


#define MPU9250_ADDR_ACCELCONFIG  			  0x1C
#define MPU9250_ADDR_USER_CTRL				  0x6A
#define MPU9250_ACCEL_XOUT_H				  0x3B

#define MPU9250_ADDR_GYROCONFIG  			  0x1B



void mpu9250_accel_config(uint8_t mode);
void mpu9250_accel_update(void);
float mpu9250_get_acc_x(void);
float mpu9250_get_acc_y(void);
float mpu9250_get_acc_z(void);
float mpu9250_get_gyro_x(void);
float mpu9250_get_gyro_y(void);
float mpu9250_get_gyro_z(void);
void mpu9250_ncs_pin_config(void);
void mpu9250_ncs_pin_set(void);
void mpu9250_ncs_pin_reset(void);
void mpu9250_accel_gyro_update(void);
void mpu9250_gyro_config(uint8_t mode);



#endif
