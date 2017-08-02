#include "app.h"
#include <stdio.h>
char time_buf[50];
char time2_buf[5];
unsigned int SetTime[6];
unsigned int Str2BCD(const char * str)
{
	unsigned int i = 0;
	unsigned int result = 0;
	while(str[i] != '\0')
	{
		result = result * 16 + (str[i] - '0');
		i++;
	}
	
	return result;
}


int rtc_set_time(const char *str)
{
	unsigned char i = 0;
	unsigned char j = 0;
	unsigned char k = 0;
	while(str[i] != '\0')
	{
		while(str[i] != '-' && str[i] != '\0')
		{
			if(str[i] >= '0' && str[i] <= '9')
			{
				time2_buf[j++] = str[i++];
			}
			else
			{
				return -1;
			}
			
		}
		
		if(j > 4)
		{
			return -1;
		}
		
		time2_buf[j] = '\0';
		SetTime[k++] = Str2BCD(time2_buf);
		j = 0;
		
		if(str[i] == '\0')
		{
			break;
		}
		else
		{
			i++;
		}
		
	}
	
	RTCCON |= 0X01;
	BCDYEAR = SetTime[0];
	BCDMONTH = SetTime[1];
	BCDDAY = SetTime[2];
	BCDHOUR = SetTime[3];
	BCDMIN = SetTime[4];
	BCDSEC = SetTime[5];
	RTCCON &= ~(0x01);
	
	return 0;
	
}

void rtc_get_time(TIME *time)
{
	RTCCON |= 0X01;
	time->year = BCDYEAR + 0x2000;
	time->month = BCDMONTH;
	time->day = BCDDAY;
	time->hour = BCDHOUR;
	time->min = BCDMIN;
	time->sec = BCDSEC;
	RTCCON &= ~(0x01);
}

void RTC_S(TIME *time)
{
	LED_S();
	rtc_get_time(time);
	sprintf(time_buf,"%x-%x-%x  %x : %x : %x  ",time->year,time->month,time->day,
											time->hour,time->min,time->sec);
	lcd_dis_All(0,0,RED,WHITE,time_buf);
}

int rtc_work()
{
	while(1)
	{
		lcd_dis_chinese_str(100, 100, RED, WHITE, "时间设置");
		while((GPFDAT & 0x08) == 0)	
		{
			while((GPFDAT & 0x08) == 0);	//时钟
			return 0;
			
		}
		
	}
	
	
}


