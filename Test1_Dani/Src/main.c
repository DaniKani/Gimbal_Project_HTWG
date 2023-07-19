#include "i2c_dma.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include "dma.h"
#include "adc_dma.h"
#include "mpu9250.h"
#include <string.h>
#include "tim_sample_mpu.h"
#include "systick.h"
#include "Gyr_Acc_Calibration.h"
#include "stdint.h"
#include "Global_Variables.h"
#include "EKF.h"
#include "system_stm32f4xx.h"
#include "System_Clock.h"
#include "MLX90393.h"
#include "uart.h"
#include <GY_511.h>


float KALMAN_P_INIT = 0.1;
float KALMAN_Q = 0.01;
float KALMAN_R = 0.0001;		//3e-06f (vorschlag Chatgpt)	//0.011f

float B_roll[3];
float B_rp[3];
float B_pr[3];
float B_r1r2r3[3], B_r3r2r1[3];
float yawRefMag_r3r2r1, yawRefMag_r1r2r3;


float acc_x,acc_y,acc_z;
float gyro_x , gyro_y, gyro_z;

extern float pitch_avg, roll_avg;

float gyro_z_messung;

float magx, magy, magz;
float yawRefMag_rp;
float yawRefMag_pr;
float yawRefMag_roll;
float yawRefMag_raw, yawRefMag;
float roll_init, pitch_init, yaw_init;

uint64_t core_clock = 0;
uint32_t before, after;
double double_time_taken;
float time_taken;
uint16_t ii;

float roll_angle_up;
float pitch_angle_up;
float yaw_angle_up;
float roll_angle_pr;	//phi
float pitch_angle_pr;	//theta
float yaw_angle_pr;		//psi

/*For Calibration*/
Offset_Scale_value_acc Offset_Scale_acc;
values_acc	Values_acc;
Offset_value_gyro Offset_gyro;

Offset_Scale_value_acc measurements_acc_mpu9250 ={
		.x_offset_acc	= 0.0556f,
		.x_scale_acc	= 1.0012f,
		.y_offset_acc	= 0.0236f,
		.y_scale_acc	= 1.0022f,
		.z_offset_acc	= 0.1108f,
		.z_scale_acc	= 1.0177f,
};

Offset_value_gyro measurements_gyro_mpu9250;

uint16_t cnt_gyro_cali = 0;
uint16_t counter_pb =0;
float delta_t_gyro;
float timer_cnt=0;
uint8_t Zustand = 2;
void static get_camera_position(lsm303MagData *MagnetometerData,Offset_Scale_value_acc* acc_offset_scale, Offset_value_gyro* gyro_offset, int8_t *Magneto_offset);
void static set_gyro_offset(uint16_t counter, uint16_t cyle_times);
void static get_camera_position_calibration(void);
void YAW_Complementary(EKF *ekf, float alpha);
void MagYaw_to_RefKoordinate(EKF *ekf, lsm303MagData *Mag);
void MagYaw_RollKompensated (EKF *data, float Bx, float By, float Bz);
void Roll_Pitch_transformation(float *Bx_corrected, float *By_corrected, float *Bz_corrected, float *cos_r, float *sin_r, float *cos_p, float *sin_p);
void Pitch_Roll_transfomration(float *Bx_corrected, float *By_corrected, float *Bz_corrected, float *cos_r, float *sin_r, float *cos_p, float *sin_p);
void Roll_transfomration(float *Bx_corrected, float *By_corrected, float *Bz_corrected, float *cos_r, float *sin_r);
void R1_R2_R3_transformation(float *Bx_corrected, float *By_corrected, float *Bz_corrected, float *cos_r, float *sin_r, float *cos_p, float *sin_p, float *sin_y, float *cos_y);
void R3_R2_R1_transfomration(float *Bx_corrected, float *By_corrected, float *Bz_corrected, float *cos_r, float *sin_r, float *cos_p, float *sin_p, float *sin_y, float *cos_y);

EKF Start_Conditions;
lsm303MagData MagnetometerData;
int8_t Magneto_offset[3]={0, 0, 0};
uint8_t r = 0;

float yaw_raw = 0;

void GPIO_PA8_Init(void){

	/*1.Enable clk to PORT A*/
	RCC->AHB1ENR |= 1U<<0;

	/*2. Set PIN to Output*/
	GPIOA->MODER |= (1U<<16);
	GPIOA->MODER &= ~(1U<<17);
	GPIOA->BSRR = (1U<<24);		//Reset PA8
}


int main(void)
{
	GPIO_PA8_Init();

	/*create start conditions for the Kalman-Filter*/
	float P[2]={KALMAN_P_INIT, KALMAN_P_INIT};			//Kovarianzmatrix
	float Q[2]={KALMAN_Q, KALMAN_Q}; 					//Kovarianzmatrix Prozessrauschen
	float R[3]={KALMAN_R,KALMAN_R,KALMAN_R};			//Kovarianzmatrix Messrauschen

	/*create start conditions for the Kalman-Filter*/
//	float P_Yaw[2]={KALMAN_P_INIT, KALMAN_P_INIT};			//Kovarianzmatrix
//	float Q_Yaw[2]={KALMAN_Q, KALMAN_Q, KALMAN_Q}; 			//Kovarianzmatrix Prozessrauschen
//	float R_Yaw[3]={KALMAN_R,KALMAN_R,KALMAN_R};			//Kovarianzmatrix Messrauschen

	EKF_Init(&Start_Conditions, P, Q, R);

	/*local_Variables*/
	//Offset_value_gyro  measurements_gyro_mpu9250 = {-0.17926,0.06552,0.01092};
	//Offset_value_gyro  measurements_gyro_mpu9250 = {0,0,0};	//calibration gets executed at the beginning
	//Offset_Scale_value_acc measurements_acc_mpu9250 = {0.03552, 9.81508/9.81f,0.01730,9.82851/9.81f,0.08203,9.97796/9.81f};

	/*Enable User Button*/
	BTN_init();

	/*SysTick Timer init*/
	systick_counter_init();

	/***MPU*config***************************************/
	/*Enable SPI*/
	spi1_dma_init();

	/*Enable Floating Point Unit*/
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

	/*Config NCS pin*/
	mpu9250_ncs_pin_config();

	/*Enable tx stream*/
	dma2_stream3_spi_tx_init();

	/*Enable rx stream*/
	dma2_stream2_spi_rx_init();
	/******************************************************/

	/*ACCELEROMETER+Gyroskope****START SPI********/
	/*Reset NCS pin*/
	mpu9250_ncs_pin_reset();

	/*Config accel & gyro*/
	mpu9250_accel_config(ACC_FULL_SCALE_2_G);
	mpu9250_gyro_config(GYRO_FULL_SCALE_250);

	/*Set NCS pin to high-level*/
	mpu9250_ncs_pin_set();
	/**************END SPI************************/

// delta_t_gyro = tim2_500hz_interrupt_init();
//	delta_t_gyro = tim2_100hz_interrupt_init();


	//SystemClock_Config();
	SystemCoreClockUpdate(); //Used to read the HCLK frequency

	 core_clock = SystemCoreClock;

	/***Magnetometer*config********************************/
	/*Enable I2C*/
	i2c1_init();

	/*Enable Floating Point Unit*/
	//SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

	/*Enable tx stream*/
	dma1_stream6_i2c1_tx_init();

	/*Enable rx stream*/
	dma1_stream5_i2c1_rx_init();
	/*******************************************************/
	/*Config Magnetometer*/
	GY511_init(LSM303_CONTIMODE, LSM303_MAGGAIN_8_1, LSM303_MAGRATE_220);
	uart2_rx_interrupt_init();
	/******************************************************/

	/*Enable Timer 1kHz*/
	delta_t_gyro = tim2_1khz_interrupt_init();
	NVIC_SetPriority(TIM2_IRQn,70);



	while(1)
	{
//		before = SysTick->VAL;
//		after = SysTick->VAL;
//		double_time_taken = (before - after)*0.0000000625;
//		if(double_time_taken<1){
//			time_taken= (float)double_time_taken;
//		}
	}
}



/*FUNCTIONS***********************************/


/*INTERRUPTS**********************************/
void TIM2_IRQHandler(void) // jede 1ms Interrupt
{
	/*Clear update interrupt flag*/
	TIM2->SR &=~SR_UIF;

	static float res_time_Z0 = 0;
	static float timer_cnt_Z0 = 0;
	static uint8_t g = 0;
	static uint16_t calibration_cycles = 1000;



	switch(Zustand){

		case 0:
			timer_cnt_Z0++;
			res_time_Z0 = delta_t_gyro*timer_cnt_Z0;

			if(!(GPIOC->IDR & BTN_PIN) && res_time_Z0 < 5)
			{
				Zustand = 4;
			}

			if (res_time_Z0 >= 5)
			{
				timer_cnt_Z0 = 0;
				//Zustand = 4; //direkt zur EKF Berechnung
			}

		break;


		case 1:															// Magnetometer Kalibrierung
			// Zuerst GUI starten
//			if((!(GPIOC->IDR & BTN_PIN)) || g==1)
//			{
//				g = 1;
				GY_511_update(&MagnetometerData, Magneto_offset);
				uart_send_Magneto(&MagnetometerData);
				uart_send_yaw(&MagnetometerData);

				int allNonZero = 1;  // Annahme, dass alle Werte ungleich Null sind

				    for(int i = 0; i < 3; i++)
				    {
				        if(Magneto_offset[i] == 0)
				        {
				            allNonZero = 0;  // Wenn ein Wert gleich Null ist, setzen Sie allNonZero auf 0

				        }
				    }


				if(allNonZero)
				{
					Zustand = 2;
				}
//			}

			break;

		case 2:	//Gyro Kalibrierung
			set_gyro_offset(cnt_gyro_cali, calibration_cycles);

			cnt_gyro_cali++;

			if(cnt_gyro_cali > calibration_cycles)
			{
				//Zustand = 3;
//				Start_Conditions.pitch_r = pitch_avg;
//				Start_Conditions.roll_r = roll_avg;
				Zustand = 4;
			}

			break;

		case 3:	//Acc Kalibrierung

			get_camera_position_calibration();
			Offset_Calibration_acc(&Values_acc,&measurements_acc_mpu9250, acc_x, acc_y, acc_z, (uint16_t) 1000);

			break;

		case 4: //EKF mit Complementary Filter
			get_camera_position(&MagnetometerData, &measurements_acc_mpu9250, &measurements_gyro_mpu9250, Magneto_offset);

			break;
	}


}



void static get_camera_position(lsm303MagData *MagnetometerData,Offset_Scale_value_acc* acc_offset_scale, Offset_value_gyro* gyro_offset, int8_t *Magneto_offset)
{
		static uint8_t enable = 0;
		/*Set NCS pin to low-level*/
		mpu9250_ncs_pin_reset();
		/*Update accel values*/
		mpu9250_accel_gyro_update();
		/*Set NCS pin to high-level*/
		mpu9250_ncs_pin_set();

		/*Get accel data*/
		acc_x =  mpu9250_get_acc_x()/acc_offset_scale->x_scale_acc - acc_offset_scale->x_offset_acc;
		acc_y =  mpu9250_get_acc_y()/acc_offset_scale->y_scale_acc - acc_offset_scale->y_offset_acc;
		acc_z =  mpu9250_get_acc_z()/acc_offset_scale->z_scale_acc - acc_offset_scale->z_offset_acc;

		/*Get accel data*/
		gyro_x =  mpu9250_get_gyro_x()-gyro_offset->x_offset_gyro;
		gyro_y =  mpu9250_get_gyro_y()-gyro_offset->y_offset_gyro;
		gyro_z =  mpu9250_get_gyro_z()-gyro_offset->z_offset_gyro;
		//gyro_z_messung = gyro_z * 180/M_PI;

		/* 1. Roll und Pitch aus Acc mit KardanWinkel */



		/* 2. Roll und Pitch in "YAW_Init_Mag" um den Yaw zu berechnen und Referenzkoordinatensystem zu erhalten */

//		if(!enable){
//		for(uint8_t i = 0; i<10; i++){YAW_Init_Mag(MagnetometerData, Magneto_offset);}
//		//YAW_Init_Mag(MagnetometerData, Magneto_offset);
//		while(!MagnetometerData->yaw)YAW_Init_Mag(MagnetometerData, Magneto_offset);
//		Start_Conditions.yaw_r = MagnetometerData->yaw; // in Radiant
//		//Start_Conditions.roll_r
//		//Start_Conditions.pitch_r
//		enable = 1;
//		}
		EKF_Predict(&Start_Conditions, gyro_x, gyro_y, gyro_z, delta_t_gyro);

		roll_angle_pr	= Start_Conditions.roll_r 	*180.0f/M_PI;
		pitch_angle_pr	= Start_Conditions.pitch_r 	*180.0f/M_PI;
		yaw_angle_pr	= Start_Conditions.yaw_r 	*180.0f/M_PI;
//		after = SysTick->VAL;
//		time_taken = (before - after)*0.0000000625;

		if (ii==10)
		{
			// update Roll, Pitch
			//EKF_Update(&Start_Conditions, acc_x, acc_y, acc_z);
			roll_angle_up	= Start_Conditions.roll_r 	*180.0f/M_PI;
			pitch_angle_up	= Start_Conditions.pitch_r 	*180.0f/M_PI;
			// update Yaw
			//GY_511_update(MagnetometerData, Magneto_offset);
			//MagYaw_RollKompensated(&Start_Conditions, MagnetometerData->x, MagnetometerData->y, MagnetometerData->z);
			//MagYaw_to_RefKoordinate(&Start_Conditions,MagnetometerData);
			//YAW_Complementary(&Start_Conditions, 0.02);
			yaw_angle_up	= Start_Conditions.yaw_r *180.0f/M_PI;

			ii=0;
		}
		ii++;
}

void static get_camera_position_calibration(void)
{
		/*Set NCS pin to low-level*/
		mpu9250_ncs_pin_reset();
		/*Update accel values*/
		mpu9250_accel_gyro_update();
		/*Set NCS pin to high-level*/
		mpu9250_ncs_pin_set();

		/*Get accel data*/
		acc_x =  mpu9250_get_acc_x();
		acc_y =  mpu9250_get_acc_y();
		acc_z =  mpu9250_get_acc_z();

}

void static set_gyro_offset(uint16_t counter, uint16_t cycle_times)
{
		/*Set NCS pin to low-level*/
		mpu9250_ncs_pin_reset();
		/*Update accel values*/
		mpu9250_accel_gyro_update();
		/*Set NCS pin to high-level*/
		mpu9250_ncs_pin_set();
		counter_pb++;
		/*Get accel data*/
		gyro_x =  mpu9250_get_gyro_x();
		gyro_y =  mpu9250_get_gyro_y();
		gyro_z =  mpu9250_get_gyro_z();

		acc_x =  mpu9250_get_acc_x();
		acc_y =  mpu9250_get_acc_y();
		acc_z =  mpu9250_get_acc_z();

		Offset_Calibration_gyro(&measurements_gyro_mpu9250, gyro_x, gyro_y, gyro_z, counter, cycle_times);
		//PitchRollInit(acc_x, acc_y, acc_z, counter, cycle_times);
}

void USART2_IRQHandler(void)
{
	/*ChecK if RXNE is set*/
	if(USART2->SR & SR_RXNE)
	{
		Magneto_offset[r] = uart2_read();
		r++;
	}
}

void YAW_Complementary(EKF *ekf, float alpha){

//	float yawAngle = (atan2f((float)Mag->Raw_Buffer16[2], (float)Mag->Raw_Buffer16[0])); //tan(y/x)
//
//	// Yaw-Winkel auf den Bereich von 0 bis 360 Grad anpassen
//	if (yawAngle < 0)
//	{
//		yawAngle += 360.0f;
//	}
	ekf->yaw_r =  yawRefMag_pr*alpha+ekf->yaw_r*(1-alpha);
}

void MagYaw_to_RefKoordinate(EKF *ekf, lsm303MagData *Mag)// float Bx_const, float By_const, float Bz_const) 
{

	/* Compute output function h(x,u) */
		float sin_r = sinf(ekf->roll_r);
		float sin_p = sinf(ekf->pitch_r);
		float sin_y = sinf(ekf->yaw_r);
		float cos_r = cosf(ekf->roll_r);
		float cos_p = cosf(ekf->pitch_r);
		float cos_y = cosf(ekf->yaw_r);

		//Euler Umrechnung auf Referenzkoordinatensystem mit h[3] = C[3][3] *mag_roh[3]
		float h[3]={
				 	// 1 Zeile
					cos_p*cos_y * Mag->x                       + -cos_p*sin_y * Mag->y                    +  sin_p  * Mag->z,
					// 2 Zeile
					(cos_r*sin_y + sin_r*sin_p*cos_y) *Mag->x  + (cos_r*cos_y-sin_r*sin_p*sin_y) * Mag->y + (-sin_r*cos_p) * Mag->z,
					// 3 Zeile
					(sin_r*sin_y - cos_r*sin_p*cos_y) * Mag->x  + (sin_r*cos_y+cos_r*sin_p*sin_y) * Mag->y  + (cos_r*cos_p)* Mag->z};

		magx = h[0];
		magy = h[1];
		magz = h[2];

		yawRefMag = atan2f(magy,magx);// * 180.0f / M_PI;

			// Yaw-Winkel auf den Bereich von 0 bis 360 Grad anpassen
			if (yawRefMag < 0)
			{
				yawRefMag += 2*M_PI; //360.0f;
			}

		//ekf->yaw_r = yawAngle;
}

void MagYaw_RollKompensated (EKF *data, float Bx, float By, float Bz)
{
	//yaw_raw = atan2f (By,Bx)*180.f / M_PI;
	float cos_r = cosf(data->roll_r);
	float sin_r = sinf(data->roll_r);
	float cos_p = cosf(data->pitch_r);
	float sin_p = sinf(data->pitch_r);
	float cos_y = cosf(data->yaw_r);
	float sin_y = sinf(data->yaw_r);

  float Bx_corrected = By;
  float Bz_corrected = Bz;
  float By_corrected = -Bx;

  //Roll_Pitch_transformation(&Bx_corrected, &By_corrected, &Bz_corrected, &cos_r, &sin_r, &cos_p, &sin_p);
  Pitch_Roll_transfomration(&Bx_corrected, &By_corrected, &Bz_corrected, &cos_r, &sin_r, &cos_p, &sin_p);
  //Roll_transfomration(&Bx_corrected, &By_corrected, &Bz_corrected, &cos_r, &sin_r);
  //R1_R2_R3_transformation(&Bx_corrected, &By_corrected, &Bz_corrected, &cos_r, &sin_r, &cos_p, &sin_p, &sin_y, &cos_y);
  //R3_R2_R1_transfomration(&Bx_corrected, &By_corrected, &Bz_corrected, &cos_r, &sin_r, &cos_p, &sin_p, &sin_y, &cos_y);
  yawRefMag_pr = atan2f(B_pr[1], B_pr[0]);// *180.0f / M_PI;
  //yawRefMag_rp = atan2f(B_rp[1], B_rp[0]) *180.0f / M_PI;
  //yawRefMag_roll = atan2f(B_roll[1], B_roll[0]) *180.0f / M_PI;
  //yawRefMag_raw = atan2f(By_corrected,Bx_corrected)*180.0f / M_PI;
//  yawRefMag_r1r2r3 = atan2f(B_r1r2r3[1], B_r1r2r3[0]);// *180.0f / M_PI;
//  yawRefMag_r3r2r1 = atan2f(B_r3r2r1[1], B_r3r2r1[0]);

 }

void Roll_Pitch_transformation(float *Bx_corrected, float *By_corrected, float *Bz_corrected, float *cos_r, float *sin_r, float *cos_p, float *sin_p)
{
 B_rp[0] = (*Bx_corrected) * (*cos_p)                                   + (*Bz_corrected) * (*sin_p) ;
 B_rp[1] = (*Bx_corrected) * (-(*sin_r)*-(*sin_p)) + (*By_corrected) * (*cos_r)  + (*Bz_corrected) * (-(*sin_r)*(*cos_p));
 B_rp[2] = (*Bx_corrected) * ((*cos_r)*-(*sin_p))  + (*By_corrected) * (*sin_r)  + (*Bz_corrected) * ((*cos_r) * (*cos_p));
};



void Pitch_Roll_transfomration(float *Bx_corrected, float *By_corrected, float *Bz_corrected, float *cos_r, float *sin_r, float *cos_p, float *sin_p)
{
 B_pr[0] = (*Bx_corrected) * (*cos_p)   + (*By_corrected) * ((*sin_p)*(*sin_r))  + (*Bz_corrected) * ((*sin_p)*(*cos_r));
 B_pr[1] =                        + (*By_corrected) * (*cos_r)          + (*Bz_corrected) * -(*sin_r);
 B_pr[2] = (*Bx_corrected) * -(*sin_p)  + (*By_corrected) * (*cos_p)*(*sin_r)    + (*Bz_corrected) * ((*cos_r) * (*cos_p));
};

void Roll_transfomration(float *Bx_corrected, float *By_corrected, float *Bz_corrected, float *cos_r, float *sin_r)
{
	  B_roll[0] = 1 * (*Bx_corrected);
	  B_roll[1] = (*cos_r) * (*By_corrected) - (*sin_r) * (*Bz_corrected);
	  B_roll[2] = (*sin_r) * (*By_corrected) + (*cos_r) * (*Bz_corrected);
};

void R1_R2_R3_transformation(float *Bx_corrected, float *By_corrected, float *Bz_corrected, float *cos_r, float *sin_r, float *cos_p, float *sin_p, float *sin_y, float *cos_y)
{ //PDF von Uni Stuttgart: Inertial frame -> Body frame
  B_r1r2r3[0] = (*Bx_corrected) * ((*cos_p)*(*cos_y))                            + (*By_corrected) * (-(*cos_p) * (*sin_y))                         + (*Bz_corrected) * (*sin_p) ;
  B_r1r2r3[1] = (*Bx_corrected) * ((*cos_r)*(*sin_y)+(*sin_r)*(*sin_p)*(*cos_y)) + (*By_corrected) * ((*cos_r)*(*cos_y)+(*sin_r)*(*sin_p)*(*sin_y)) + (*Bz_corrected) * (-(*sin_r)*(*cos_p));
  B_r1r2r3[2] = (*Bx_corrected) * ((*sin_r)*(*sin_y)-(*cos_r)*(*sin_p)*(*cos_y)) + (*By_corrected) * ((*sin_r)*(*cos_y)+(*cos_r)*(*sin_p)*(*sin_y)) + (*Bz_corrected) * ((*cos_r) * (*cos_p));
};


void R3_R2_R1_transfomration(float *Bx_corrected, float *By_corrected, float *Bz_corrected, float *cos_r, float *sin_r, float *cos_p, float *sin_p, float *sin_y, float *cos_y)
{ //Formeln von PhilsLab: Body frame -> Inertial frame
  B_r3r2r1[0] = (*Bx_corrected) * ((*cos_p)*(*cos_y))   + (*By_corrected) * ((*sin_p)*(*sin_r)*(*cos_y)-(*cos_y)*(*sin_y))  + (*Bz_corrected) * ((*cos_r)*(*sin_p)*(*cos_y)+(*sin_r)*(*sin_y));
  B_r3r2r1[1] = (*Bx_corrected) * ((*cos_p)*(*sin_y))    + (*By_corrected) * ((*sin_p)*(*sin_r)*(*sin_y)-(*cos_r)*(*cos_y))  + (*Bz_corrected) * ((*cos_r)*(*sin_p)*(*sin_y)-(*sin_r)*(*cos_y));
  B_r3r2r1[2] = (*Bx_corrected) * (-(*sin_p))            + (*By_corrected) * ((*sin_r)*(*cos_p))                             + (*Bz_corrected) * ((*cos_r)*(*cos_p));
};

