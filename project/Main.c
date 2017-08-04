#include "app.h"
#include <stdio.h>
TIME t = {0,0,0,0,0,0};
TIME time_temp;
char send_buff[100];
int Show(int flag);

unsigned char cmd[50];

void Init()
{
	
	lcd_init();
	MMU_Init();
	uart_init();
	//time0_init();
	//key_init();
}



void Main()
{	
	int flag = 0;
	
//	int menu_flag = 0;
	
	Init();
	lcd_clear(WHITE);
	rtc_get_time(&time_temp);
	while(1)
	{
		rtc_get_time(&t);
// 		sprintf(send_buff,"a %d a ",(t.sec - time_temp.sec));
// 		uart_send_str((unsigned char *)send_buff);		
		while((GPFDAT & 0x02) == 0)
		{
			while((GPFDAT & 0x02) == 0);	//������		
			rtc_get_time(&time_temp);
			flag = 1;
			
		}
		
		while((GPFDAT & 0x04) == 0)
		{
			while((GPFDAT & 0x04) == 0);	//������		
			rtc_get_time(&time_temp);
			flag = 2;
			
		}
		
		while((GPFDAT & 0x01) == 0)
		{
			while((GPFDAT & 0x01) == 0);	//���½���	
			rtc_get_time(&time_temp);
			switch (flag)
			{
				case 1 :
					bmp_work();	
					break;
				
				case 2:
					rtc_work();			
					break;
				
				default :
					break;
			}
			lcd_clear(WHITE);
			rtc_get_time(&t);
			rtc_get_time(&time_temp);
							
		}
		
		if((t.sec - time_temp.sec) > 5)	//ͣ��5s����ʱ����ʾ
		{
			rtc_work();
			lcd_clear(WHITE);
			rtc_get_time(&time_temp);
		}
		
		Show(flag);
		LED_S();
		
						
 	}
	
}

int Show(int flag)
{
	lcd_dis_chinese_str(0, 0, BLUE, WHITE,"����");
	lcd_dis_All(50, 130, BLUE, WHITE,"�������");
	
	switch (flag)
	{
		case 1:
			lcd_dis_chinese_str(100, 100, BLUE, GREEN,"���");
			lcd_dis_chinese_str(100, 200, BLUE, WHITE,"ʱ��");
			break;
		
		case 2:
			lcd_dis_chinese_str(100, 100, BLUE, WHITE,"���");
			lcd_dis_chinese_str(100, 200, BLUE, GREEN,"ʱ��");
			break;
		
		default :
			lcd_dis_chinese_str(100, 100, BLUE, WHITE,"���");
			lcd_dis_chinese_str(100, 200, BLUE, WHITE,"ʱ��");
			break;
	}
	
	return 0;
}







