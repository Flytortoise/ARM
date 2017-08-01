#include "app.h"

#define TACLS 1
#define TWRTH0 4
#define TWRTH1 0


void nand_rest()
{
	NF_Enable();
	NF_Enable_RB();
	NF_Send_Cmd(NF_CMD_RESET);
	NF_Check_Busy();
	NF_Disable();
}

void nand_init()
{
	rGPACON |= (0x3f << 17);
	rNFCONF = (TACLS << 12) | (TWRTH0 << 8) | (TWRTH1 << 4);
	rNFCONT |= 1;
	rNFSTAT = 0;
	nand_rest();
}

void nand_erasure( unsigned int block)
{
	unsigned int block_num = (block << 6);
	nand_rest();	
	NF_Enable();
	NF_Enable_RB();
	NF_Send_Cmd(NF_CMD_ERASE1);
	NF_Send_Addr(block_num & 0xff);
	NF_Send_Addr((block_num >> 8) & 0xff);
	NF_Send_Addr((block_num >> 16) & 0xff);
	NF_Send_Cmd(NF_CMD_ERASE2);
	NF_Check_Busy();
	NF_Disable();
}

void nand_write(unsigned int block, unsigned int page, unsigned char *buf)
{
	int i = 0;
	unsigned int block_num = (block << 6);
	nand_rest();	
	NF_Enable();
	NF_Enable_RB();
	NF_Send_Cmd(NF_CMD_WRITE1);
	NF_Send_Addr(0x00);
	NF_Send_Addr(0x00);
	NF_Send_Addr(block_num & 0xff);
	NF_Send_Addr((block_num >> 8) & 0xff);
	NF_Send_Addr((block_num >> 16) & 0xff);
	
	for(i = 0; i < 2048; i++)
	{
		NF_Send_Data(buf[i]);
	}
	
	NF_Send_Cmd(NF_CMD_WRITE2);
	NF_Check_Busy();
	NF_Disable();
}

void nand_read(unsigned int block, unsigned int page, unsigned char *buf)
{
	int i = 0;
	unsigned int block_num = (block << 6);
	nand_rest();	
	NF_Enable();
	NF_Enable_RB();
	NF_Send_Cmd(NF_CMD_READ1);
	NF_Send_Addr(0x00);
	NF_Send_Addr(0x00);
	NF_Send_Addr(block_num & 0xff);
	NF_Send_Addr((block_num >> 8) & 0xff);
	NF_Send_Addr((block_num >> 16) & 0xff);
	
	NF_Send_Cmd(NF_CMD_READ2);
	NF_Check_Busy();
	
	for(i = 0; i < 2048; i++)
	{
		buf[i] = NF_Read_Byte();
	}
	
	NF_Disable();
	
}






