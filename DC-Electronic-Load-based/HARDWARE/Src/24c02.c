#include "24c02.h"
#include "stm32f4xx.h"
#include "i2c.h"
#include "stdint.h"
#include "usart.h"
#define ADDR_24LCxx_Write 0xA0
#define ADDR_24LCxx_Read 0xA1
#define BufferSize 8
uint8_t WriteBuffer[BufferSize],ReadBuffer[BufferSize];


void AT24CXX_WriteByte(void)
{
	for(uint16_t i=0;i<1;i++)//i具体看需要保存的数据量
	{
		HAL_I2C_Mem_Write(&hi2c2,ADDR_24LCxx_Write,8*i,I2C_MEMADD_SIZE_8BIT,WriteBuffer+8*i,8,1000);
		HAL_Delay(20);
	}
}

void AT24CXX_ReadByte(void)
{
	HAL_I2C_Mem_Read(&hi2c2,ADDR_24LCxx_Read,0,I2C_MEMADD_SIZE_8BIT,ReadBuffer,BufferSize,0XFF);
	for(uint16_t i=0;i<8;i++)
	{
		Usart1Printf("%d\r\n",ReadBuffer[i]);
		HAL_Delay(1000);
	}
}
