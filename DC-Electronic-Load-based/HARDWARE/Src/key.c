#include "key.h"
#include "gpio.h"
#include "usart.h"
#include "lv_obj_my.h"
#include "rtc_time.h"
extern unsigned long key_now_time;
extern uint8_t run_time_control;
uint8_t s_key=0,l_key=0;//按键长短按标志
uint8_t setup_en=1;//设置编码器在电流设置和菜单选择中切换
uint8_t s_key_en=1;//长按开始输出后，禁止短按的使用
uint8_t padlock=1;//长按开始输出后，禁止进入设置界面
uint8_t mode=1;//模式选择
void KEY_Scan(void)
{
	static unsigned char key_state = 0; 
 
	switch (key_state)
	{
		case 0:
			if(HAL_GPIO_ReadPin(KEY_OK_GPIO_Port,KEY_OK_Pin)==0)
			{
				key_state=1;
				key_now_time=0;
			}
		break;
		case 1:
			if(HAL_GPIO_ReadPin(KEY_OK_GPIO_Port,KEY_OK_Pin)==0)
			{
				if(key_now_time>10)key_state=2;
			}else key_state=0;
		break;
		case 2:
			if(HAL_GPIO_ReadPin(KEY_OK_GPIO_Port,KEY_OK_Pin)==1)
			{
				//单击
				KEY_short_electric(setup_en);
				KEY_Exit_setup(setup_en,1);
				
				key_state=0;
			}
			else
			{
				if(key_now_time>800)
				{
					//长按
					KEY_long_electric(setup_en);
					
					
					
					key_state=3;
				}
			}
		break;
		case 3:
		{
			if(HAL_GPIO_ReadPin(KEY_OK_GPIO_Port,KEY_OK_Pin)==1) key_state=0;
		}
		break;
		default:
			key_state=0;
		break;
	}
}
extern uint8_t set_key;
uint8_t set_en=1,quti_en=0;//防止按下按键时，重复执行设置界面的初始化和删除任务
void KEY_setup(void)
{
	if(padlock==1)
	{
		if(set_key)
		{
			set_key=0;
			if(set_en)
			{
				set_en=0;
				quti_en=1;
				setup_en=2;
				Set_menu_init();
				select_setup_init();
				Set_menu_Text_init();
				Set_menu_Line_init();			
				Switch_mode_clearing();
			}
		}
	}
}
extern uint8_t quit_key;
uint8_t mode_change=0;//模式切换标志
void KEY_Exit_setup(uint8_t en,uint8_t x)
{
	if(en==2)
	{
		if(quit_key||x)
		{
			quit_key=0;
			if(quti_en)
			{
				quti_en=0;
				set_en=1;
				setup_en=1;
				Exit_setup();
				if(x==1)mode_change=1;
//				Usart1Printf("%d\r\n",mode);
			}
		}
	}
	
}
void KEY_sweep(void)
{
	KEY_Scan();
	KEY_setup();
	KEY_Exit_setup(setup_en,0);
}
void KEY_short_electric(uint8_t en)
{
	if(en==1)
	{
		if(s_key_en)//当长按开始输出后，禁止显示电流设置的位数
		{
			s_key=1;
		}
	}
	else if(en==2)
	{
		Mode_switch_display();
	}
}
void KEY_long_electric(uint8_t en)
{
	if(en==1)
	{
		l_key=1;
		ON_OR_OFF_Display();//控制电流设置背景的改变
		run_time_control=!run_time_control;//控制运行时间是否显示
		Time_clear();//清空RTC计时
		s_key_en=!s_key_en;//长按开始输出后，禁止短按的使用
		Select_area_flashing(5);//清空位数选择		
		padlock=!padlock;
		HAL_GPIO_TogglePin(GPIOC, SYS_EN_Pin);
	}	
}
