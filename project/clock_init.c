
#define 	LOCKCON0  	(*(volatile unsigned long *)0x4C000000)
#define 	MPLLCON   	(*(volatile unsigned long *)0x4C000010)
#define 	CLKSRC    	(*(volatile unsigned long *)0x4C000020)
#define 	CLKDIV0    	(*(volatile unsigned long *)0x4C000024)

#define MPLL_ON 0 
#define MDIV 400
#define PDIV 3
#define SDIV 1
#define ARMDIV 1
#define PREDIV 2
#define HCLKDIV 1
#define PCLKDIV 1

#define MPLLout 0	//应该是1  此处只是检测时钟初始化是否正确


void clock_init()
{
	
	//设置MPLLOUT输出为800M
	MPLLCON = ( MPLL_ON << 24 ) | ( MDIV << 14 ) | ( PDIV << 5) | ( SDIV );
	
	//设置ARMCLK,HCLK,PCLK
	CLKDIV0 = ( ARMDIV << 9 ) | ( PREDIV << 4 ) | ( PCLKDIV << 2) | ( HCLKDIV );
	
	//设置锁定时间，用于12M到800M的转换
	LOCKCON0 = 0XFFFF;
	
	//设置MPLL为输出
	CLKSRC = ( MPLLout << 4 );
		
}



