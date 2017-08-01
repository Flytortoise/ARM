
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

#define MPLLout 0	//Ӧ����1  �˴�ֻ�Ǽ��ʱ�ӳ�ʼ���Ƿ���ȷ


void clock_init()
{
	
	//����MPLLOUT���Ϊ800M
	MPLLCON = ( MPLL_ON << 24 ) | ( MDIV << 14 ) | ( PDIV << 5) | ( SDIV );
	
	//����ARMCLK,HCLK,PCLK
	CLKDIV0 = ( ARMDIV << 9 ) | ( PREDIV << 4 ) | ( PCLKDIV << 2) | ( HCLKDIV );
	
	//��������ʱ�䣬����12M��800M��ת��
	LOCKCON0 = 0XFFFF;
	
	//����MPLLΪ���
	CLKSRC = ( MPLLout << 4 );
		
}



