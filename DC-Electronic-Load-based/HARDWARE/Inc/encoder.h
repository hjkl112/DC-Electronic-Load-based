#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "main.h"
#include "tim.h"

void ENCODER_Init(void);
void encoder_read(void);
void encoder_setup_mode_selection(uint8_t en);//编码器在模式选择


void electric_setup(uint8_t en);//编码器在电流设置模式
void power_setup(uint8_t en);//编码器在功率设置模式
void battery_setup(uint8_t en);//编码器在电池容量测试模式
#endif

