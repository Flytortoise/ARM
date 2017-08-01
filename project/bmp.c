#include "app.h"

int bmp_work(void)
{	
	//unsigned int t = 0x1000000;
	
	while(1)	//œ‡≤·¥Û—≠ª∑
	{
	//	lcd_printf("bmp_flag = %d   ",bmp_flag);
		
		//t = 0x1000000;
		lcd_dis_bmp(gImage_bmp2);
		//while(t--)
		{
			while((GPFDAT & 0x08) == 0)	
			{
				while((GPFDAT & 0x08) == 0);	
				return 0;
				
			}
		}
		
		lcd_dis_bmp(gImage_bmp3);
		//t = 0x1000000;
		//while(t--)
		{
			while((GPFDAT & 0x08) == 0)	
			{
				while((GPFDAT & 0x08) == 0);	
				return 0;
				
			}
		}
		//t = 0x10000000;
		
	}
}
