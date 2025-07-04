#include "ADS1115.h"
#include "stm32f4xx.h"
#include "i2c.h"
#include "stdint.h"
#include "usart.h"
#include "lv_obj_my.h"
#include "stdio.h"
#include "MCP4725.h"
#include "PID.h"
void ads1115_config_register(I2C_HandleTypeDef ads1115_I2cHandle,uint8_t pointADD,uint8_t configH,uint8_t configL)
{
    uint8_t reg_data[3]={pointADD,configH,configL};
    while(HAL_I2C_Master_Transmit(&ads1115_I2cHandle, ADS1115_WRITE_ADDRESS, reg_data, 3, 1000) != HAL_OK)
    {
        if(HAL_I2C_GetError(&ads1115_I2cHandle) != HAL_I2C_ERROR_AF)
        {
            Usart1Printf("ads1115 Config Register error!!!\r\n");
        }
    }
}


int16_t ads1115_read_data(I2C_HandleTypeDef ads1115_I2cHandle)
{
    int16_t data;
    uint8_t rx_data[2]={0};
 
    while(HAL_I2C_Master_Transmit(&ads1115_I2cHandle, ADS1115_WRITE_ADDRESS, 0x00, 1, 1000) != HAL_OK)
    {
        if(HAL_I2C_GetError(&ads1115_I2cHandle) != HAL_I2C_ERROR_AF)
        {
            Usart1Printf("ads1115 convert Register error!!!\r\n");
        }
    }
 
    while(HAL_I2C_Master_Receive(&ads1115_I2cHandle, ADS1115_READ_ADDRESS, rx_data, 2, 1000) != HAL_OK)
    {
        if(HAL_I2C_GetError(&ads1115_I2cHandle) != HAL_I2C_ERROR_AF)
        {
            Usart1Printf("ads1115 read data error!!!\r\n");
        }
    }
 
    data=rx_data[0]*256+rx_data[1];
    return data;
}


double ads1115_get_voltage_val(I2C_HandleTypeDef ads1115_I2cHandle,uint8_t pointADD,uint8_t configH,uint8_t configL)
{
    double val;
    int16_t ad_val;
 
    ads1115_config_register(ads1115_I2cHandle,pointADD,configH,configL);
    HAL_Delay(10);
    ad_val=ads1115_read_data(ads1115_I2cHandle);
    if((ad_val==0x7FFF)|(ad_val==0X8000))//是否超量程了
    {
        ad_val=0;
        Usart1Printf("over PGA\r\n");
    }
 
    switch((0x0E&configH)>>1)//量程对应的分辨率
    {
        case(0x00):
            val=(double)ad_val*187.5/1000000.0;//
        break;
        case(0x01):
            val=(double)ad_val*125/1000000.0;
        break;
        case(0x02):
            val=(double)ad_val*62.5/1000000.0;
        break;
        case(0x03):
            val=(double)ad_val*31.25/1000000.0;
        break;
        case(0x04):
            val=(double)ad_val*15.625/1000000.0;
        break;
        case(0x05):
            val=(double)ad_val*7.8125/1000000.0;
        break;
    }
    return val;
 
}

extern uint8_t data_display_time;
extern uint8_t padlock;
extern uint8_t mode;
float current_value;//璇诲彇鐨勭數娴佸��
float voltage_value;//璇诲彇鐨勭數鍘嬪��
void Voltage_Current_display(void)
{
	static char current[]="00.00"; 
	static char voltage[]="00.00";
	static char power_str[]="00.00";
	static float vol,cur,power;
	static uint8_t x=1;
	float Current_multiple=5.8,Voltage_multiple=11.11,time_value=0.1,battery;
	static float battery_capacity=0;//鐢垫睜瀹归噺
	if(padlock==0)//褰撳紑濮嬭緭鍑哄悗锛屽啀鏇存柊鏁版嵁
	{
		if(data_display_time>=100)
		{
				x=1;
				data_display_time=0;
				cur=current_value;//璇诲彇鐢垫祦鏁版嵁
				cur=cur*Current_multiple;
				if(cur>=10) sprintf(current,"%.2f",cur);
				else sprintf(current,"%.3f",cur);
	//			Usart1Printf("dianliu:%s\r\n",current);
				Current_display(current);			
				vol=voltage_value;//璇诲彇鐢靛帇鏁版嵁
				vol=vol*Voltage_multiple;
				if(vol>=10&&vol<100) sprintf(voltage,"%.2f",vol);
				else if(vol>=100) sprintf(voltage,"%.1f",vol);
				else if(vol<10) sprintf(voltage,"%.3f",vol);
				voltage_display(voltage);	
			if(mode==1||mode==2)
			{
				power=vol*cur;
				if(power>=10&&power<100) sprintf(power_str,"%.2f",power);
				else if(power>=100) sprintf(power_str,"%.1f",power);
				else if(power<10) sprintf(power_str,"%.3f",power);
				power_display(power_str);
			}
			else if(mode==3)
			{
				battery=current_value*Current_multiple*time_value/3600;
				battery_capacity+=battery;

				if(battery_capacity>=10&&battery_capacity<100) sprintf(power_str,"%.2f",battery_capacity);
				else if(battery_capacity>=100) sprintf(power_str,"%.1f",battery_capacity);
				else if(battery_capacity<10) sprintf(power_str,"%.3f",battery_capacity);		
//				Usart1Printf("%s\r\n",power_str);
				power_display(power_str);				
			}
		}
	}
	else
	{
		if(x==1)
		{
			x=0;
			
			sprintf(voltage,"%s","00.00");
			sprintf(current,"%s","00.00");
			sprintf(power_str,"%s","00.00");
			if(mode!=3) power_display(power_str);
			voltage_display(voltage);
			Current_display(current);
			battery_capacity=0;//灏嗗凡缁忕敤杩囩殑鏁版嵁娓呴浂锛屽惁鍒欎笅娆′娇鐢ㄨ繕浼氭樉绀轰笂娆＄殑鏁版嵁
			current_value=0;
			voltage_value=0;
		}
	}
}	

extern uint8_t ads1115_read_time;
extern uint16_t Temperature_protection;
uint16_t vol_out_value=0;
float current_target;//鐢垫祦鐩爣鍊�
float power_target;//鍔熺巼鐩爣鍊�
void ads1115_value_read(void)
{
	float Current_multiple=5.8,Voltage_multiple=11.11;
	static uint8_t ads1115_read_time_old=0,i=1;
	uint16_t vol_out=0;
	if(padlock==0)
	{
		if(ads1115_read_time>=20&&i==1)
		{
			current_value=ads1115_get_voltage_val(hi2c1,0x01,CONFIG_REG_H_3,CONFIG_REG_L_3);
			voltage_value=ads1115_get_voltage_val(hi2c1,0x01,CONFIG_REG_H_2,CONFIG_REG_L_2);//璇诲彇鐢靛帇鏁版嵁
			if(mode==1||mode==3) vol_out_value=(int)((current_target*378+PID_realize(current_target,current_value*Current_multiple))*10+5)/10;
			else vol_out_value=(int)((power_target/(voltage_value*Voltage_multiple)*378+PID_realize(power_target/(voltage_value*Voltage_multiple),current_value*Current_multiple))*10+5)/10;
			if(vol_out_value>4095&&vol_out_value<=4115)vol_out_value=4095;
			else if (vol_out_value>4115)vol_out_value=0;
			ads1115_read_time_old=ads1115_read_time;
//			Usart1Printf("ads1115_read_time_old:%d\r\n",ads1115_read_time_old);
			i=0;
		}
		if((ads1115_read_time>=(ads1115_read_time_old+5))&&i==0)
		{
//			Usart1Printf("ads1115_read_time:%d\r\n",ads1115_read_time);
			vol_out=vol_out_value-Temperature_protection;
			if (vol_out>4095)vol_out=0;
			MCP4725_WriteData_Volatge(vol_out_value);
			ads1115_read_time=0;
			i=1;
		}

		
	}
}


