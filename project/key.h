#ifndef KEY_H_
#define KEY_H_


#define 	GPFCON 		(*(volatile unsigned long *)0x56000050)
#define 	GPFDAT 		(*(volatile unsigned long *)0x56000054)
#define 	EXTINT0		(*(volatile unsigned long *)0x56000088)
#define 	EINTPEND	(*(volatile unsigned long *)0x560000a8)
#define 	SRCPND		(*(volatile unsigned long *)0x4a000000)
#define 	INTMOD		(*(volatile unsigned long *)0x4a000004)
#define 	INTMSK		(*(volatile unsigned long *)0x4a000008)
#define 	INTPND		(*(volatile unsigned long *)0x4a000010)
#define 	INTOFFSET	(*(volatile unsigned long *)0x4a000014)

void key_init(void);

#endif



