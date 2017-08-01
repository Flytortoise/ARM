#ifndef _LED_H_
#define _LED_H_


#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4

#define ON 1
#define OFF 0

#define GPACON (*(volatile unsigned long *) 0x56000000)
#define GPADAT (*(volatile unsigned long *) 0x56000004)



void LED_init(void);
void Led_Control(unsigned char led, unsigned char ison);
void LED_Display(unsigned int count);

void LED_S(void);

#endif




