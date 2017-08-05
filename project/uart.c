#include "app.h"
#include <stdio.h>
#include <string.h>
extern int main_flag;
extern TIME time_temp;
extern TIME t;
extern int change_flag ;
extern int bmp_speed;

#define ULCON0   		( *((volatile unsigned long *)0x50000000) )
#define UCON0    		( *((volatile unsigned long *)0x50000004) )
#define UFCON0   	 	( *((volatile unsigned long *)0x50000008) )
#define UMCON0    		( *((volatile unsigned long *)0x5000000C) )
#define UTRSTAT0  		( *((volatile unsigned long *)0x50000010) )
#define UFSTAT0 		( *((volatile unsigned long *)0x50000018) )
#define UTXH0      		( *((volatile unsigned char *)0x50000020) )
#define URXH0      		( *((volatile unsigned char *)0x50000024) ) 
#define UBRDIV0    		( *((volatile unsigned short *)0x50000028) )
#define UDIVSLOT0  		( *((volatile unsigned short *)0x5000002C) )
#define GPHCON     		( *((volatile unsigned long *)0x56000070 ) )
#define INTMSK1     	( *((volatile unsigned long *)0x4A000008 ) )
#define INTSUBMSK     	( *((volatile unsigned long *)0X4A00001C ) )
#define INTPND1     	( *((volatile unsigned long *)0X4A000010 ) )
#define UART_INT (*(unsigned *)(0x33ffff90))

unsigned char uart_buff[100];
int uart_bmp_flag = 0;
int uart_rtc_flag = 0;
int uart_plus_flag = 0;

int set_time(char *);

void uart_init(void)
{
	//设置GPH0和GPH1为TXD,RXD
	GPHCON = 0XA;
	
	//设置串口的数据格式为8N1
	ULCON0 = 0X03;
	
	//设置UART时钟PCLK，禁止中断，使能发送
	UCON0 = 0X05;
	
	//使能FIF0，串口接收和发送的缓冲
	UFCON0 = 0X01;
	
	//无流量控制  可不写
	UMCON0 = 0;
	
	//设置波特率  115200
	UBRDIV0 = 35;
	UDIVSLOT0 = 0X888;
	
// 	INTMSK1 &= ~(1 << 28);
// 	INTSUBMSK &= ~(0x1);
	//UART_INT = (unsigned int)uart_work;
	
}

void uart_send_byte(unsigned char ch)
{
	while(UFSTAT0 & (1 << 14));
	
	UTXH0 = ch;
}

char uart_recv_byte()
{
	while((UFSTAT0 & 0X7F)==0)
	{
		delay_c(0x10000);
		if((UFSTAT0 & 0X7F)==0)
		{
			return ';';
		}
	}
	
	return URXH0;
}

void uart_send_str(unsigned char *str)
{
	while(*str)
	{
		uart_send_byte(*str);
		str++;
	}
}

void uart_recv_str(unsigned char *buff)
{
	*buff = uart_recv_byte();
	while(*buff != ';')
	{
		buff++;
		*buff = uart_recv_byte();
	}
	
	*buff = '\0';
		
}

int uart_work(void)
{
	int i;
	int dat = 0;
	uart_recv_str(uart_buff);
	
	if(strlen((char *)uart_buff) == 0)
	{
		return -1;
	}
	
	if(strcmp((char *)uart_buff,"run bmp") == 0)
	{
		bmp_work();
		
	}
	
	if(strcmp((char *)uart_buff,"run time") == 0)
	{
		rtc_work();
		
	}
	
	if(uart_bmp_flag)
	{
		if(strcmp((char *)uart_buff,"display1") == 0)
		{
			change_flag = 1;
			
		}
		
		if(strcmp((char *)uart_buff,"display2") == 0)
		{
			change_flag = -1;
		}
		
		
		
		if(strcmp((char *)uart_buff,"bmp +") == 0)
		{
			uart_plus_flag = 1;
		}
		
		if(strcmp((char *)uart_buff,"bmp -") == 0)
		{
			uart_plus_flag = 2;
		}
		
		if(strncmp((char *)uart_buff,"set speed = ",12) == 0 )
		{
			i = 12;
			while(uart_buff[i] != '\0')
			{
				dat = dat*10 + uart_buff[i] - '0';
				i++;
			}
			
			if(dat >= 1 && dat <= 5)
			{
				bmp_speed = dat;
			}		
			
		}
		
		
		
	}
	else if(uart_rtc_flag)
	{
		set_time((char *)uart_buff);
	}
	
	//uart_send_str(uart_buff);
	
	return 0;
}

int set_time(char *str)
{
	int dat = 0;
	int i = 0;
//	char day_buff[20];
	TIME t;
	rtc_get_time(&t);
	
	if(strncmp(str,"set year = ",11) == 0 )
	{
		i = 11;
		while(str[i] != '\0')
		{
			dat = dat*10 + str[i] - '0';
			i++;
		}
		
		if(dat >= 0 && dat <= 99)
		{
			t.year = INT2BCD(&dat);
			rtc_set_t(&t);
			return 0;
		}		
		else
		{
			return 1;
		}
	}
	
	if(strncmp(str,"set month = ",12) == 0 )
	{
		i = 12;
		while(str[i] != '\0')
		{
			dat = dat*10 + str[i] - '0';
			i++;
		}
		
		if(dat >= 1 && dat <= 12)
		{
			t.month = INT2BCD(&dat);
			rtc_set_t(&t);
			return 0;
		}		
		else
		{
			return 1;
		}
	}
	
	if(strncmp(str,"set day = ",10) == 0 )
	{
		i = 10;
		while(str[i] != '\0')
		{
			dat = dat*10 + str[i] - '0';
			i++;
		}
		if(dat >= 0 && dat <= 31)
		{
			t.day = INT2BCD(&dat);
			rtc_set_t(&t);
			return 0;
		}		
		else
		{
			return 1;
		}
	}
	
	if(strncmp(str,"set hour = ",11) == 0 )
	{
		i = 11;
		while(str[i] != '\0')
		{
			dat = dat*10 + str[i] - '0';
			i++;
		}
		
		if(dat >= 0 && dat <= 23)
		{
			t.hour = INT2BCD(&dat);
			rtc_set_t(&t);
			return 0;
		}		
		else
		{
			return 1;
		}
	}
	
	if(strncmp(str,"set min = ",10) == 0 )
	{
		i = 10;
		while(str[i] != '\0')
		{
			dat = dat*10 + str[i] - '0';
			i++;
		}
		
		if(dat >= 0 && dat <= 59)
		{
			t.min = INT2BCD(&dat);
			rtc_set_t(&t);
			return 0;
		}		
		else
		{
			return 1;
		}
	}
	
	if(strncmp(str,"set sec = ",10) == 0 )
	{
		i = 10;
		while(str[i] != '\0')
		{
			dat = dat*10 + str[i] - '0';
			i++;
		}
		
		if(dat >= 0 && dat <= 59)
		{
			t.sec = INT2BCD(&dat);
			rtc_set_t(&t);
			return 0;
		}		
		else
		{
			return 1;
		}
	}
	
	return 0;
}




