#ifndef EKF_H
#define EKF_H

#include <stdio.h>
#include <math.h>
#include "GY_511.h"

typedef struct {

	float roll_r;
	float pitch_r;
	float yaw_r;

	float P[2][2];

	float Q[2];
	float R[3];

} EKF;

extern uint8_t aa;
typedef struct {
    double w, x, y, z;
} test_test;


typedef struct {
    double w, x, y, z;
} Quaternion;


void EKF_Init(EKF *ekf, float P[2], float Q[2], float R[3]);

void EKF_Predict(EKF *ekf, float p_rps, float q_rps, float r_rps, float sampleTime_s);

void EKF_Update(EKF *ekf, float ax_mps2, float ay_mps2, float az_mps2);

void EKF_Predict_modular(EKF *ekf, float p_rps, float q_rps, float r_rps, float sampleTime_s);

/******YAW-Achse********/
typedef struct {

	float roll_r;
	float pitch_r;
	float yaw_r;

	float P[2][2];

	float Q[3];
	float R[3];

} EKF_YAW;

void EKF_YAW_Init(EKF_YAW *ekf, float P[2], float Q[2], float R[3]);
void EKF_YAW_Predict(EKF_YAW *ekf, float p_rps, float q_rps, float r_rps, float sampleTime_s);
//void EKF_YAW_Update(EKF_YAW *ekf, float ax_mps2, float ay_mps2, float az_mps2);
float YAW_Complementary(lsm303MagData *Mag, EKF *ekf, float alpha);

#endif
