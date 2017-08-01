#include "app.h"
#include <string.h>
#define LINEVAL 240
#define HOZVAL 320
char lcd_Buf[20];
unsigned int FRAME_BUF[240][320];

void lcd_init()
{
	//����GPC,GPDΪLCD����/���ݿ�
	GPCCON = 0XAAAAAAAA;
	GPDCON = 0XAAAAAAAA;
	
	//�򿪱��� ����GPB1Ϊ���
	GPBCON |= (0X01 << 2);
	GPBDAT |= (0X01 << 1);
	
	//���ýӿ�����ΪRGB��������ʾģʽΪRGB����ģʽ������VCLKʱ��Ƶ��
	//��VCLK,ѡ��ʱ�ӷ�Ƶ��ѡ��ʱ��Դ(0ΪHCLK),ʹ��ͼ�����
	VIDCON0 = (0 << 22) | (0 << 13) | (9 << 6) |
				(1 << 5) | (1 << 4) | (0 << 2) | (3);
	
	//����ʱ�Ӽ��ԣ��������Ŀ������趨
	VIDCON1 = (1 << 6) | (1 << 5);
	
	//����ʱ�����
	VIDTCON0 = (VBPD << 16) | ( VFPD << 8 ) | (VSPW);
	VIDTCON1 = (HBPD << 16) | ( HFPD << 8 ) | (HSPW);
	
	//���ó��Ϳ�
	VIDTCON2 = ((LINEVAL - 1) << 11) | (HOZVAL - 1);
	
	//����WINDOW0�����ݸ�ʽ��������ݸ�ʽΪ24bpp
	WINCON0 = (0XB << 2) | (1);
	
	//����WINDW0������
	VIDOSD0A = (0X0 << 11) | (0);
	VIDOSD0B = (319 << 11) | (239);
	
	//������ʾ�����ַ
	VIDW00ADD0B0 = (unsigned long )FRAME_BUF;
	VIDW00ADD0B1 = (unsigned long )FRAME_BUF + sizeof(FRAME_BUF);
	
}

void lcd_clear(unsigned int color)
{
	unsigned int i,j;
	for(i = 0; i < LINEVAL; i++)
	{
		for(j = 0; j < HOZVAL ;j++)
		{
			FRAME_BUF[i][j] = color;
		}
	}
}

void lcd_dis_bmp(const unsigned char *bmp)
{
	unsigned int i,j;
	int k = 0;
	for(i = 0; i < LINEVAL; i++)
	{
		for(j = 0; j < HOZVAL ;j++)
		{
			FRAME_BUF[i][j] = (bmp[k] << 24) | (bmp[k+1] << 16) | (bmp[k+2] << 8) | (bmp[k+3] << 0);
			k += 4;
		}
	}
}

int lcd_dis_char(unsigned int x, unsigned int y, unsigned int color, unsigned int back_color, unsigned char ch)
{
	unsigned char i,j;
	unsigned char temp;
	unsigned int k;
	
	for(k = 0; k < 200; k++)
	{
		if(ch == ascii[k].ch[0])
		{
			for(i = 0; i < 16; i++)
			{
				temp = 0x80;
				for(j = 0; j < 8; j++)
				{
					if(ascii[k].hex[i] & temp )
					{
						FRAME_BUF[x+i][y+j] = color;
					}
					else
					{
						FRAME_BUF[x+i][y+j] = back_color;
					}
					
					temp >>= 1;
					
				}
			}
			return 1;
		}
	}
	
	return 0;
	
}


int lcd_dis_chinese(unsigned int x, unsigned int y, unsigned int color, unsigned int back_color,const char *str)
{
	unsigned char i,j;
	unsigned int index;
	unsigned char temp;
	
	
	for(index = 0; index < 10000; index++)
	{
		if(strcmp(str,chinese[index].ch) == 0)
		{
			for(i = 0; i < 32; )
			{
				temp = 0x80;
				for(j = 0; j < 8; j++)
				{
					if(chinese[index].hex[i] & temp)
					//if(ascii[index][i] & temp)
					{
						FRAME_BUF[x+i/2][y+j] = color;
					}
					else
					{
						FRAME_BUF[x+i/2][y+j] = back_color;
					}
					
					temp >>= 1;			
				}
				
				temp = 0x80;
				for(j = 0; j < 8; j++)
				{
					if(chinese[index].hex[i+1] & temp)
					//if(ascii[index][i] & temp)
					{
						FRAME_BUF[x+i/2][y+8+j] = color;
					}
					else
					{
						FRAME_BUF[x+i/2][y+8+j] = back_color;
					}
					
					temp >>= 1;			
				}
				
				i+=2;			
			}
			
			return 1;
		}
	}

	return 0;
}


void lcd_dis_str(unsigned int x, unsigned int y, unsigned int color, unsigned int back_color,const char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		lcd_dis_char(x,y + i * 8,color,back_color,str[i]);
		i++;
	}
//	lcd_dis_char(x,y + i * 8,color,back_color,str[i]);
	 

}


void lcd_dis_chinese_str(unsigned int x, unsigned int y, unsigned int color, unsigned int back_color, const char * str)
{
	char buff[4] = {0};
	int index = 0;
	int count = 0;
	while(*str)
	{
		if(index == 2)
		{
			lcd_dis_chinese(x ,y+ count * 16,color,back_color,buff);
			count++;
			index = 0;
		}
		buff[index] = *str;
		index++;
		str++;
	}
	buff[index] = *str;
	lcd_dis_chinese(x ,y+ count * 16,color,back_color,buff);
}









void lcd_dis_All(unsigned int x, unsigned int y, unsigned int color, unsigned int back_color,const char *str)
{
	unsigned int i = 0;
	unsigned char flag = 0;
	char buff[3] = {0};
	while(str[i] != '\0')
	{
		if(lcd_dis_char(x,y + i * 8,color,back_color,str[i]) == 0)
		{
			flag++;
			buff[0] = str[i];
			buff[1] = str[i+1];
			lcd_dis_chinese(x,y + i * 8,color,back_color,buff);
			i += 2;
		}
		
		if(flag == 0)
		{
			i++;
		}
		else
		{
			flag = 0;
		}
		
	}
	
	
}







int lcd_printf(const char *fmt, ...)
{
	//int i;
	int len;
	va_list args;
	va_start(args, fmt);
	len = vsprintf(lcd_Buf,fmt,args);
	va_end(args);
	
	lcd_dis_str(100,0,RED,WHITE,lcd_Buf);
	
	return len;
}



