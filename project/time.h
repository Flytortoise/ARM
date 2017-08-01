#ifndef TIME_H_
#define TIME_H_

#define		TCFG0		(*(volatile unsigned long *)0x51000000)
#define		TCFG1		(*(volatile unsigned long *)0x51000004)
#define		TCON		(*(volatile unsigned long *)0x51000008)
#define		TCNTB0		(*(volatile unsigned long *)0x5100000c)
#define		TCMPB0		(*(volatile unsigned long *)0x51000010)
#define		TCNTO0		(*(volatile unsigned long *)0x51000014)

#define 	SRCPND		(*(volatile unsigned long *)0x4a000000)
#define 	INTMOD		(*(volatile unsigned long *)0x4a000004)
#define 	INTMSK		(*(volatile unsigned long *)0x4a000008)
#define 	INTPND		(*(volatile unsigned long *)0x4a000010)
#define 	INTOFFSET	(*(volatile unsigned long *)0x4a000014)

void time0_init(void);

#endif 

