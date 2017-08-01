#include "app.h"
#include <stdio.h>
char time_buf[50];

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

void rtc_init()
{
	RTCCON = 0X01;
	BCDYEAR = Str2BCD("17");
	BCDMONTH = Str2BCD("8");
	BCDDAY = Str2BCD("1");
	BCDHOUR = Str2BCD("13");
	BCDMIN = Str2BCD("47");
	BCDSEC = Str2BCD("58");

}

void RTC_S()
{
	sprintf(time_buf,"%2x-%2x-%2x  %2x : %2x : %2x",BCDYEAR,BCDMONTH,BCDDAY,
											BCDHOUR,BCDMIN,BCDSEC);
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


