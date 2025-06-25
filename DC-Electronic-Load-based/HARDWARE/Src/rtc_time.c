#include "rtc_time.h"
#include "rtc.h"
#include "usart.h"
#include "stdio.h"
#include "lv_obj_my.h"
RTC_TimeTypeDef GetTime;    //获取时间结构体
RTC_DateTypeDef GetData;    //获取日期结构体
uint8_t run_time_control=0;
void GET_Time(void)
{
	char str[]="00:00:00";
	uint8_t Hours,Minutes,Seconds;
	static uint8_t Hours_old,Minutes_old,Seconds_old;
	
	if(run_time_control)
	{
		HAL_RTC_GetTime(&hrtc, &GetTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &GetData, RTC_FORMAT_BIN);
		Hours=GetTime.Hours;
		Minutes=GetTime.Minutes;
		Seconds=GetTime.Seconds;
		if(Hours!=Hours_old||Minutes!=Minutes_old||Seconds!=Seconds_old)
		{
			Hours_old=Hours;
			Minutes_old=Minutes;
			Seconds_old=Seconds;
			sprintf(str,"%02d:%02d:%02d",Hours,Minutes,Seconds);
			Run_Time(str);
		}
}
}

void Time_clear(void)
{
	RTC_TimeTypeDef sTime = {0};
	
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
}
