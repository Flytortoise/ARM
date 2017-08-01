#include "app.h"

void Init()
{
	uart_init();
	lcd_init();
	MMU_Init();
	time0_init();
	//key_init();
	rtc_init();
}



void Main()
{	
	Init();
	lcd_clear(WHITE);
	
	while(1)
	{
		while((GPFDAT & 0x04) == 0)	
		{
			while((GPFDAT & 0x04) == 0);	//ʱ��
			WORK = RTC;		
		}
        
		
		while((GPFDAT & 0x02) == 0)
		{
			while((GPFDAT & 0x02) == 0);	//���
			WORK = BMP;			
		}
			
		switch(WORK)		//����ѡ��
		{
			case BMP:
				//work_flag = 1;	
				bmp_work();
				ir_flag = 0;			
				lcd_clear(WHITE);			
				break;
			
			case RTC:
				//work_flag = 1;	
				rtc_work();	
				ir_flag = 0;			
				lcd_clear(WHITE);
				break;
			
			default :
				break;
		}
		
		if(ir_flag >= 10)
		{
			ir_flag = 0;
			WORK = RTC;
		}
		
		
		WORK = 0;
		RTC_S();
		
						
 	}
	
}





