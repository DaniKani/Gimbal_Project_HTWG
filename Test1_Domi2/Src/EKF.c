#include "EKF.h"
#include <math.h>
#include <stdio.h>
float g = 9.81;

typedef struct {
    float roll, pitch;
} Gyro_Angles;

Gyro_Angles abc;

typedef struct{
	float aa, ab, ac;
	float ba, bb, bc;

} Kalman_Gain;	//2x3 Matrix

Kalman_Gain Kalman_Gain_;

void EKF_Init(EKF *ekf, float P[2], float Q[2], float R[3]) {

	/* Reset state estimates */
	ekf->roll_r 	= 0.0f;
	ekf->pitch_r 	= 0.0f;

	/* Initialise state covariance matrix */
	ekf->P[0][0] = P[0]; ekf->P[0][1] = 0.0f;
	ekf->P[1][0] = 0.0f; ekf->P[1][1] = P[1];

	/* Set process and measurement noise */
	ekf->Q[0] = Q[0];
	ekf->Q[1] = Q[1];

	ekf->R[0] = R[0];
	ekf->R[1] = R[1];
	ekf->R[2] = R[2];

}

void EKF_Predict(EKF *ekf, float p_rps, float q_rps, float r_rps, float sampleTime_s) {


	/* Pre-compute trigonometric quantities */
	float sin_roll = sinf(ekf->roll_r);
	float cos_roll = cosf(ekf->roll_r);
	float tan_pitch = tanf(ekf->pitch_r);

	/* Compute state transition function dx/dt = f(x,u) */
	float drolldt	= p_rps + tan_pitch * (q_rps * sin_roll + r_rps * cos_roll);
	float dpitchdt	= 					   q_rps * cos_roll - r_rps * sin_roll;

	/* Update state estimates (x(n+1) = x(n) + T * dx/dt) */
	ekf->roll_r 	+= sampleTime_s * drolldt;
	ekf->pitch_r	+= sampleTime_s * dpitchdt;

	/* Re-compute trigonometric quantities */
	sin_roll 			= sinf(ekf->roll_r);
	cos_roll 			= cosf(ekf->roll_r);
	tan_pitch 			= tanf(ekf->pitch_r);
	float cos_pitch_inv = 1.0f / cosf(ekf->pitch_r);

	/* Compute Jacobian of state transition function A(x,u) = df(x,u)/dx */
	float A[2][2] =
	{ 	{ tan_pitch * (q_rps * cos_roll - r_rps * sin_roll) , (q_rps * sin_roll + r_rps * cos_roll) * cos_pitch_inv * cos_pitch_inv },
		{ -(q_rps * sin_roll + r_rps * cos_roll)			, 	  0.0f } };

	/* Update state covariance matrix P(n+1) = P(n) + T * (A * P(n) + P(n) * A' + Q) (note that A[1][1] = 0!) */
	float Pnew[2][2] =
	{	{A[0][0] * ekf->P[0][0] + A[0][1] * ekf->P[1][0] + ekf->P[0][0] * A[0][0] + ekf->P[0][1] * A[0][1] + ekf->Q[0], A[0][0] * ekf->P[0][1] + A[0][1] * ekf->P[1][1] + ekf->P[0][0] * A[1][0]},
		{A[1][0] * ekf->P[0][0] + 						   ekf->P[1][0] * A[0][0] + ekf->P[1][1] * A[0][1], 			A[1][0] * ekf->P[0][1] + 						  ekf->P[1][0] * A[1][0] + ekf->Q[1]} };

	ekf->P[0][0] += sampleTime_s * Pnew[0][0]; ekf->P[0][1] += sampleTime_s * Pnew[0][1];
	ekf->P[1][0] += sampleTime_s * Pnew[1][0]; ekf->P[1][1] += sampleTime_s * Pnew[1][1];
}

void EKF_Update(EKF *ekf, float ax_mps2, float ay_mps2, float az_mps2) {

	/*1.Calculate Kalman Gain*************************************************************************/
	/* Compute Jacobian of output function C(x,u) = dh(x,u)/dx */
	float sin_roll = sinf(ekf->roll_r);
	float cos_roll = cosf(ekf->roll_r);
	float sin_pitch = sinf(ekf->pitch_r);
	float cos_pitch = cosf(ekf->pitch_r);

	float C[3][2] = {	{				     0.0f,	g*cos_pitch},
						{-g* cos_roll * cos_pitch, 	g*sin_roll * sin_pitch},
						{ g*sin_roll *  cos_pitch, 	g*cos_roll * sin_pitch} };

	/* Compute Kalman gain K = P * C' * (R + C * P * C ')^-1 in steps (note that C[0][0] = 0!) */

	/* P * C'*/
	float PCt[2][3] = { {ekf->P[0][1] * C[0][1], ekf->P[0][0] * C[1][0] + ekf->P[0][1] * C[1][1], ekf->P[0][0] * C[2][0] + ekf->P[0][1] * C[2][1]},
						{ekf->P[1][1] * C[0][1], ekf->P[1][0] * C[1][0] + ekf->P[1][1] * C[1][1], ekf->P[1][0] * C[2][0] + ekf->P[1][1] * C[2][1]} };

	/* R + C * P * C' */
	float RCPCt[3][3] = { 	{					   C[0][1] * PCt[1][0] + ekf->R[0],			  C[0][1] * PCt[1][1], 									  C[0][1] * PCt[1][2]},
							{C[1][0] * PCt[0][0] + C[1][1] * PCt[1][0],	C[1][0] * PCt[0][1] + C[1][1] * PCt[1][1] + ekf->R[1],	C[1][0] * PCt[0][2] + C[1][1] * PCt[1][2]},
							{C[2][0] * PCt[0][0] + C[2][1] * PCt[1][0],	C[2][0] * PCt[0][1] + C[2][1] * PCt[1][1],				C[2][0] * PCt[0][2] + C[2][1] * PCt[1][2] + ekf->R[2]} };

	/* Build invert matrix with Cramscher Alogorithem [inv(R + C * P * C')] */
	float detMatInv = 1.0f / (RCPCt[0][0] * (RCPCt[2][2] * RCPCt[1][1] - RCPCt[2][1] * RCPCt[1][2])
					- RCPCt[1][0] * (RCPCt[2][2] * RCPCt[0][1] - RCPCt[2][1] * RCPCt[0][2])
					+ RCPCt[2][0] * (RCPCt[1][2] * RCPCt[0][1] - RCPCt[1][1] * RCPCt[0][2]));

	float matInv[3][3] = { 	{	RCPCt[2][2] * RCPCt[1][1] - RCPCt[2][1] * RCPCt[1][2], -(	RCPCt[2][2] * RCPCt[0][1] - RCPCt[2][1] * RCPCt[0][2]), 	RCPCt[1][2] * RCPCt[0][1] - RCPCt[1][1] * RCPCt[0][2] },
							{-(	RCPCt[2][2] * RCPCt[1][0] - RCPCt[2][0] * RCPCt[1][2]), 	RCPCt[2][2] * RCPCt[0][0] - RCPCt[2][0] * RCPCt[0][2], -(	RCPCt[1][2] * RCPCt[0][0] - RCPCt[1][0] * RCPCt[0][2]) },
							{	RCPCt[2][1] * RCPCt[1][0] - RCPCt[2][0] * RCPCt[1][1], -(	RCPCt[2][1] * RCPCt[0][0] - RCPCt[2][0] * RCPCt[0][1]), 	RCPCt[1][1] * RCPCt[0][0] - RCPCt[1][0] * RCPCt[0][1]} };

	for (unsigned int i = 0; i < 3; i++) {

		for (unsigned int j = 0; j < 3; j++) {

			matInv[i][j] *= detMatInv;

		}

	}

	/* C' * inv(R + C * P * C') */
	float CtmatInv[2][3] = { 	{						  C[1][0] * matInv[1][0] + C[2][0] * matInv[2][0], 							C[1][0] * matInv[1][1] + C[2][0] * matInv[2][1], 						  C[1][0] * matInv[1][2] + C[2][0] * matInv[2][2]},
								{C[0][1] * matInv[0][0] + C[1][1] * matInv[1][0] + C[2][1] * matInv[2][0], C[0][1] * matInv[0][1] + C[1][1] * matInv[1][1] + C[2][1] * matInv[2][1], C[0][1] * matInv[0][2] + C[1][1] * matInv[1][2] + C[2][1] * matInv[2][2]} };

	/* K = P * C' * inv(R + C * P * C') */
	float K[2][3] = { 	{ekf->P[0][0] * CtmatInv[0][0] + ekf->P[0][1] * CtmatInv[1][0], ekf->P[0][0] * CtmatInv[0][1] + ekf->P[0][1] * CtmatInv[1][1], ekf->P[0][0] * CtmatInv[0][2] + ekf->P[0][1] * CtmatInv[1][2]},
						{ekf->P[1][0] * CtmatInv[0][0] + ekf->P[1][1] * CtmatInv[1][0], ekf->P[1][0] * CtmatInv[0][1] + ekf->P[1][1] * CtmatInv[1][1], ekf->P[1][0] * CtmatInv[0][2] + ekf->P[1][1] * CtmatInv[1][2]} };


	Kalman_Gain_.aa = K[0][0];
	Kalman_Gain_.ab = K[0][1];
	Kalman_Gain_.ac = K[0][2];
	Kalman_Gain_.ba = K[1][0];
	Kalman_Gain_.bb = K[1][1];
	Kalman_Gain_.bc = K[1][2];

	/****************************************************************************************************************************/
	/* Normalise accelerometer readings */
	//float accNormFactor = 1.0f / sqrtf(ax_mps2 * ax_mps2 + ay_mps2 * ay_mps2 + az_mps2 * az_mps2);

	float ax_norm 		= ax_mps2 ;//* accNormFactor;
	float ay_norm 		= ay_mps2 ;//* accNormFactor;
	float az_norm 		= az_mps2 ;//* accNormFactor;

	/* Update state covariance matrix P(n+1) = (I - K * C) * P(n) */ //I = [0 0], [0 0]
	float IminKC[2][2] = { 	{1.0f - (K[0][1] * C[1][0] + K[1][0] * C[2][0]), -(K[0][1] * C[1][1] + K[1][0] * C[2][1])},
							{- (K[1][1] * C[1][0] + K[1][2] * C[2][0]), 	1.0f-(K[1][1] * C[1][1] + K[1][2] * C[2][1])} };

	float Pnew[2][2] = { 	{IminKC[0][0] * ekf->P[0][0] + IminKC[0][1] * ekf->P[1][0], IminKC[0][0] * ekf->P[0][1] + IminKC[0][1] * ekf->P[1][1]},
							{IminKC[1][0] * ekf->P[0][0] + IminKC[1][1] * ekf->P[1][0], IminKC[1][0] * ekf->P[0][1] + IminKC[1][1] * ekf->P[1][1]} };

	ekf->P[0][0] = Pnew[0][0]; ekf->P[0][1] = Pnew[0][1];
	ekf->P[1][0] = Pnew[1][0]; ekf->P[1][1] = Pnew[1][1];

	/* Compute output function h(x,u) */
	float h[3] = {	 g*sinf(ekf->pitch_r),
					-g*cosf(ekf->pitch_r) * sinf(ekf->roll_r),
					-g*cosf(ekf->pitch_r) * cosf(ekf->roll_r) };

	/* Update state estimate x(n+1) = x(n) + K * (y - h) */
	ekf->roll_r 	+= (K[0][0] * (ax_norm - h[0]) + K[0][1] * (ay_norm - h[1]) + K[0][2] * (az_norm - h[2]));
	ekf->pitch_r 	+= (K[1][0] * (ax_norm - h[0]) + K[1][1] * (ay_norm - h[1]) + K[1][2] * (az_norm - h[2]));

}

/************************************************************************************************/
void Euler_Angle(EKF *ekf, float p_rps, float q_rps, float r_rps, float sampleTime_s)
{
	/* Pre-compute trigonometric quantities */
	float sp = sinf(ekf->roll_r);
	float cp = cosf(ekf->roll_r);
	float tt = tanf(ekf->pitch_r);

	/* Compute state transition function dx/dt = f(x,u) */
	float droll_new		= p_rps + tt * (q_rps * sp + r_rps * cp);
	float dpitch_new	= 				q_rps * cp - r_rps * sp;

	/* Update state estimates (x(n+1) = x(n) + T * dx/dt) */
	ekf->roll_r	 += sampleTime_s * droll_new;
	ekf->pitch_r += sampleTime_s * dpitch_new;
}

	//Start values
Quaternion quaternion_multiply(Quaternion a, Quaternion b) {
    Quaternion result;
    result.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    result.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    result.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
    result.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
    return result;
}
void quaternion_Angle(EKF *ekf, float wx, float wy, float wz, float delta_t) {

	Quaternion qq;
	Quaternion* ptr_qq = &qq;


	float w = sqrt(wx * wx + wy * wy + wz * wz);

	if (w < 1e-9) return;

    Quaternion q_rot;
    float cos_half_angle = cos(w * delta_t / 2);
    float sin_half_angle = sin(w * delta_t / 2);;

    float delta_qw = cos_half_angle;
	float delta_qx = (wx / w) * sin_half_angle;
	float delta_qy = (wy / w) * sin_half_angle;
	float delta_qz = (wz / w) * sin_half_angle;

    float q0 = 1, qx = 0, qy = 0, qz = 0;

    float updated_qw = q0 * delta_qw - qx * delta_qx - qy * delta_qy - qz * delta_qz;
	float updated_qx = q0 * delta_qx + qx * delta_qw + qy * delta_qz - qz * delta_qy;
	float updated_qy = q0 * delta_qy - qx * delta_qz + qy * delta_qw + qz * delta_qx;
	float updated_qz = q0 * delta_qz + qx * delta_qy - qy * delta_qx + qz * delta_qw;

    /*Convert quaternions to euler angular*/
    ekf->roll_r = atan2(2 * (updated_qw * updated_qx + updated_qy * updated_qz), 1 - 2 * (updated_qx * updated_qx + updated_qy * updated_qy));
    ekf->pitch_r = asin(2 * (updated_qw * updated_qy - updated_qz * updated_qx));
}

void EKF_Predict_modular(EKF *ekf, float p_rps, float q_rps, float r_rps, float sampleTime_s) {

	// phi = roll
	// theta = pitch
	//Gyro_Angles Euler_Angles;
	//Gyro_Angles Quaternion_Angles;

	//Euler_Angle(ekf, p_rps, q_rps, r_rps, sampleTime_s);
	quaternion_Angle(ekf, p_rps, q_rps, r_rps, sampleTime_s);

	/* Re-compute trigonometric quantities */
	float sp	= sinf(ekf->roll_r);
	float cp 	= cosf(ekf->roll_r);
	float tt	= tanf(ekf->pitch_r);
	float ctInv = 1.0f / cosf(ekf->pitch_r);

	/* Compute Jacobian of state transition function A(x,u) = df(x,u)/dx */
	float A[2][2] =
	{ 	{ tt * (q_rps * cp - r_rps * sp), (q_rps * sp + r_rps * cp) * ctInv * ctInv },
		{ -(q_rps * sp + r_rps * cp), 	  0.0f } };

	/* Update state covariance matrix P(n+1) = P(n) + T * (A * P(n) + P(n) * A' + Q) (note that A[1][1] = 0!) */
	float Pnew[2][2] =
	{	{A[0][0] * ekf->P[0][0] + A[0][1] * ekf->P[1][0] + ekf->P[0][0] * A[0][0] + ekf->P[0][1] * A[1][0] + ekf->Q[0], A[0][0] * ekf->P[0][1] + A[0][1] * ekf->P[1][1] + ekf->P[0][0] * A[0][1]},
		{A[1][0] * ekf->P[0][0] + 						   ekf->P[1][0] * A[0][0] + ekf->P[1][1] * A[1][0], 			A[1][0] * ekf->P[0][1] + 						  ekf->P[1][0] * A[0][1] + ekf->Q[1]} };

	ekf->P[0][0] += sampleTime_s * Pnew[0][0]; ekf->P[0][1] += sampleTime_s * Pnew[0][1];
	ekf->P[1][0] += sampleTime_s * Pnew[1][0]; ekf->P[1][1] += sampleTime_s * Pnew[1][1];


}




