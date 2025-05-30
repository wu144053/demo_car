#ifndef _SERIAL_H_
#define _SERIAL_H_

#include"stm32f1xx_hal.h"

#define UART_RX_BUF_SIZE 512
#define UART_RX_QUEQUE_SIZE 1024


extern uint8_t flag ;
extern uint16_t length ;

typedef struct {
	uint16_t UART_RX_BUF[UART_RX_BUF_SIZE];
	volatile uint8_t head;
	volatile uint8_t tail;
	volatile uint8_t over_flow;
}UART_QUEue;

void serial_init(void);
void uart_RXqueue_Init(void);//初始化dma接收队列
extern UART_QUEue rx_queue;//声明队列
void uart_rxQueue_clear(void);//清空队列
void serial_send_num(uint8_t* tx_buf,uint8_t length);
void serial_send_str(uint8_t *tx_buf);
#endif // _SERIAL_H_
