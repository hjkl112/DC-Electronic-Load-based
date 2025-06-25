#include "fan_speed.h"
#include "tim.h"
#include "lv_obj_my.h"
#include "usart.h"
extern uint16_t capture_speed;
extern uint16_t capture_speed_time;
void Fan_speed_init(void)
{
	HAL_TIM_IC_Start_IT(&htim8, TIM_CHANNEL_4); 
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,139);

}

void Fan_speed_read(void)
{
	static uint16_t fan_speed=0;
	static char str[]="0000";
	uint16_t a,b,c,d;
	if(capture_speed_time>=1000)
	{
		capture_speed_time=0;
		fan_speed=capture_speed*13;
//		Usart1Printf("%d\r\n",capture_speed);
		capture_speed=0;
		
		a=fan_speed/1000;
		b=fan_speed/100%10;
		c=fan_speed/10%10;
		d=fan_speed%10;
		
		str[0]=(char)('0'+a);
		str[1]=(char)('0'+b);
		str[2]=(char)('0'+c);
		str[3]=(char)('0'+d);
		
		FAN_speed_display(str);
	}
}



