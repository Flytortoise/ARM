#ifndef _APP_H_
#define _APP_H_

#include "led.h"
#include "delay.h"
#include "lcd.h"
#include "uart.h"
#include "printf.h"
#include "nand.h"
#include "key.h"
#include "rtc.h"
#include "bmp.h"
#include "./MMU/mmu.h"

#include "time.h"

#define BMP 1
#define RTC 2


extern unsigned char WORK;
extern unsigned char work_flag;
extern unsigned char ir_flag;


extern unsigned char gImage_bmp1[307200];
extern unsigned char gImage_bmp2[307200];
extern unsigned char gImage_bmp3[307200];
extern unsigned char gImage_bmp4[307200];
extern unsigned char gImage_bmp5[307200];


typedef struct
{	
	unsigned char hex[32];
	char ch[4];
}chara;

extern const chara chinese[];

typedef struct
{	
	unsigned char hex[16];
	char ch[2];
}ASC;


extern const ASC ascii[];

extern int uart_bmp_flag;
extern int uart_rtc_flag;

#endif

