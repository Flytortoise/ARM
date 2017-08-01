#include "app.h"

#define ULCON0   		( *((volatile unsigned long *)0x50000000) )
#define UCON0    		( *((volatile unsigned long *)0x50000004) )
#define UFCON0   	 	( *((volatile unsigned long *)0x50000008) )
#define UMCON0    		( *((volatile unsigned long *)0x5000000C) )
#define UTRSTAT0  		( *((volatile unsigned long *)0x50000010) )
#define UFSTAT0 		( *((volatile unsigned long *)0x50000018) )
#define UTXH0      		( *((volatile unsigned char *)0x50000020) )
#define URXH0      		( *((volatile unsigned char *)0x50000024) ) 
#define UBRDIV0    		( *((volatile unsigned short *)0x50000028) )
#define UDIVSLOT0  		( *((volatile unsigned short *)0x5000002C) )
#define GPHCON     		( *((volatile unsigned long *)0x56000070 ) )



void uart_init(void)
{
	//设置GPH0和GPH1为TXD,RXD
	GPHCON = 0XA;
	
	//设置串口的数据格式为8N1
	ULCON0 = 0X03;
	
	//设置UART时钟PCLK，禁止中断，使能发送
	UCON0 = 0X05;
	
	//使能FIF0，串口接收和发送的缓冲
	UFCON0 = 0X01;
	
	//无流量控制  可不写
	UMCON0 = 0;
	
	//设置波特率  115200
	UBRDIV0 = 35;
	UDIVSLOT0 = 0X888;
}

void uart_send_byte(unsigned char ch)
{
	while(UFSTAT0 & (1 << 14));
	
	UTXH0 = ch;
}

unsigned char uart_recv_byte()
{
	while((UFSTAT0 & 0X7F)==0);
	
	return URXH0;
}

void uart_send_str(unsigned char *str)
{
	while(*str)
	{
		uart_send_byte(*str);
		str++;
	}
}

void uart_recv_str(unsigned char *buff)
{
	*buff = uart_recv_byte();
	while(*buff != '`')
	{
		buff++;
		*buff = uart_recv_byte();
	}
	
	*buff = '\0';
	
}


