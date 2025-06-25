#include "MCP4725.h"
#include "i2c.h"
#include "usart.h"
void MCP4725_WriteData_Volatge(uint16_t Vout)
{
	uint8_t data_h=0,data_l=0;
	data_h=(0x0f00&Vout)>>8; //传输数据高四位
	data_l = (0x00ff&Vout);//传输数据低八位
	uint8_t reg_data[2]={data_h,data_l};
	while(HAL_I2C_Master_Transmit(&hi2c1, 0xc0, reg_data, 2, 1000) != HAL_OK)
	{
			if(HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
			{
					Usart1Printf("ads1115 Config Register error!!!\r\n");
			}
	}
}
