#include "PID.h"
#include "MCP4725.h"
#include "ADS1115.h"
#include "usart.h"
struct PID pid;

void PID_Init(void)
{
	pid.Kp=300;
	pid.Ki=50;
	pid.Kd=5;
	
	pid.out_max=20;
	pid.out_min=-20;
	pid.Ki_max=10;
	pid.Ki_min=-10;
}
float PID_realize(float target,float actual_val)
{
	pid.err=target-actual_val;
	
	pid.integral+=pid.Ki*pid.err;
	if(pid.integral>=pid.Ki_max)pid.integral=pid.Ki_max;
	if(pid.integral<=pid.Ki_min)pid.integral=pid.Ki_min;
	
	pid.output_val=pid.Kp*pid.err + pid.integral + pid.Kd*(pid.err-pid.err_last);
	pid.err_last=pid.err;
	
	if(pid.output_val>=pid.out_max)pid.output_val=pid.out_max;
	if(pid.output_val<=pid.out_min)pid.output_val=pid.out_min;
	
	return pid.output_val;
}




