#ifndef __ILI9341_H
#define __ILI9341_H		
#include "stm32f4xx_hal.h"	 

#define USE_HORIZONTAL 3 //���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 240
#define LCD_H 320

#else
#define LCD_W 320
#define LCD_H 240
#endif

// ��������
#define	LCD_LED_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
#define	LCD_LED_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);


//GPIO��λ�����ߣ�
#define	LCD_CS_SET  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);    //Ƭѡ�˿�  	
#define	LCD_RS_SET  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);    //����/����      
#define	LCD_RST_SET  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);    //��λ			  

//GPIO��λ�����ͣ�							    
#define	LCD_CS_CLR  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);    
#define	LCD_RS_CLR  	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);      
#define	LCD_RST_CLR  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET); 

  															  
void LCD_Init(void);
void LCD_WR_DATA8(uint8_t data);
void LCD_WR_REG(uint8_t data);
void LCD_RESET(void);
void LCD_WR_DATA(uint16_t dat);//д�������ֽ�
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);//�������꺯��
#endif  
