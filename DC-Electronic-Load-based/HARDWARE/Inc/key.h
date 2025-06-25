#ifndef __KEY_H__
#define __KEY_H__
#include "main.h"
void KEY_Scan(void);
void KEY_setup(void);
void KEY_Exit_setup(uint8_t en,uint8_t x);
void KEY_sweep(void);//所有的按键循环函数
void KEY_short_electric(uint8_t en);//电流设置短按函数
void KEY_long_electric(uint8_t en);//电流设置长按函数
#endif


