#ifndef UART_H_
#define UART_H_

void uart_init(void);

void uart_send_byte(unsigned char ch);
unsigned char uart_recv_byte(void);
void uart_send_str(unsigned char *str);
void uart_recv_str(unsigned char *buff);

#endif


