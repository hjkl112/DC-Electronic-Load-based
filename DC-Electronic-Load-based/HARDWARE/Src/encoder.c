#include "encoder.h"
#include "tim.h"
#include "usart.h"
#include "lv_obj_my.h"
#include "key.h"
#include "w25qxx.h"
#include "stdio.h"
#include "MCP4725.h"
#include "PID.h"
extern uint8_t s_key;
extern uint8_t l_key;
extern uint8_t setup_en;
int CaptureNumber=0;//编码器转动次数
uint8_t setup_end=0;//当退出设置时，使CaptureNumber回到电流设置的原始数据
extern uint8_t mode;
void ENCODER_Init(void)
{
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_1 | TIM_CHANNEL_2);
}
void encoder_read(void)
{
	int Direction=0;//编码器旋转方向
	electric_setup(setup_en);
	power_setup(setup_en);
	battery_setup(setup_en);
	encoder_setup_mode_selection(setup_en);
	Direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3);   //��ȡ���ת������
	CaptureNumber =	(short)__HAL_TIM_GET_COUNTER(&htim3);	  //��ȡ����������
}

extern uint8_t mode_change;
void encoder_setup_mode_selection(uint8_t en)
{
	static uint8_t innebel=1;
	static int CaptureNumber_old;
	if(en==2)
	{
		if(innebel)
		{
			innebel=0;
			TIM3 -> CNT=mode;
			CaptureNumber=mode;
			select_setup(CaptureNumber);
			CaptureNumber_old=CaptureNumber;
			setup_end=1;
		}
		if(CaptureNumber<=0)
		{
			TIM3 -> CNT=3;
			CaptureNumber=3;
		}
		if(CaptureNumber>3)
		{
			TIM3 -> CNT=1;
			CaptureNumber=1;
		}		
		if(CaptureNumber!=CaptureNumber_old)
		{
			select_setup(CaptureNumber);
			CaptureNumber_old=CaptureNumber;
			mode=CaptureNumber;
		}
	}else	innebel=1;
//	if(mode_change)//当确定模式选择后，更新mode值，同时更新模式界面
//	{
//		mode_change=0;
//		mode=CaptureNumber;
//		Mode_switch_display();
//	}
}

extern uint8_t currents1[4];
extern float current_target;
extern float power_target;
void electric_setup(uint8_t en)
{
	static char str[]="00.00";
	static uint8_t i=0;
	static int CaptureNumber_old;
	static float divisor=100;//设置的电流  被除数
	if(en==1&&mode==1)//恒流模式和非菜单选择界面下
	{
		if(s_key)
		{
			s_key=0;
			i++;
			
			if(i==5)W25QXX_Write(currents1,0,4);
			if(i==6)i=1;
//			Usart1Printf("%d\r\n",i);
			Select_area_flashing(i);
			switch (i)
			{
				case 1:
					TIM3 -> CNT=currents1[0];
				break;
				case 2:
					TIM3 -> CNT=currents1[1];
				break;
				case 3:
					TIM3 -> CNT=currents1[2];
				break;
				case 4:
					TIM3 -> CNT=currents1[3];
				break;				
			}
		}
		
		if(l_key)//如果发生长按开始输出
		{
			l_key=0;
			i=5;
			W25QXX_Write(currents1,0,4);
			current_target=(currents1[0]*1000+currents1[1]*100+currents1[2]*10+currents1[3])/divisor;//计算得到设置的电流值

//			Usart1Printf("%f\r\n",current_target);
		}
		
		if(setup_end)//使数据从菜单选择的编码器数据，变为原来的电流数据 
		{
			setup_end=0;
			Select_area_flashing(5);
			switch (i)//按位更新之前保存的数据
			{
				case 1:		
					TIM3 -> CNT=currents1[0];
					CaptureNumber=currents1[0];
				break;
				case 2:		
					TIM3 -> CNT=currents1[1];
					CaptureNumber=currents1[1];
				break;
				case 3:		
					TIM3 -> CNT=currents1[2];
					CaptureNumber=currents1[2];
				break;			
				case 4:		
					TIM3 -> CNT=currents1[3];
					CaptureNumber=currents1[3];
				break;				
			}		
			sprintf(str,"%d%d.%d%d",currents1[0],currents1[1],currents1[2],currents1[3]);
//			Usart1Printf("%s\r\n",str);
			Current_setting_display(str);//重新显示原来的电流值
		}		
		
		//数据限幅	
			if(CaptureNumber<0)
			{
				TIM3 -> CNT=0;
				CaptureNumber=0;
			}
			if(CaptureNumber>9)
			{
				TIM3 -> CNT=9;
				CaptureNumber=9;
			}
		//数据限幅	
			
		if(CaptureNumber!=CaptureNumber_old)
		{
			switch (i)
			{
				case 1:
					if(CaptureNumber>1)
					{
						CaptureNumber=1;
						TIM3 -> CNT=1;
					}
					currents1[0]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",currents1[0],currents1[1],currents1[2],currents1[3]);
				break;
				case 2:
					if(currents1[0]==1)CaptureNumber=0;
					currents1[1]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",currents1[0],currents1[1],currents1[2],currents1[3]);
				break;
				case 3:
					if(currents1[0]==1)CaptureNumber=0;
					currents1[2]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",currents1[0],currents1[1],currents1[2],currents1[3]);
				break;
				case 4:
					if(currents1[0]==1)CaptureNumber=0;
					currents1[3]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",currents1[0],currents1[1],currents1[2],currents1[3]);
				break;				
			}
			if(currents1[0]==1)
			{
				currents1[1]=0;
				currents1[2]=0;
				currents1[3]=0;
				sprintf(str,"%d%d.%d%d",currents1[0],currents1[1],currents1[2],currents1[3]);
			}
			Current_setting_display(str);
			CaptureNumber_old=CaptureNumber;
		}
	}else i=0;
}

extern uint8_t power[4];
void power_setup(uint8_t en)
{
	static char str[]="00.00";
	static uint8_t i=0;
	static int CaptureNumber_old;
	static float divisor=100;//设置的功率  被除数
	if(en==1&&mode==2)//恒流模式和非菜单选择界面下
	{
		if(s_key)
		{
			s_key=0;
			i++;
			if(i==5)W25QXX_Write(power,7,4);
			if(i==6)i=1;
			Select_area_flashing(i);
			switch (i)
			{
				case 1:
					TIM3 -> CNT=power[0];
				break;
				case 2:
					TIM3 -> CNT=power[1];
				break;
				case 3:
					TIM3 -> CNT=power[2];
				break;
				case 4:
					TIM3 -> CNT=power[3];
				break;				
			}
		}
		
		if(l_key)//如果发生长按开始输出
		{
			l_key=0;
			i=5;
			W25QXX_Write(power,7,4);
			power_target=(power[0]*1000+power[1]*100+power[2]*10+power[3])/divisor;//计算得到设置的电流值
//			Usart1Printf("%f\r\n",current_value);
		}
		
		if(setup_end)//使数据从菜单选择的编码器数据，变为原来的电流数据 
		{
			setup_end=0;
			Select_area_flashing(5);
			switch (i)//按位更新之前保存的数据
			{
				case 1:		
					TIM3 -> CNT=power[0];
					CaptureNumber=power[0];
				break;
				case 2:		
					TIM3 -> CNT=power[1];
					CaptureNumber=power[1];
				break;
				case 3:		
					TIM3 -> CNT=power[2];
					CaptureNumber=power[2];
				break;			
				case 4:		
					TIM3 -> CNT=power[3];
					CaptureNumber=power[3];
				break;				
			}		
			sprintf(str,"%d%d.%d%d",power[0],power[1],power[2],power[3]);
			Current_setting_display(str);//重新显示原来的功率值
		}		
		
		//数据限幅	
			if(CaptureNumber<0)
			{
				TIM3 -> CNT=0;
				CaptureNumber=0;
			}
			if(CaptureNumber>9)
			{
				TIM3 -> CNT=9;
				CaptureNumber=9;
			}
		//数据限幅	
			
		if(CaptureNumber!=CaptureNumber_old)
		{
			switch (i)
			{
				case 1:
					power[0]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",power[0],power[1],power[2],power[3]);
				break;
				case 2:
					power[1]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",power[0],power[1],power[2],power[3]);
				break;
				case 3:
					power[2]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",power[0],power[1],power[2],power[3]);
				break;
				case 4:
					power[3]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",power[0],power[1],power[2],power[3]);
				break;				
			}
			Current_setting_display(str);
			CaptureNumber_old=CaptureNumber;
		}
	}else i=0;	
}

extern uint8_t currents2[4];
void battery_setup(uint8_t en)
{
	static char str[]="00.00";
	static uint8_t i=0;
	static int CaptureNumber_old;
	static float divisor=100;//设置的电流  被除数
	if(en==1&&mode==3)//恒流模式和非菜单选择界面下
	{
		if(s_key)
		{
			s_key=0;
			i++;
//			Usart1Printf("%d\r\n",i);
			if(i==5)W25QXX_Write(currents2,11,4);
			if(i==6)i=1;
			Select_area_flashing(i);
			switch (i)
			{
				case 1:
					TIM3 -> CNT=currents2[0];
				break;
				case 2:
					TIM3 -> CNT=currents2[1];
				break;
				case 3:
					TIM3 -> CNT=currents2[2];
				break;
				case 4:
					TIM3 -> CNT=currents2[3];
				break;				
			}
		}
		
		if(l_key)//如果发生长按开始输出
		{
			l_key=0;
			i=5;
			W25QXX_Write(currents2,11,4);
			current_target=(currents2[0]*1000+currents2[1]*100+currents2[2]*10+currents2[3])/divisor;//计算得到设置的电流值
//			Usart1Printf("%f\r\n",current_value);
		}
//		
		if(setup_end)//使数据从菜单选择的编码器数据，变为原来的电流数据 
		{
			setup_end=0;
			Select_area_flashing(5);
			switch (i)//按位更新之前保存的数据
			{
				case 1:		
					TIM3 -> CNT=currents2[0];
					CaptureNumber=currents2[0];
				break;
				case 2:		
					TIM3 -> CNT=currents2[1];
					CaptureNumber=currents2[1];
				break;
				case 3:		
					TIM3 -> CNT=currents2[2];
					CaptureNumber=currents2[2];
				break;			
				case 4:		
					TIM3 -> CNT=currents2[3];
					CaptureNumber=currents2[3];
				break;				
			}		
			sprintf(str,"%d%d.%d%d",currents2[0],currents2[1],currents2[2],currents2[3]);
			Current_setting_display(str);//重新显示原来的电流值
		}		
		
		//数据限幅	
			if(CaptureNumber<0)
			{
				TIM3 -> CNT=0;
				CaptureNumber=0;
			}
			if(CaptureNumber>9)
			{
				TIM3 -> CNT=9;
				CaptureNumber=9;
			}
		//数据限幅	
			
		if(CaptureNumber!=CaptureNumber_old)
		{
			switch (i)
			{
				case 1:
					if(CaptureNumber>1)
					{
						CaptureNumber=1;
						TIM3 -> CNT=1;
					}
					currents2[0]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",currents2[0],currents2[1],currents2[2],currents2[3]);
				break;
				case 2:
					if(currents2[0]==1)CaptureNumber=0;
					currents2[1]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",currents2[0],currents2[1],currents2[2],currents2[3]);
				break;
				case 3:
					if(currents2[0]==1)CaptureNumber=0;
					currents2[2]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",currents2[0],currents2[1],currents2[2],currents2[3]);
				break;
				case 4:
					if(currents2[0]==1)CaptureNumber=0;
					currents2[3]=CaptureNumber;
					sprintf(str,"%d%d.%d%d",currents2[0],currents2[1],currents2[2],currents2[3]);
				break;				
			}
			if(currents2[0]==1)
			{
				currents2[1]=0;
				currents2[2]=0;
				currents2[3]=0;
				sprintf(str,"%d%d.%d%d",currents2[0],currents2[1],currents2[2],currents2[3]);
			}
//			Usart1Printf("%s\r\n",str);
			Current_setting_display(str);
			CaptureNumber_old=CaptureNumber;
		}
	}else i=0;	
}




