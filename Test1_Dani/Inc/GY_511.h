#ifndef __I2C_DMA_H__
#define __I2C_DMA_H__

#define RAD_TO_DEG(rad) ((rad) * 180.0f / M_PI)

#include <stdint.h>


#define ACC_FULL_SCALE_2_G       0x00
#define ACC_FULL_SCALE_4_G       0x08
#define ACC_FULL_SCALE_8_G       0x10
#define ACC_FULL_SCALE_16_G      0x18


/*Register address*/
#define CRA_REG_M	0x00
#define CRB_REG_M	0x01
#define MR_REG_M	0x02
#define OUT_X_H_M	0x03
#define	SR_REG_Mg	0x09

/*Bits*/
#define  LSM303_MAGGAIN_1_3 0x20	// +/- 1.3
#define  LSM303_MAGGAIN_1_9 0x40	// +/- 1.9
#define  LSM303_MAGGAIN_2_5 0x60	// +/- 2.5
#define  LSM303_MAGGAIN_4_0 0x80	// +/- 4.0
#define  LSM303_MAGGAIN_4_7 0xA0 	// +/- 4.7
#define  LSM303_MAGGAIN_5_6 0xC0	// +/- 5.6
#define  LSM303_MAGGAIN_8_1 0xE0	// +/- 8.1

#define  LSM303_MAGRATE_0_7 0x00	// 0.75 Hz
#define  LSM303_MAGRATE_1_5 0x04	// 1.5 Hz
#define  LSM303_MAGRATE_3_0 0x08	// 3.0 Hz
#define  LSM303_MAGRATE_7_5 0x0C	// 7.5 Hz
#define  LSM303_MAGRATE_15  0x10	// 15 Hz
#define  LSM303_MAGRATE_30  0x14	// 30 Hz
#define  LSM303_MAGRATE_75  0x18	// 75 Hz
#define  LSM303_MAGRATE_220 0x1C	// 220 Hz

#define LSM303_CONTIMODE	0x00	// continuous conversion
#define LSM303_SINGLEMODE	0x01	// single conversion
#define LSM303_SLEEPMODE	0x02	// sleep mode

#define GY_511_MAGNETO_OUT_X_H_M			  0x03

#define SENSORS_GAUSS_TO_MICROTESLA 0.1f

typedef struct{
  uint8_t Raw_Buffer[6];
  uint8_t test;
  float x; ///< x-axis data
  float y; ///< y-axis data
  float z; ///< z-axis data
  float yaw;
} lsm303MagData;



void GY511_init(uint8_t mode, uint8_t gain, uint8_t rate);
void GY_511_update(lsm303MagData *data);
void GY_511_update_alt(lsm303MagData *data);




#endif


