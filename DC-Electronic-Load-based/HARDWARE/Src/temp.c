#include "temp.h"
#include "adc.h"
#include "lv_obj_my.h"
#include "usart.h"
#include "stdio.h"
#define T25 298.15   
#define R25 10
#define B	3435
__IO uint32_t ADC_ConvertedValue;
extern uint16_t temp_time;
float temp_GET_R(void)
{
	double v1,v2,r;
	v1=(float)ADC_ConvertedValue/4096;
	v1=v1*3.3;
	v2=3.3f-v1;
  r=(v2/v1)*10;
//	Usart1Printf("%f\r\n",v1);
	return r;
}
void Temp_Init(void)
{
	HAL_ADC_Start_IT(&hadc1); 
}


double myln(double a)
{
   int N = 15;
   int k,nk;
   double x,xx,y;
   x = (a-1)/(a+1);
   xx = x*x;
   nk = 2*N+1;
   y = 1.0/nk;
   for(k=N;k>0;k--)
   {
     nk = nk - 2;
     y = 1.0/nk+xx*y;
     
   }
   return 2.0*x*y;
}
 
float Get_Kelvin_Temperature(void)
{
	float N1,N2,N3,N4;
	float Rntc = temp_GET_R();
	N1 = (myln(R25)-myln(Rntc))/B;
	N2 = 1/T25 - N1;
	N3 = 1/N2;
	N4 = N3-273.15f;
	
	return N4;
}
uint16_t Temperature_protection=0;//温度保护参数
void Temp_read(void)
{
	static char str[]="00";
	float temp;
	int aa,bb,cc;
	if(temp_time>=500)
	{
		temp_time=0;
		temp=Get_Kelvin_Temperature();
		aa=(int)(temp*10+5)/10;
		bb=aa/10;
		cc=aa%10;
		
		sprintf(str,"%d%d",bb,cc);
		Temp_display(str);
		
		if(temp>=75&&temp<90)Temperature_protection=temp*1;
		else if(temp>=90)Temperature_protection=4095;
		else if(temp<75)Temperature_protection=0;
	}
}
