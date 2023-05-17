#ifndef __MPU9250_H__
#define __MPU9250_H__

#include <stdint.h>
#include "spi_dma.h"
#include <math.h>
#include "Global_Variables.h"

#define ACC_FULL_SCALE_2_G       0x00
#define ACC_FULL_SCALE_4_G       0x08
#define ACC_FULL_SCALE_8_G       0x10
#define ACC_FULL_SCALE_16_G      0x18

#define GYRO_FULL_SCALE_250		 0x00
#define GYRO_FULL_SCALE_500		 0x08
#define GYRO_FULL_SCALE_1000	 0x10
#define GYRO_FULL_SCALE_2000 	 0x18

#define MPU9250_ADDR_USER_CTRL				  0x6A

#define MPU9250_ADDR_ACCELCONFIG  			  0x1C
#define MPU9250_ACCEL_XOUT_H				  0x3B

#define MPU9250_ADDR_GYROCONFIG  			  0x1B
#define MPU9250_GYRO_XOUT_H					  0x3F

void mpu9250_WHO_AM_I(void);
void mpu9250_read_addr(uint32_t addr);


void mpu9250_accel_config(uint8_t mode);
void mpu9250_accel_gyro_update(void);
float mpu9250_get_acc_x(void);
float mpu9250_get_acc_y(void);
float mpu9250_get_acc_z(void);

float mpu9250_get_temp(void);


void mpu9250_gyro_config(uint8_t mode);
void mpu9250_gyro_update(void);
float mpu9250_get_gyro_x(void);
float mpu9250_get_gyro_y(void);
float mpu9250_get_gyro_z(void);

void mpu9250_ncs_pin_config(void);
void mpu9250_ncs_pin_set(void);
void mpu9250_ncs_pin_reset(void);

extern uint8_t g_tx_cmplt;
extern uint8_t g_rx_cmplt;


#endif
