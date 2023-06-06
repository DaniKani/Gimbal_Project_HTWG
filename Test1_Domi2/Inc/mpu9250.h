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



// AK8963 registers
#define magneto_sensitivity 		0.6
#define AK8963_I2C_ADDR 			0x0C
#define AK8963_HXL 					0x03
#define AK8963_CNTL1 				0x0A
#define AK8963_PWR_DOWN 			0x00
#define AK8963_CNT_MEAS1 			0x12
#define AK8963_CNT_MEAS2 			0x16
#define AK8963_FUSE_ROM 			0x0F
#define AK8963_CNTL2 				0x0B
#define AK8963_RESET 				0x01
#define AK8963_ASA 					0x10


#define I2C_SLV0_ADDR 0x25
#define I2C_SLV0_DO 0x63
#define I2C_SLV0_CTRL 0x27
#define I2C_SLV0_REG 0x26
#define I2C_SLV0_EN 0x80
#define I2C_MST_CTRL 0x24
#define I2C_MST_CLK 0x0D



#define I2C_READ_FLAG 0x80
#define EXT_SENS_DATA_00 0x49


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
float mpu9250_get_mag_x(void);
float mpu9250_get_mag_y(void);
float mpu9250_get_mag_z(void);


void mpu9250_mag_config(void);
void readAK8963_WHOAMI(uint8_t *dest);
void writeAK8963Register(uint8_t subAddress, uint8_t data);
void readAK8963Registers(uint8_t subAddress, uint8_t count, uint8_t* dest);
void mpu9250_magneto_update(void);

void mpu9250_ncs_pin_config(void);
void mpu9250_ncs_pin_set(void);
void mpu9250_ncs_pin_reset(void);

extern uint8_t g_tx_cmplt;
extern uint8_t g_rx_cmplt;




#endif
