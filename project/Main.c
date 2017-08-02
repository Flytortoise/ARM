#include "app.h"

void Init()
{
	uart_init();
	lcd_init();
	MMU_Init();
	//time0_init();
	//key_init();
}



void Main()
{	
	TIME t = {0,0,0,0,0,0};
	Init();
	lcd_clear(WHITE);
	
	
	
	while(1)
	{
		while((GPFDAT & 0x04) == 0)	
		{
			while((GPFDAT & 0x04) == 0);	// ±÷”
			bmp_work();	
			lcd_clear(WHITE);
		}
        
		
		while((GPFDAT & 0x02) == 0)
		{
			while((GPFDAT & 0x02) == 0);	//œ‡≤·
			rtc_work();
			lcd_clear(WHITE);			
		}
		
		
		WORK = 0;	
		RTC_S(&t);
		LED_S();
						
 	}
	
}





