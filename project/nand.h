#ifndef NAND_H_
#define NAND_H_


#define rNFCONF	 (*(volatile unsigned long *)(0x4e000000))
#define rNFCONT	 (*(volatile unsigned long *)(0x4e000004))
#define rNFCMD	 (*(volatile unsigned long *)(0x4e000008))
#define rNFADDR	 (*(volatile unsigned long *)(0x4e00000c))
#define rNFDATA8 (*(volatile unsigned char *)(0x4e000010))
#define rNFSTAT  (*(volatile unsigned long *)(0x4e000028))
#define rGPACON  (*(volatile unsigned long *)(0x56000000))


//选中芯片
#define NF_Enable() {rNFCONT &= ~(1<<1);}

//取消选中
#define NF_Disable() {rNFCONT |= (1<<1);}

//发送指令
#define NF_Send_Cmd(cmd) {rNFCMD = (cmd);}

//发送地址函数
#define NF_Send_Addr(addr) {rNFADDR = addr;}	

//发送数据函数
#define NF_Send_Data(data) {rNFDATA8 = (data);}

//使能检测
#define NF_Enable_RB() {rNFSTAT |= (1 << 4);}	

//判别忙
#define NF_Check_Busy() {while(!(rNFSTAT & (1 << 0)));}	

//读字节函数
#define NF_Read_Byte() (rNFDATA8)	



#define NF_CMD_READ1         0x00
#define NF_CMD_READ2         0x30

#define NF_CMD_WRITE1        0x80
#define NF_CMD_WRITE2        0x10

#define NF_CMD_RESET         0xff

#define NF_CMD_ERASE1        0x60
#define NF_CMD_ERASE2        0xd0


void nand_init(void);
void nand_erasure(unsigned int block);	//擦除
void nand_write(unsigned int block, unsigned int page, unsigned char *buf);
void nand_read(unsigned int block, unsigned int page, unsigned char *buf);


#endif

