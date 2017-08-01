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
	//����GPH0��GPH1ΪTXD,RXD
	GPHCON = 0XA;
	
	//���ô��ڵ����ݸ�ʽΪ8N1
	ULCON0 = 0X03;
	
	//����UARTʱ��PCLK����ֹ�жϣ�ʹ�ܷ���
	UCON0 = 0X05;
	
	//ʹ��FIF0�����ڽ��պͷ��͵Ļ���
	UFCON0 = 0X01;
	
	//����������  �ɲ�д
	UMCON0 = 0;
	
	//���ò�����  115200
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


