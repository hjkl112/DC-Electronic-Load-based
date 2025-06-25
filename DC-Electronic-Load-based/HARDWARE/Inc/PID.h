#ifndef __PID_H
#define __PID_H

#include "stm32f4xx.h"


struct PID
{
	float err;          //偏差值
	float err_last;     //上一个偏差值
	float Kp,Ki,Kd;     //比例、积分、微分系数
	float integral;     //积分值
	float output_val;   //输出值
	float out_max;
	float out_min;
	float Ki_max;
	float Ki_min;
};


void PID_Init(void);
float PID_realize(float target,float actual_val);




#endif
