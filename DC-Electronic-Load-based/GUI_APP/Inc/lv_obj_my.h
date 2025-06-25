#ifndef __LV_OBJ_MY_H
#define __LV_OBJ_MY_H
#include "main.h"



void Background_display(void);//背景显示
void Icon_display(void);//图标显示
void Mode_Obj_set(void);//模式显示背景
void TEXT_display(void);
void Current_setting_display(char *str);//电流设定显示  Num:要显示的数据；i:要显示的位数
void Current_setting_display_init(void);//电流设定显示初始化
void Select_area_flashing(uint8_t x);//设置电流设定各位数值时背景的显示
void Select_area_flashing_init(void);//设置电流设定各位数值时背景的显示的初始化
void ON_OR_OFF_Display(void);//开启和关闭时，电流设定背景的切换函数
void ON_OR_OFF_Display_Init(void);//初始化电流设定背景
void Temp_display(char *str);//设置温度显示数值
void Temp_display_init(void);//温度显示数值初始化
void Current_display(char *str);//电流显示
void Current_display_init(void);//电流显示文本初始化
void voltage_display(char *str);//电压显示
void voltage_display_init(void);//电压显示文本初始化
void power_display(char *str);//功率显示
void power_display_init(void);//功率显示文本初始化
void Run_Time(char *str);//运行时间显示
void Run_Time_Init(void);//运行时间文本初始化
void Set_menu_init(void);//设置菜单背景初始化
void Set_menu_Text_init(void);//设置字体初始化
void Set_menu_Line_init(void);//设置分隔线条初始化
void Exit_setup(void);//退出设置界面
void select_setup_init(void);//选择功能背景显示的初始化
void select_setup(int x);//选择功能的高亮位置变更
void Mode_display_init(void);//模式显示
void Mode_display(void);//模式显示选择
void Set_display_init(void);//电流设定、功率设定初始化
void Set_display(void);//电流设定、功率设定
void Mode_obj_display(void);//模式背景颜色切换
void Mode_obj_display_init(void);//模式背景颜色切换初始化
void Mode_switch_display(void);//模式切换时背景的更换
void Init_display_mode(void);//上电读取模式数据
void Unit_switching_init(void);//电流和功率的单位切换初始化
void Unit_switching(void);//电流和功率的单位切换
void FAN_speed_display_init(void);//风扇转速显示初始化
void FAN_speed_display(char *str);//风扇转速显示
void Power_or_Bat_display_init(void);//功率图标或电池图标显示初始化
void Power_or_Bat_display(void);//功率图标或电池图标显示
void Switch_mode_clearing(void);//切换模式后将时间和容量值清零
#endif
