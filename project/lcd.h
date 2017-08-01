#ifndef LCD_H_
#define LCD_H_

void lcd_init(void);
void lcd_clear(unsigned int color);
void lcd_dis_bmp(const unsigned char *bmp);

int lcd_dis_char(unsigned int x, unsigned int y, unsigned int color, unsigned int back_color, unsigned char ch);
int lcd_dis_chinese(unsigned int x, unsigned int y, unsigned int color, unsigned int back_color,const char *str);
void lcd_dis_str(unsigned int x, unsigned int y, unsigned int color, unsigned int back_color,const char *str);
void lcd_dis_All(unsigned int x, unsigned int y, unsigned int color, unsigned int back_color,const char *str);
void lcd_dis_chinese_str(unsigned int x, unsigned int y, unsigned int color, unsigned int back_color, const char * str);
int lcd_printf(const char *fmt, ...);
extern char lcd_Buf[20];

#define WHITE 0XFFFFFF
#define RED 0XFF0000
#define ORANGE 0XFF8C00
#define YELLOW 0XFFFF00
#define GREEN 0X00FF00
#define BLUE 0X0000FF
#define GREEN2 0X00FFFF
#define PURPLE 0xFF00FF



#define VIDCON0			(*(volatile unsigned *)0x4c800000)	
#define VIDCON1			(*(volatile unsigned *)0x4c800004)	
#define VIDTCON0		(*(volatile unsigned *)0x4c800008)	
#define VIDTCON1		(*(volatile unsigned *)0x4c80000C)	
#define VIDTCON2		(*(volatile unsigned *)0x4c800010)	
#define WINCON0			(*(volatile unsigned *)0x4c800014)	
#define WINCON1			(*(volatile unsigned *)0x4c800018)	
#define VIDOSD0A		(*(volatile unsigned *)0x4c800028)	
#define VIDOSD0B		(*(volatile unsigned *)0x4c80002C)
#define VIDOSD1A		(*(volatile unsigned *)0x4c800034)	
#define VIDOSD1B		(*(volatile unsigned *)0x4c800038)	
#define VIDOSD1C		(*(volatile unsigned *)0x4c80003C)	
#define VIDW00ADD0B0	(*(volatile unsigned *)0x4c800064)	
#define VIDW00ADD0B1	(*(volatile unsigned *)0x4c800068)	
#define VIDW01ADD0		(*(volatile unsigned *)0x4c80006C)	
#define VIDW00ADD1B0	(*(volatile unsigned *)0x4c80007C)	
#define VIDW00ADD1B1	(*(volatile unsigned *)0x4c800080)	
#define VIDW01ADD1		(*(volatile unsigned *)0x4c800084)	
#define VIDW00ADD2B0	(*(volatile unsigned *)0x4c800094)	
#define VIDW00ADD2B1	(*(volatile unsigned *)0x4c800098)	
#define VIDW01ADD2		(*(volatile unsigned *)0x4c80009C)	
#define VIDINTCON		(*(volatile unsigned *)0x4c8000AC)	
#define W1KEYCON0		(*(volatile unsigned *)0x4c8000B0)	
#define W1KEYCON1		(*(volatile unsigned *)0x4c8000B4)	
#define W2KEYCON0		(*(volatile unsigned *)0x4c8000B8)	
#define W2KEYCON1		(*(volatile unsigned *)0x4c8000BC)	
#define W3KEYCON0		(*(volatile unsigned *)0x4c8000C0)	
#define W3KEYCON1		(*(volatile unsigned *)0x4c8000C4)	
#define W4KEYCON0		(*(volatile unsigned *)0x4c8000C8)	
#define W4KEYCON1		(*(volatile unsigned *)0x4c8000CC)	
#define WIN0MAP			(*(volatile unsigned *)0x4c8000D0)	
#define WIN1MAP			(*(volatile unsigned *)0x4c8000D4)	
#define WPALCON			(*(volatile unsigned *)0x4c8000E4)	
#define SYSIFCON0		(*(volatile unsigned *)0x4c800130)	
#define SYSIFCON1		(*(volatile unsigned *)0x4c800134)	
#define DITHMODE1		(*(volatile unsigned *)0x4c800138)	
#define SIFCCON0		(*(volatile unsigned *)0x4c80013C)	
#define SIFCCON1		(*(volatile unsigned *)0x4c800140)	
#define SIFCCON2		(*(volatile unsigned *)0x4c800144)	
#define CPUTRIGCON1		(*(volatile unsigned *)0x4c80015C)	
#define CPUTRIGCON2		(*(volatile unsigned *)0x4c800160)	
#define VIDW01ADD0		(*(volatile unsigned *)0x4c80006C)	
#define GPCCON			(*(volatile unsigned *)(0x56000020))	
#define GPCDAT			(*(volatile unsigned *)(0x56000024))	
#define GPCUDP			(*(volatile unsigned *)(0x56000028))	
#define GPDCON			(*(volatile unsigned *)(0x56000030))	
#define GPDDAT			(*(volatile unsigned *)(0x56000034))	
#define GPDUDP			(*(volatile unsigned *)(0x56000038))	
#define MISCCR			(*(volatile unsigned *)(0x56000080))	
#define GPLCON			(*(volatile unsigned *)(0x560000f0))	
#define GPLDAT			(*(volatile unsigned *)(0x560000f4))	
#define GPBCON 			(*(volatile unsigned long *)0x56000010)
#define GPBDAT 			(*(volatile unsigned long *)0x56000014)
#define GPGCON 			(*(volatile unsigned long *)0x56000060)
#define GPGDAT 			(*(volatile unsigned long *)0x56000064)

#define HSPW (0)
#define HBPD (40- 1)
#define HFPD (5 - 1)
#define VSPW (0)
#define VBPD (8 - 1)
#define VFPD (8 - 1)


#endif


