#ifndef __PID_H
#define __PID_H

#include "stm32f4xx.h"


struct PID
{
	float err;          //ƫ��ֵ
	float err_last;     //��һ��ƫ��ֵ
	float Kp,Ki,Kd;     //���������֡�΢��ϵ��
	float integral;     //����ֵ
	float output_val;   //���ֵ
	float out_max;
	float out_min;
	float Ki_max;
	float Ki_min;
};


void PID_Init(void);
float PID_realize(float target,float actual_val);




#endif
