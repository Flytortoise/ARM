#include "app.h"

unsigned char ir_flag = 0;
unsigned char WORK = 0;
//unsigned char work_flag = 0;


void do_irq(void)
{
	LED_S();	
	RTC_S();
	ir_flag++;
		
	SRCPND = SRCPND;
	INTPND = INTPND;
		
}


