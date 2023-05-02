#include "Gyr_Acc_Calibration.h"

uint16_t i;

double sum, offset;

#define Buff_size	1000

double Offset_Calibration(float data)
{
	if(i=0, i < Buff_size, i++)
	{
		sum = sum + data;
	}

	return offset = sum/Buff_size;

}
