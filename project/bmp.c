#include "app.h"

extern int uart_plus_flag;

unsigned char temp[307200];
unsigned char temp1[320][240][4];
unsigned char bmp_temp_flag[307200] = {0};
int change_flag = 1;
unsigned char *bmp[] = {gImage_bmp1,gImage_bmp2,gImage_bmp3,gImage_bmp4,gImage_bmp5};

//从bmp1渐影到bmp2
int bmp_display1(unsigned char *bmp1, unsigned char *bmp2)
{
	unsigned int i,j,k;
	
	for(i = 0; i < 307200; i++)
	{
		bmp_temp_flag[i] = 0;
		temp[i] = bmp1[i];
	}
	lcd_dis_bmp(temp);
	for(j = 50; j >0 ; j-- )	//渐影效果
	{
		if(j % 2 != 0)
		{
			k = 307200/j;
			for(i = 0; i < k; i++)
			{
				if(bmp_temp_flag[i*j] == 0)
				{
					temp[i*j] = bmp2[i*j];
					bmp_temp_flag[i*j] = 1;
					while((GPFDAT & 0x08) == 0)	
					{
						while((GPFDAT & 0x08) == 0);	
						lcd_clear(WHITE);
						return 0;
						
					}
					
					while((GPFDAT & 0x01) == 0)	
					{
						while((GPFDAT & 0x01) == 0);
						lcd_dis_bmp(bmp2);						
						return -1;
						
					}
					
					
				}		
			}
			lcd_dis_bmp(temp);		
		}
		
	}	
	return 1;	
		
}

int bmp_display2(unsigned char *bmp1, unsigned char *bmp2)	//向下
{
	long int i;
	for(i = 0; i < 307200; i++)
	{
		temp[i] = bmp1[i];
	}
	lcd_dis_bmp(temp);
	
	for(i = 0; i < 307200; i++)
	{
		//uart_work();
		temp[i] = bmp2[i];
		if(i % 10000 == 0)
		{
			lcd_dis_bmp(temp);
		}
		
		while((GPFDAT & 0x08) == 0)	
		{
			while((GPFDAT & 0x08) == 0);
			lcd_clear(WHITE);			
			return 0;
			
		}
		
	}
	lcd_dis_bmp(temp);
	
	return 1;
}


int bmp_display3(unsigned char *bmp1, unsigned char *bmp2)	//向上
{
	int i;
	for(i = 0; i < 307200; i++)
	{
		temp[i] = bmp1[i];
	}
	lcd_dis_bmp(temp);
	
	for(i = 307200; i >= 0; i--)
	{
		//uart_work();
		temp[i] = bmp2[i];
		if(i % 10000 == 0)
		{
			lcd_dis_bmp(temp);
		}
		
		while((GPFDAT & 0x08) == 0)	
		{
			while((GPFDAT & 0x08) == 0);
			lcd_clear(WHITE);			
			return 0;
			
		}
		
	}
	
	lcd_dis_bmp(temp);
	
	return 1;
}


int bmp_work(void)
{	
	unsigned char i = 0;
	int flag = 1;
	
	change_flag = 1;
	lcd_dis_bmp(bmp[i]);
	uart_bmp_flag = 1;	
	uart_rtc_flag = 0;
	while(flag)	//相册大循环
	{	
		uart_work();
		while((change_flag != -1) && (change_flag != 0))		//默认循环播放
		{
			
			if(i == 4)
			{
				change_flag = bmp_display1(bmp[4],bmp[0]);
				i = 0;
			}
			else
			{
				change_flag = bmp_display1(bmp[i],bmp[i+1]);
				i++;
			}
			
			uart_work();
			flag = change_flag;
			
		}
		
		
		while((GPFDAT & 0x04) == 0)		//上一张
		{
			uart_work();
			while((GPFDAT & 0x04) == 0);				
			if(i == 4)
			{
				flag = bmp_display2(bmp[4], bmp[0]);
				i = 0;
			}
			else
			{
				flag = bmp_display2(bmp[i], bmp[i+1]);
				i++;
			}		
		}
				
		while((GPFDAT & 0x02) == 0)		//下一张
		{
			uart_work();
			while((GPFDAT & 0x02) == 0);				
			if(i == 0)
			{
				flag = bmp_display3(bmp[0], bmp[4]);
				i = 4;
			}
			else
			{
				flag = bmp_display3(bmp[i], bmp[i-1]);
				i--;
			}		
		}
		
		switch(uart_plus_flag)
		{
			case 1 :
				if(i == 4)
				{
					flag = bmp_display2(bmp[4], bmp[0]);
					i = 0;
				}
				else
				{
					flag = bmp_display2(bmp[i], bmp[i+1]);
					i++;
				}	
				break;
			
			case 2 :
				if(i == 0)
				{
					flag = bmp_display3(bmp[0], bmp[4]);
					i = 4;
				}
				else
				{
					flag = bmp_display3(bmp[i], bmp[i-1]);
					i--;
				}	
				break;
			
			default :
				break;
		}
		uart_plus_flag = 0;
		
		
		while((GPFDAT & 0x01) == 0)		//切换到循环播放
		{
			while((GPFDAT & 0x01) == 0);	
			change_flag = 1;
			
		}
		
		
		
		while((GPFDAT & 0x08) == 0)		//退出
		{
			while((GPFDAT & 0x08) == 0);
			lcd_clear(WHITE);
			uart_bmp_flag = 0;	
			return 0;
			
		}
		
	}
	uart_bmp_flag = 0;	
	return 0;
}




