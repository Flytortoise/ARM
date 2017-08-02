#include "app.h"


void LED_init()
{
	GPACON = 0;
	GPBCON = (0X05 << 10);
}

void LED_S()
{
	Led_Control(LED1,ON);
	Led_Control(LED2,ON);
	Led_Control(LED3,ON);
	Led_Control(LED4,ON);
	delay_c(0x500000);
	Led_Control(LED1,OFF);
	Led_Control(LED2,OFF);
	Led_Control(LED3,OFF);
	Led_Control(LED4,OFF);
	delay_c(0x500000);
	
}

void LED_Display(unsigned int count)
{
	switch(count)
	{
		case 0:
			Led_Control(LED1,OFF);
			Led_Control(LED2,OFF);
			Led_Control(LED3,OFF);
			Led_Control(LED4,OFF);
		break;
		
		case 1:
			Led_Control(LED1,ON);
			Led_Control(LED2,OFF);
			Led_Control(LED3,OFF);
			Led_Control(LED4,OFF);
		break;
		
		case 2:
			Led_Control(LED1,OFF);
			Led_Control(LED2,ON);
			Led_Control(LED3,OFF);
			Led_Control(LED4,OFF);
		break;
		
		case 3:
			Led_Control(LED1,ON);
			Led_Control(LED2,ON);
			Led_Control(LED3,OFF);
			Led_Control(LED4,OFF);
		break;
		
		case 4:
			Led_Control(LED1,OFF);
			Led_Control(LED2,OFF);
			Led_Control(LED3,ON);
			Led_Control(LED4,OFF);
		break;
		
		case 5:
			Led_Control(LED1,ON);
			Led_Control(LED2,OFF);
			Led_Control(LED3,ON);
			Led_Control(LED4,OFF);
		break;
		
		case 6:
			Led_Control(LED1,OFF);
			Led_Control(LED2,ON);
			Led_Control(LED3,ON);
			Led_Control(LED4,OFF);
		break;
		
		case 7:
			Led_Control(LED1,ON);
			Led_Control(LED2,ON);
			Led_Control(LED3,ON);
			Led_Control(LED4,OFF);
		break;
		
		case 8:
			Led_Control(LED1,OFF);
			Led_Control(LED2,OFF);
			Led_Control(LED3,OFF);
			Led_Control(LED4,ON);
		break;
		
		case 9:
			Led_Control(LED1,ON);
			Led_Control(LED2,OFF);
			Led_Control(LED3,OFF);
			Led_Control(LED4,ON);
		break;
		
		case 10:
			Led_Control(LED1,OFF);
			Led_Control(LED2,ON);
			Led_Control(LED3,OFF);
			Led_Control(LED4,ON);
		break;
		
		case 11:
			Led_Control(LED1,ON);
			Led_Control(LED2,ON);
			Led_Control(LED3,OFF);
			Led_Control(LED4,ON);
		break;
		
		case 12:
			Led_Control(LED1,OFF);
			Led_Control(LED2,OFF);
			Led_Control(LED3,ON);
			Led_Control(LED4,ON);
		break;
		
		case 13:
			Led_Control(LED1,ON);
			Led_Control(LED2,OFF);
			Led_Control(LED3,ON);
			Led_Control(LED4,ON);
		break;
		
		case 14:
			Led_Control(LED1,OFF);
			Led_Control(LED2,ON);
			Led_Control(LED3,ON);
			Led_Control(LED4,ON);
		break;
		
		case 15:
			Led_Control(LED1,ON);
			Led_Control(LED2,ON);
			Led_Control(LED3,ON);
			Led_Control(LED4,ON);
		break;
		
		default :
			break;
	}
}




void Led_Control(unsigned char led, unsigned char ison)
{
	
	if(ison == ON)
	{
		switch(led)
		{
			case LED1 :
				GPBDAT &= ~(0x01 << 5);
			break;
			
			case LED2 :
				GPBDAT &= ~(0x01 << 6);
			break;
			
			case LED3 :
				GPADAT &= ~(0x01 << 25);
			break;
			
			case LED4 :
				GPADAT &= ~(0x01 << 26);
			break;
			
			default :
				break;
				
		}
	}
	else
	{
		switch(led)
		{
			case LED1 :
				GPBDAT |= (0x01 << 5);
			break;
			
			case LED2 :
				GPBDAT |= (0x01 << 6);
			break;
			
			case LED3 :
				GPADAT |= (0x01 << 25);
			break;
			
			case LED4 :
				GPADAT |= (0x01 << 26);
			break;
			
			default :
				break;
		}
	}
}




