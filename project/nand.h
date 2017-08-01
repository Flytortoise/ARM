#ifndef NAND_H_
#define NAND_H_


#define rNFCONF	 (*(volatile unsigned long *)(0x4e000000))
#define rNFCONT	 (*(volatile unsigned long *)(0x4e000004))
#define rNFCMD	 (*(volatile unsigned long *)(0x4e000008))
#define rNFADDR	 (*(volatile unsigned long *)(0x4e00000c))
#define rNFDATA8 (*(volatile unsigned char *)(0x4e000010))
#define rNFSTAT  (*(volatile unsigned long *)(0x4e000028))
#define rGPACON  (*(volatile unsigned long *)(0x56000000))


//ѡ��оƬ
#define NF_Enable() {rNFCONT &= ~(1<<1);}

//ȡ��ѡ��
#define NF_Disable() {rNFCONT |= (1<<1);}

//����ָ��
#define NF_Send_Cmd(cmd) {rNFCMD = (cmd);}

//���͵�ַ����
#define NF_Send_Addr(addr) {rNFADDR = addr;}	

//�������ݺ���
#define NF_Send_Data(data) {rNFDATA8 = (data);}

//ʹ�ܼ��
#define NF_Enable_RB() {rNFSTAT |= (1 << 4);}	

//�б�æ
#define NF_Check_Busy() {while(!(rNFSTAT & (1 << 0)));}	

//���ֽں���
#define NF_Read_Byte() (rNFDATA8)	



#define NF_CMD_READ1         0x00
#define NF_CMD_READ2         0x30

#define NF_CMD_WRITE1        0x80
#define NF_CMD_WRITE2        0x10

#define NF_CMD_RESET         0xff

#define NF_CMD_ERASE1        0x60
#define NF_CMD_ERASE2        0xd0


void nand_init(void);
void nand_erasure(unsigned int block);	//����
void nand_write(unsigned int block, unsigned int page, unsigned char *buf);
void nand_read(unsigned int block, unsigned int page, unsigned char *buf);


#endif

