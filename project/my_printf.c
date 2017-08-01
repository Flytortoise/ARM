#include "app.h"

char g_pcOutBuf[1024];
char g_pcInBuf[1024];

int my_printf(const char *fmt, ...)
{
	//int i;
	int len;
	va_list args;
	va_start(args, fmt);
	len = vsprintf(g_pcOutBuf,fmt,args);
	va_end(args);
	
	uart_send_str((unsigned char *)g_pcOutBuf);
	uart_send_str("\r\n");
	return len;
	
}

int my_scanf(const char * fmt, ...)
{
	int i = 0;
	unsigned char c;
	va_list args;
//	memset(g_pcInBuf,0,sizeof(g_pcInBuf));
	while(1)
	{
		c = uart_recv_byte();
		//uart_send_byte(c);
		if(c == ';')
		{
			g_pcInBuf[i] = '\0';
			uart_send_str("\r\n");
			break;
		}
		else
		{
			uart_send_byte(c);
			g_pcInBuf[i++] = c;
		}
	}
	
// 	uart_send_str((unsigned char *)g_pcInBuf);
// 	uart_send_str("\r\n");
	
	va_start(args,fmt);

//	uart_send_str((unsigned char *)g_pcInBuf);
//	uart_send_str((unsigned char *)fmt);
	i = vsprintf(g_pcInBuf,fmt,args);
//	uart_send_byte('9');
	va_end(args);
			
	return i;
}


