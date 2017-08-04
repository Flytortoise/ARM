#include "app.h"
#include <stdio.h>

extern TIME t;

int rtc_show(int );
void change_day1(unsigned int *);
void change_day2(unsigned int *);
int rtc_time_change(int flag,unsigned int *date);

char time_buf[50];
char time2_buf[5];
unsigned int SetTime[6];


TIME time_;

unsigned int INT2BCD(unsigned int *dat)
{
	unsigned int result= 0;
	unsigned int temp = *dat;
	
	result = temp/10 * 16 + temp % 10;
	*dat = result;
	
	return result;
}

unsigned int BCD2INT(unsigned int *dat)
{
	unsigned int result= 0;
	unsigned int temp = *dat;
	
	result = temp/16 * 10 + temp % 16;
	*dat = result;
	
	return result;
}

void rtc_BCD2INT(TIME *time)
{
	BCD2INT(&time->year);
	BCD2INT(&time->month);
	BCD2INT(&time->day);
	BCD2INT(&time->hour);
	BCD2INT(&time->min);
	BCD2INT(&time->sec);
	
}

void rtc_INT2BCD(TIME *time)
{
	INT2BCD(&time->year);
	INT2BCD(&time->month);
	INT2BCD(&time->day);
	INT2BCD(&time->hour);
	INT2BCD(&time->min);
	INT2BCD(&time->sec);
	
}


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
	time->year = BCDYEAR;
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
	sprintf(time_buf,"20%x-%x-%x  %x : %x : %x         ",time->year,time->month,time->day,
											time->hour,time->min,time->sec);
	lcd_dis_All(100,85,BLUE,WHITE,time_buf);
}

int rtc_work()
{
	int flag = 0;
	int ON_flag = 0;
	lcd_clear(WHITE);
	rtc_get_time(&time_);
	
	rtc_BCD2INT(&time_);
	
	
	while(1)
	{
		if(ON_flag)
		{
			lcd_dis_All(50, 100, BLUE, WHITE,"    时间设置               ");
			while((GPFDAT & 0x02) == 0)
			{
				while((GPFDAT & 0x02) == 0);	//按下左		
				
				flag--;
				if(flag < 1)
				{
					flag = 6;
				}
					
				
			}
			
			while((GPFDAT & 0x04) == 0)
			{
				while((GPFDAT & 0x04) == 0);	//按下右		
				
				flag++;
				if(flag > 6)
				{
					flag = 1;
				}
				
			}
			
			while((GPFDAT & 0x01) == 0)
			{
				while((GPFDAT & 0x01) == 0);	//按下进入	
				switch(flag)
				{
					case 1:
						rtc_time_change(flag,&time_.year);
						break;
					case 2:
						rtc_time_change(flag,&time_.month);
						break;
					case 3:
						rtc_time_change(flag,&time_.day);
						break;
					case 4:
						rtc_time_change(flag,&time_.hour);
						break;
					case 5:
						rtc_time_change(flag,&time_.min);
						break;
					case 6:
						rtc_time_change(flag,&time_.sec);
						break;
				}
								
			}
			
			
			while((GPFDAT & 0x08) == 0)	
			{
				while((GPFDAT & 0x08) == 0);	//退出
				ON_flag = 0;		
			}
			
			
			rtc_show(flag);
		}
		else
		{
			lcd_dis_All(50, 100, BLUE, WHITE,"按确定键进入时间设置");
			RTC_S(&t);
			while((GPFDAT & 0x01) == 0)
			{
				while((GPFDAT & 0x01) == 0);	//按下进入	
				ON_flag = 1;
			}
			
			while((GPFDAT & 0x08) == 0)	
			{
				while((GPFDAT & 0x08) == 0);	//退出
				return 0;	
			}
		}
		

	}
	
}

int rtc_show(int flag)
{
	switch(flag)
	{
		case 1:
			sprintf(time_buf,"【20%d】 -%d-%d  %d : %d : %d     ",time_.year,time_.month,time_.day,
											time_.hour,time_.min,time_.sec);
			break;
		case 2:
			sprintf(time_buf,"20%d- 【%d】 -%d  %d : %d : %d    ",time_.year,time_.month,time_.day,
											time_.hour,time_.min,time_.sec);
			break;
		case 3:
			sprintf(time_buf,"20%d-%d- 【%d】   %d : %d : %d    ",time_.year,time_.month,time_.day,
											time_.hour,time_.min,time_.sec);
			break;
		case 4:
			sprintf(time_buf,"20%d-%d-%d  【%d】   : %d : %d    ",time_.year,time_.month,time_.day,
											time_.hour,time_.min,time_.sec);
			break;
		case 5:
			sprintf(time_buf,"20%d-%d-%d  %d : 【%d】  : %d     ",time_.year,time_.month,time_.day,
											time_.hour,time_.min,time_.sec);
			break;
		case 6:
			sprintf(time_buf,"20%d-%d-%d  %d : %d : 【%d】      ",time_.year,time_.month,time_.day,
											time_.hour,time_.min,time_.sec);
			break;
		default:
			sprintf(time_buf,"20%d-%d-%d  %d : %d : %d          ",time_.year,time_.month,time_.day,
											time_.hour,time_.min,time_.sec);
			break;
	}
	
	lcd_dis_All(100,85,BLUE,WHITE,time_buf);	
	return 0;
}

int rtc_time_change(int flag,unsigned int *date)
{
	char change_flag = 0;
	lcd_dis_All(50, 100, RED, WHITE, "    请设置具体数值");
	while(1)
	{
		while((GPFDAT & 0x02) == 0)
		{
			while((GPFDAT & 0x02) == 0);	//按下+	
			if(change_flag)
			{
				lcd_dis_str(150, 130, WHITE, WHITE,"          ");
				change_flag = 0;
			}
			
			(*date)++;
			switch(flag)
			{
				case 1:
					if(*date > 99) *date = 0;
					break;
				case 2:
					if(*date > 12) *date = 1;
					break;
				case 3:
					change_day1(date);
					break;
				case 4:
					if(*date > 24) *date = 1;
					break;
				case 5:
					if(*date > 59) *date = 0;
					break;
				case 6:
					if(*date > 59) *date = 0;
					break;
			}
				
			
		}
		
		while((GPFDAT & 0x04) == 0)
		{
			while((GPFDAT & 0x04) == 0);	//按下右		
			if(change_flag)
			{
				lcd_dis_str(150, 130, WHITE, WHITE,"          ");
				change_flag = 0;
			}
			(*date)--;
			switch(flag)
			{
				case 1:
					if(*date >99 ) *date = 99;
					break;
				case 2:
					if(*date > 12) *date = 12;
					break;
				case 3:
					change_day2(date);
					break;
				case 4:
					if(*date > 24) *date = 23;
					break;
				case 5:
					if(*date > 59) *date = 59;
					break;
				case 6:
					if(*date > 59) *date = 59;
					break;
			}
			
		}
		
		while((GPFDAT & 0x01) == 0)
		{
			while((GPFDAT & 0x01) == 0);	//按下确定	
			sprintf(time_buf,"%d-%d-%d-%d-%d-%d",time_.year,time_.month,time_.day,
											time_.hour,time_.min,time_.sec);
			rtc_set_time(time_buf);
			lcd_dis_chinese_str(150, 130, RED, WHITE,"设置成功");
			change_flag++;
		}
		
		
		while((GPFDAT & 0x08) == 0)	
		{
			while((GPFDAT & 0x08) == 0);	//退出
			if(change_flag)
			{
				lcd_dis_str(150, 130, WHITE, WHITE,"          ");
				change_flag = 0;
			}
			return 0;		
		}
		
		rtc_show(flag);
		
	
	}
	
	return 0;
}

void change_day1(unsigned int *day)
{
	switch(time_.month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:if(*day > 31) *day = 1;
			break;
		case 4:
		case 6:
		case 9:
		case 11:if(*day > 30) *day = 1;
			break;
		case 2: if(*day > 28) *day = 1;
			break;
			
	}
}

void change_day2(unsigned int *day)
{
	switch(time_.month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:if(*day == 0) *day = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:if(*day == 0) *day = 30;
			break;
		case 2: if(*day == 0) *day = 28;
			break;
			
	}
}




