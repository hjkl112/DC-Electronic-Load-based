#include "lv_obj_my.h"
#include "lvgl.h"
#include "usart.h"
#include "stdio.h"
#include "encoder.h"
#include "w25qxx.h"
#include "rtc_time.h"
LV_IMG_DECLARE(Image);
LV_FONT_DECLARE(my_font_icon_30);
LV_FONT_DECLARE(my_font_icon_16);
LV_FONT_DECLARE(my_font_heiti_22);
LV_FONT_DECLARE(my_font_heiti_16);


extern uint8_t mode;
void Background_display(void)
{
	lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(img1, &Image);
  lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, 0);
}

//定义图标,因为 littleVGL 只接受 utf-8 编码
//所以我们得通过工具把图标的 unicode 编码转化成 utf-8 编码
#define MY_ICON_TEMP "\xEE\x98\x91"
#define MY_ICON_ELE "\xEE\x99\xA5"
#define MY_ICON_VOL "\xEE\x99\xA6"
#define MY_ICON_POWER "\xEE\x99\xA8"
#define MY_ICON_TIME "\xEE\xA2\xA9"
#define MY_ICON_FAN "\xEE\x98\x88"
#define MY_ICON_BAT "\xEE\x98\xAB"


void Icon_display(void)
{
	lv_obj_t* scr = lv_scr_act();
	lv_obj_t* label1 = lv_label_create(scr,NULL);
	lv_obj_t* label2 = lv_label_create(scr,NULL);
	lv_obj_t* label3 = lv_label_create(scr,NULL);
	lv_obj_t* label5 = lv_label_create(scr,NULL);
	lv_obj_t* label6 = lv_label_create(scr,NULL);
	static lv_style_t style1;
	static lv_style_t style2;
	
	lv_style_copy(&style1,&lv_style_plain_color);
	style1.text.font = &my_font_icon_30;//使用图标字体
	lv_label_set_style(label1,LV_LABEL_STYLE_MAIN,&style1);//设置样式
	lv_label_set_text(label1,MY_ICON_TEMP);//设置文本
	lv_obj_align(label1,NULL,LV_ALIGN_IN_TOP_LEFT,235,30);
	
	lv_label_set_style(label2,LV_LABEL_STYLE_MAIN,&style1);//设置样式
	lv_label_set_text(label2,MY_ICON_ELE);//设置文本
	lv_obj_align(label2,NULL,LV_ALIGN_IN_TOP_LEFT,67,70);
	
	lv_label_set_style(label3,LV_LABEL_STYLE_MAIN,&style1);//设置样式
	lv_label_set_text(label3,MY_ICON_VOL);//设置文本
	lv_obj_align(label3,NULL,LV_ALIGN_IN_TOP_LEFT,221,70);	
	
	lv_label_set_style(label5,LV_LABEL_STYLE_MAIN,&style1);//设置样式
	lv_label_set_text(label5,MY_ICON_TIME);//设置文本
	lv_obj_align(label5,NULL,LV_ALIGN_IN_TOP_LEFT,221,155);		
	
	lv_style_copy(&style2,&lv_style_plain_color);
	style2.text.font = &my_font_icon_16;//使用图标字体
	lv_label_set_style(label6,LV_LABEL_STYLE_MAIN,&style2);//设置样式
	lv_label_set_text(label6,MY_ICON_FAN);//设置文本
	lv_obj_align(label6,NULL,LV_ALIGN_IN_TOP_LEFT,225,0);	
}


void Mode_Obj_set(void)
{
	
	lv_obj_t * obj5;
	static lv_style_t my_style1;
	
	lv_style_copy(&my_style1,&lv_style_plain_color);
	my_style1.body.main_color = LV_COLOR_BLACK;
	my_style1.body.grad_color = LV_COLOR_BLACK;
	my_style1.body.opa = 130;//设置透明度
	
	obj5 = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(obj5, 320, 22);
	lv_obj_set_style(obj5, &my_style1);
	lv_obj_align(obj5, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);	
	
}
void TEXT_display(void)
{
	static lv_style_t label_style;
	static lv_style_t label_style1;
	static lv_style_t label_style2;
	
	lv_obj_t* scr = lv_scr_act();
	lv_obj_t* label1 = lv_label_create(scr,NULL);
	lv_obj_t* label2 = lv_label_create(scr,NULL);
	lv_obj_t* label3 = lv_label_create(scr,NULL);
	lv_obj_t* label5 = lv_label_create(scr,NULL);
	
	lv_style_copy(&label_style,&lv_style_plain_color);//样式拷贝
	label_style.text.font = &lv_font_roboto_28;//设置字体
	
	lv_label_set_style(label1,LV_LABEL_STYLE_MAIN,&label_style);//给标签对象设置样式
	lv_label_set_text(label1,"A");//设置文本
	lv_obj_align(label1,NULL,LV_ALIGN_IN_TOP_LEFT,125,110);		
	
	lv_label_set_style(label2,LV_LABEL_STYLE_MAIN,&label_style);//给标签对象设置样式
	lv_label_set_text(label2,"V");//设置文本
	lv_obj_align(label2,NULL,LV_ALIGN_IN_TOP_LEFT,280,110);			
	
	lv_style_copy(&label_style1,&lv_style_plain_color);
	label_style1.text.font = &my_font_heiti_22;//在样式中使用这个字体
	
	lv_label_set_style(label5,LV_LABEL_STYLE_MAIN,&label_style1);
	lv_label_set_text(label5," ℃ ");//设置文本
	lv_obj_align(label5,NULL,LV_ALIGN_IN_TOP_LEFT,290,37);
	
	lv_style_copy(&label_style2,&lv_style_plain_color);
	label_style2.text.font = &lv_font_roboto_16;//在样式中使用这个字体	
	
	lv_label_set_style(label3,LV_LABEL_STYLE_MAIN,&label_style2);
	lv_label_set_text(label3,"RPM");//设置文本
	lv_obj_align(label3,NULL,LV_ALIGN_IN_TOP_RIGHT,0,0);	
	
}

//lv_font_conv --no-compress --format lvgl --font C:\Users\Administrator\Desktop\heiti.ttf -o C:\Users\Administrator\Desktop\my_font_heiti_22.c --bpp 4 --size 22 --symbols 电流设定:,功率设定:,设置,恒流模式,恒功率模式,电池容量测试,℃
//lv_font_conv --no-compress --format lvgl --font C:\Users\Administrator\Desktop\iconfont.ttf -o C:\Users\Administrator\Desktop\my_font_icon_30.c --bpp 4 --size 30 –r 0xe608,0xe8a9,0xe611,0xe665,0xe666,0xe668,0xe62b


static lv_obj_t* label_electric;
void Current_setting_display_init(void)
{
	static lv_style_t label_style;
	label_electric=lv_label_create(lv_scr_act(),NULL);
	lv_style_copy(&label_style,&lv_style_plain_color);
	label_style.text.font = &lv_font_roboto_22;//在样式中使用这个字体	
	
	lv_label_set_style(label_electric,LV_LABEL_STYLE_MAIN,&label_style);
	lv_obj_align(label_electric,NULL,LV_ALIGN_IN_TOP_LEFT,111,37);	
	
}
void Current_setting_display(char *str)
{
	char * num=str;
	lv_label_set_text(label_electric,num);//设置电流文本
}



static lv_obj_t* label_Select;
static lv_style_t style_Select;
void Select_area_flashing_init(void)
{
	
	lv_style_copy(&style_Select,&lv_style_plain_color);
	style_Select.body.main_color = LV_COLOR_GRAY;
	style_Select.body.grad_color = LV_COLOR_GRAY;
	style_Select.body.opa = 0;//设置透明度
	
	label_Select = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(label_Select, 10, 24);
	lv_obj_set_style(label_Select, &style_Select);
	lv_obj_move_foreground(label_Select);
}
void Select_area_flashing(uint8_t x)
{
	int16_t x_set;
	if(x==1)
	{
		x_set=112;
		style_Select.body.opa = 255;
	}
	else if(x==2)x_set=124;
	else if(x==3)x_set=142;
	else if(x==4)x_set=154;
	
	lv_obj_align(label_Select, NULL, LV_ALIGN_IN_TOP_LEFT, x_set, 36);//112  124  142  154
	
	
	if(x==5)style_Select.body.opa = 0;
}

static lv_obj_t * obj_display;
static lv_style_t style_display;
void ON_OR_OFF_Display_Init(void)
{
	
	lv_style_copy(&style_display,&lv_style_plain_color);
	style_display.body.main_color = LV_COLOR_RED;
	style_display.body.grad_color = LV_COLOR_RED;
	style_display.body.opa = 160;//设置透明度
	style_display.body.radius = 10;//设置圆角半径	
	
	obj_display = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(obj_display, 64, 24);
	lv_obj_set_style(obj_display, &style_display);
	lv_obj_align(obj_display, NULL, LV_ALIGN_IN_TOP_LEFT, 106,36);		
}

void ON_OR_OFF_Display(void)
{
	static uint8_t i=0;
	i=!i;
	if(i)
	{
		style_display.body.main_color = LV_COLOR_GREEN;
		style_display.body.grad_color = LV_COLOR_GREEN;
		lv_obj_refresh_style(obj_display);
	}
	else
	{
		style_display.body.main_color = LV_COLOR_RED;
		style_display.body.grad_color = LV_COLOR_RED;
		lv_obj_refresh_style(obj_display);
	}
}

static lv_obj_t* labe_temp;
void Temp_display_init(void)
{
	static lv_style_t label_style2;	
	
	labe_temp= lv_label_create(lv_scr_act(),NULL);
	lv_style_copy(&label_style2,&lv_style_plain_color);
	label_style2.text.font = &lv_font_roboto_22;//在样式中使用这个字体	
	
	lv_label_set_style(labe_temp,LV_LABEL_STYLE_MAIN,&label_style2);
	lv_label_set_text(labe_temp,"00");
	lv_obj_align(labe_temp,NULL,LV_ALIGN_IN_TOP_LEFT,263,37);		
}
void Temp_display(char *str)
{
	char *num=str;
	lv_label_set_text(labe_temp,num);//设置温度文本
}



static lv_obj_t* current_text;
void Current_display_init(void)
{
	static lv_style_t label_style1;	
	
	current_text= lv_label_create(lv_scr_act(),NULL);
	lv_style_copy(&label_style1,&lv_style_plain_color);
	label_style1.text.font = &lv_font_roboto_28;//在样式中使用这个字体		
	
	lv_label_set_style(current_text,LV_LABEL_STYLE_MAIN,&label_style1);
	lv_label_set_text(current_text,"00.00");
	lv_obj_align(current_text,NULL,LV_ALIGN_IN_TOP_LEFT,45,110);			
	
}
void Current_display(char *str)
{
	char *num=str;
	lv_label_set_text(current_text,num);
}


static lv_obj_t* voltaget_text;
void voltage_display_init(void)
{
	static lv_style_t label_style1;	
	
	voltaget_text= lv_label_create(lv_scr_act(),NULL);
	lv_style_copy(&label_style1,&lv_style_plain_color);
	label_style1.text.font = &lv_font_roboto_28;//在样式中使用这个字体		
	
	lv_label_set_style(voltaget_text,LV_LABEL_STYLE_MAIN,&label_style1);
	lv_label_set_text(voltaget_text,"00.00");
	lv_obj_align(voltaget_text,NULL,LV_ALIGN_IN_TOP_LEFT,200,110);		
}
void voltage_display(char *str)
{
	char *num=str;
	lv_label_set_text(voltaget_text,num);	
}


static lv_obj_t* power_text;
void power_display_init(void)
{
	static lv_style_t label_style1;	
	
	power_text= lv_label_create(lv_scr_act(),NULL);
	lv_style_copy(&label_style1,&lv_style_plain_color);
	label_style1.text.font = &lv_font_roboto_28;//在样式中使用这个字体		
	
	lv_label_set_style(power_text,LV_LABEL_STYLE_MAIN,&label_style1);
	lv_label_set_text(power_text,"00.00");
	lv_obj_align(power_text,NULL,LV_ALIGN_IN_TOP_LEFT,45,195);			
}
void power_display(char *str)
{
	char *num=str;
	lv_label_set_text(power_text,num);		
}


static lv_obj_t* run_time;
void Run_Time_Init(void)
{
	static lv_style_t label_style1;	
	
	run_time= lv_label_create(lv_scr_act(),NULL);
	lv_style_copy(&label_style1,&lv_style_plain_color);
	label_style1.text.font = &lv_font_roboto_28;//在样式中使用这个字体		
	
	lv_label_set_style(run_time,LV_LABEL_STYLE_MAIN,&label_style1);
	lv_label_set_text(run_time,"00:00:00");
	lv_obj_align(run_time,NULL,LV_ALIGN_IN_TOP_LEFT,183,195);			
}
void Run_Time(char *str)
{
	char *num=str;
	lv_label_set_text(run_time,num);		
}

static lv_obj_t* Set_menu;
void Set_menu_init(void)
{
	static lv_style_t label_style1;
	Set_menu= lv_obj_create(lv_scr_act(),NULL);
	lv_style_copy(&label_style1,&lv_style_plain_color);
	label_style1.body.main_color = LV_COLOR_PURPLE;
	label_style1.body.grad_color = LV_COLOR_PURPLE;
	
	lv_obj_set_size(Set_menu, 300, 160);
	lv_obj_set_style(Set_menu, &label_style1);
	lv_obj_align(Set_menu, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 70);		
}
static lv_obj_t* Set_menu_text;
static lv_obj_t* Set_menu_text1;
static lv_obj_t* Set_menu_text2;
static lv_obj_t* Set_menu_text3;
void Set_menu_Text_init(void)
{
	static lv_style_t label_style1;
	static lv_style_t label_style2;
	Set_menu_text = lv_label_create(lv_scr_act(),NULL);
	Set_menu_text1 = lv_label_create(lv_scr_act(),NULL);
	Set_menu_text2 = lv_label_create(lv_scr_act(),NULL);
	Set_menu_text3 = lv_label_create(lv_scr_act(),NULL);
	
	lv_style_copy(&label_style1,&lv_style_plain_color);
	label_style1.text.font = &my_font_heiti_22;//在样式中使用这个字体		
	
	lv_style_copy(&label_style2,&lv_style_plain_color);
	label_style2.text.font = &my_font_heiti_16;//在样式中使用这个字体			
	
	lv_label_set_style(Set_menu_text,LV_LABEL_STYLE_MAIN,&label_style2);
	lv_label_set_text(Set_menu_text,"设置");
	lv_obj_align(Set_menu_text,NULL,LV_ALIGN_IN_TOP_MID,0,75);		
	
	lv_label_set_style(Set_menu_text1,LV_LABEL_STYLE_MAIN,&label_style1);
	lv_label_set_text(Set_menu_text1,"恒流模式");
	lv_obj_align(Set_menu_text1,NULL,LV_ALIGN_IN_TOP_LEFT,20,115);		

	lv_label_set_style(Set_menu_text2,LV_LABEL_STYLE_MAIN,&label_style1);
	lv_label_set_text(Set_menu_text2,"恒功率模式");
	lv_obj_align(Set_menu_text2,NULL,LV_ALIGN_IN_TOP_LEFT,20,155);		
	
	lv_label_set_style(Set_menu_text3,LV_LABEL_STYLE_MAIN,&label_style1);
	lv_label_set_text(Set_menu_text3,"电池容量测试");
	lv_obj_align(Set_menu_text3,NULL,LV_ALIGN_IN_TOP_LEFT,20,195);		
}

static lv_obj_t* Set_menu_line;
static lv_obj_t* Set_menu_line1;
static lv_obj_t* Set_menu_line2;
static lv_obj_t* Set_menu_line3;
void Set_menu_Line_init(void)
{
	static lv_style_t line_style1;
	static lv_point_t line_points[] = {{20, 105},{299, 105}};
	static lv_point_t line_points1[] = {{20, 145},{299, 145}};
	static lv_point_t line_points2[] = {{20, 185},{299, 185}};
	static lv_point_t line_points3[] = {{20, 226},{299, 226}};
	
	lv_style_copy(&line_style1,&lv_style_plain);
	line_style1.line.color=LV_COLOR_WHITE;
	line_style1.line.width=1;
	line_style1.line.rounded = 0;//线条的末端是否为圆角
	line_style1.line.opa=100;
	
	Set_menu_line= lv_line_create(lv_scr_act(), NULL);//创建线条对象
	lv_line_set_points(Set_menu_line, line_points, 2);
	lv_line_set_style(Set_menu_line, LV_LINE_STYLE_MAIN, &line_style1);//设置样式	
	lv_obj_align(Set_menu_line, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	
	Set_menu_line1= lv_line_create(lv_scr_act(), NULL);//创建线条对象
	lv_line_set_points(Set_menu_line1, line_points1, 2);
	lv_line_set_style(Set_menu_line1, LV_LINE_STYLE_MAIN, &line_style1);//设置样式	
	lv_obj_align(Set_menu_line1, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);	
	
	Set_menu_line2= lv_line_create(lv_scr_act(), NULL);//创建线条对象
	lv_line_set_points(Set_menu_line2, line_points2, 2);
	lv_line_set_style(Set_menu_line2, LV_LINE_STYLE_MAIN, &line_style1);//设置样式	
	lv_obj_align(Set_menu_line2, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);		
	
	Set_menu_line3= lv_line_create(lv_scr_act(), NULL);//创建线条对象
	lv_line_set_points(Set_menu_line3, line_points3, 2);
	lv_line_set_style(Set_menu_line3, LV_LINE_STYLE_MAIN, &line_style1);//设置样式	
	lv_obj_align(Set_menu_line3, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);		
}

static lv_obj_t* obj_select;
void select_setup_init(void)
{
	static lv_style_t line_style1;
	obj_select= lv_obj_create(lv_scr_act(),NULL);
	lv_style_copy(&line_style1,&lv_style_plain_color);
	line_style1.body.main_color = LV_COLOR_ORANGE;
	line_style1.body.grad_color = LV_COLOR_ORANGE;	
	
	lv_obj_set_size(obj_select, 300, 40);
	lv_obj_set_style(obj_select, &line_style1);
	lv_obj_align(obj_select, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 105);			
}
void select_setup(int x)
{
	int16_t y_con;
	if(x==1)y_con=105;
	else if(x==2)y_con=145;
	else if(x==3)y_con=185;
	lv_obj_align(obj_select, NULL, LV_ALIGN_IN_TOP_LEFT, 10, y_con);
}



void Exit_setup(void)
{
	lv_obj_del(Set_menu_text);
	lv_obj_del(Set_menu_text1);
	lv_obj_del(Set_menu_text2);
	lv_obj_del(Set_menu_text3);
	lv_obj_del(Set_menu_line);
	lv_obj_del(Set_menu_line1);
	lv_obj_del(Set_menu_line2);
	lv_obj_del(Set_menu_line3);
	lv_obj_del(Set_menu);
	lv_obj_del(obj_select);
}


static lv_obj_t* label_mode;
void Mode_display_init(void)
{
	static lv_style_t label_style3;
	label_mode= lv_label_create(lv_scr_act(),NULL);
	
	lv_style_copy(&label_style3,&lv_style_plain_color);
	label_style3.text.font = &my_font_heiti_16;//在样式中使用这个字体	
	
	lv_label_set_style(label_mode,LV_LABEL_STYLE_MAIN,&label_style3);
	lv_label_set_text(label_mode,"恒流模式");//设置文本
	lv_obj_align(label_mode,NULL,LV_ALIGN_IN_TOP_LEFT,128,0);	
}
void Mode_display(void)
{
	if(mode==1)
	{
		lv_label_set_text(label_mode,"恒流模式");//设置文本
		lv_obj_align(label_mode,NULL,LV_ALIGN_IN_TOP_LEFT,128,0);	
	}
	else if(mode==2)
	{
		lv_label_set_text(label_mode,"恒功率模式");//设置文本
		lv_obj_align(label_mode,NULL,LV_ALIGN_IN_TOP_LEFT,120,0);	
	}
	else if(mode==3)
	{
		lv_label_set_text(label_mode,"电池容量测试");//设置文本
		lv_obj_align(label_mode,NULL,LV_ALIGN_IN_TOP_LEFT,112,0);	
	}
}

static lv_obj_t* label_set;
void Set_display_init(void)
{
	static lv_style_t label_style3;
	label_set=lv_label_create(lv_scr_act(),NULL);
	
	lv_style_copy(&label_style3,&lv_style_plain_color);
	label_style3.text.font = &my_font_heiti_22;//在样式中使用这个字体
	
	lv_label_set_style(label_set,LV_LABEL_STYLE_MAIN,&label_style3);
	lv_label_set_text(label_set,"电流设定:");//设置文本
	lv_obj_align(label_set,NULL,LV_ALIGN_IN_TOP_LEFT,10,37);	
}
void Set_display(void)
{
	if(mode==1)lv_label_set_text(label_set,"电流设定:");//设置文本
	else if(mode==2)lv_label_set_text(label_set,"功率设定:");//设置文本
	else if(mode==3)lv_label_set_text(label_set,"电流设定:");//设置文本
}


static lv_obj_t * obj_frame_1;
static lv_obj_t * obj_frame_2;
static lv_obj_t * obj_frame_3;
static lv_obj_t * obj_frame_4;
static lv_style_t style_frame;
void Mode_obj_display_init(void)
{
	lv_style_copy(&style_frame,&lv_style_plain_color);
	style_frame.body.main_color = LV_COLOR_RED;
	style_frame.body.grad_color = LV_COLOR_RED;
	style_frame.body.opa = 160;//设置透明度
	style_frame.body.radius = 10;//设置圆角半径
	
	obj_frame_1 = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(obj_frame_1, 145, 75);
	lv_obj_set_style(obj_frame_1, &style_frame);
	lv_obj_align(obj_frame_1, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 70);
	
	obj_frame_2 = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(obj_frame_2, 145, 75);
	lv_obj_set_style(obj_frame_2, &style_frame);
	lv_obj_align(obj_frame_2, NULL, LV_ALIGN_IN_TOP_LEFT, 165, 70);
	
	obj_frame_3 = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(obj_frame_3, 145, 75);
	lv_obj_set_style(obj_frame_3, &style_frame);
	lv_obj_align(obj_frame_3, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 155);
	
	obj_frame_4 = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(obj_frame_4, 145, 75);
	lv_obj_set_style(obj_frame_4, &style_frame);
	lv_obj_align(obj_frame_4, NULL, LV_ALIGN_IN_TOP_LEFT, 165, 155);		
}
void Mode_obj_display(void)
{
	if(mode==1)
	{
		style_frame.body.main_color = LV_COLOR_RED;
		style_frame.body.grad_color = LV_COLOR_RED;
	}
	else if(mode==2)
	{
		style_frame.body.main_color = LV_COLOR_BLUE;
		style_frame.body.grad_color = LV_COLOR_BLUE;
	}
	else if(mode==3)
	{
		style_frame.body.main_color = LV_COLOR_GREEN;
		style_frame.body.grad_color = LV_COLOR_GREEN;
	}
	lv_obj_refresh_style(obj_frame_1);
	lv_obj_refresh_style(obj_frame_2);
	lv_obj_refresh_style(obj_frame_3);
	lv_obj_refresh_style(obj_frame_4);
}
void Mode_switch_display(void)
{
  uint8_t send_data[1]={0};
	static uint8_t mode_old;
	if(mode!=mode_old)
	{
		Mode_obj_display();
		Set_display();
		Mode_display();
		Unit_switching();
		Power_or_Bat_display();
		send_data[0]=mode;
		W25QXX_Write(send_data,5,1);
	}
}

uint8_t currents1[4];//恒流模式下的电流设定
uint8_t currents2[4];//电池容量测试下的电流设定
uint8_t power[4];//功率设定

void Init_display_mode(void)
{
	uint8_t rend_data[1]={0};
	static char str[]="00.00";
	
	W25QXX_Read(rend_data,5,1);
	mode=rend_data[0];
	W25QXX_Read(currents1,0,4);
	W25QXX_Read(power,7,4);
	W25QXX_Read(currents2,11,4);
	
	Mode_obj_display();
	Set_display();
	Mode_display();
	Unit_switching();
	Power_or_Bat_display();
	
	if(mode==1)
		sprintf(str,"%d%d.%d%d",currents1[0],currents1[1],currents1[2],currents1[3]);
	else if(mode==2)
		sprintf(str,"%d%d.%d%d",power[0],power[1],power[2],power[3]);
	else if(mode==3)
		sprintf(str,"%d%d.%d%d",currents2[0],currents2[1],currents2[2],currents2[3]);	
//	Usart1Printf("%s\r\n",str);
	Current_setting_display(str);
}

static lv_obj_t* label_unit;
static lv_obj_t* label_unit_1;
void Unit_switching_init(void)
{
	static lv_style_t label_style;
	label_unit= lv_label_create(lv_scr_act(),NULL);
	label_unit_1= lv_label_create(lv_scr_act(),NULL);
	
	lv_style_copy(&label_style,&lv_style_plain_color);//样式拷贝
	label_style.text.font = &lv_font_roboto_28;//设置字体
	
	lv_label_set_style(label_unit,LV_LABEL_STYLE_MAIN,&label_style);//给标签对象设置样式
	lv_label_set_text(label_unit,"A");//设置文本
	lv_obj_align(label_unit,NULL,LV_ALIGN_IN_TOP_LEFT,172,34);		
	
	lv_label_set_style(label_unit_1,LV_LABEL_STYLE_MAIN,&label_style);//给标签对象设置样式
	lv_label_set_text(label_unit_1,"W");//设置文本
	lv_obj_align(label_unit_1,NULL,LV_ALIGN_IN_TOP_LEFT,122,195);			
}
void Unit_switching(void)
{
	if(mode==1)
	{
		lv_label_set_text(label_unit_1,"W");//设置文本
		lv_label_set_text(label_unit,"A");//设置文本
	}
	else if(mode==2)
	{
		lv_label_set_text(label_unit,"W");//设置文本
		lv_label_set_text(label_unit_1,"W");//设置文本
	}
	else if(mode==3)
	{
		lv_label_set_text(label_unit,"A");//设置文本
		lv_label_set_text(label_unit_1,"Ah");//设置文本
	}
}

static lv_obj_t* label_fan;
void FAN_speed_display_init(void)
{
	static lv_style_t label_style;
	label_fan= lv_label_create(lv_scr_act(),NULL);
	
	lv_style_copy(&label_style,&lv_style_plain_color);//样式拷贝
	label_style.text.font = &lv_font_roboto_16;//设置字体	

	lv_label_set_style(label_fan,LV_LABEL_STYLE_MAIN,&label_style);//给标签对象设置样式
	lv_label_set_text(label_fan,"0000");//设置文本
	lv_obj_align(label_fan,NULL,LV_ALIGN_IN_TOP_LEFT,246,0);		
}

void FAN_speed_display(char *str)
{
	lv_label_set_text(label_fan,str);//设置文本
}
static lv_obj_t* label_power_or_bat;
void Power_or_Bat_display_init(void)
{
	static lv_style_t label_style;
	
	label_power_or_bat=lv_label_create(lv_scr_act(),NULL);

	lv_style_copy(&label_style,&lv_style_plain_color);
	label_style.text.font = &my_font_icon_30;//使用图标字体
	lv_label_set_style(label_power_or_bat,LV_LABEL_STYLE_MAIN,&label_style);//设置样式
	
	lv_obj_align(label_power_or_bat,NULL,LV_ALIGN_IN_TOP_LEFT,67,155);		
}
void Power_or_Bat_display(void)
{
	if(mode==1||mode==2) lv_label_set_text(label_power_or_bat,MY_ICON_POWER);//设置文本
	else lv_label_set_text(label_power_or_bat,MY_ICON_BAT);//	
}
void Switch_mode_clearing(void)
{
	char str[]="00.00";
	char sta[]="00:00:00";
	Time_clear();
	power_display(str);
	Run_Time(sta);
}






