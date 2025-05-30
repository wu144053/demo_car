#include"stm32f1xx_hal.h"
#include "tim.h"
#include "usart.h"
#include "string.h"
#include "serial.h"
uint8_t flag = 0;
uint16_t length = 0;

uint8_t UART_RX_dma_buf[2][UART_RX_BUF_SIZE];
volatile uint8_t current_dma_buf = 0;
UART_QUEue rx_queue;
uint8_t test_data[]= {0x01,0x02};

void uart_RXqueue_Init(){
	rx_queue.head = 0;
	rx_queue.over_flow = 0;
	rx_queue.tail = 0;
	
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart1,UART_RX_dma_buf[current_dma_buf],UART_RX_BUF_SIZE);

}

//清空队列
void uart_rxQueue_clear(){
	rx_queue.head = 0;
	rx_queue.over_flow = 0;
	rx_queue.tail = 0;
}

//void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size){
//	if(huart->Instance == USART1){
//		
//	serial_send_num(test_data,3);
////__HAL_UART_CLEAR_IDLEFLAG(huart);//清空中断标志位
//	uint16_t remain_size = __HAL_DMA_GET_COUNTER(huart->hdmarx);
//	uint16_t recive_len = UART_RX_BUF_SIZE - remain_size;
//	uint8_t *current_buf = UART_RX_dma_buf[current_dma_buf];
//	for(uint16_t i = 0 ; i < recive_len ; i ++){
//		uint16_t next_head = (rx_queue.head + 1) % UART_RX_BUF_SIZE ;
//		if(next_head != rx_queue.tail ){
//			rx_queue.UART_RX_BUF[rx_queue.head ] = current_buf[i];
//			rx_queue.head = next_head;
//		}
//		else{
//			rx_queue.over_flow = 1;
//			break;
//		}
//	}
//	
//	if(rx_queue.over_flow != 1){
//		uint8_t rx_tx_buf[UART_RX_QUEQUE_SIZE];
//		uint8_t length = 0;
//		while(rx_queue.tail != rx_queue.head){
//			rx_tx_buf[length++] = rx_queue.UART_RX_BUF[rx_queue.tail];
//			rx_queue.tail = (rx_queue.tail + 1) % UART_RX_QUEQUE_SIZE;
//		}
//		serial_send_num(rx_tx_buf,length);
//	}else{
//		uart_rxQueue_clear();
//	}
//	current_dma_buf ^= 1;//切换dma数组
//	HAL_UART_Receive_DMA(huart,UART_RX_dma_buf[current_dma_buf],UART_RX_BUF_SIZE);
//	}
//}

//void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size){		
//	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
//	if(huart->Instance == USART1){

//		flag = 1;
//		length = Size;
//	}
//}

void serial_send_num(uint8_t* tx_buf,uint8_t length){
	HAL_UART_Transmit_DMA(&huart1,tx_buf,length);
}

void serial_send_str(uint8_t *tx_buf){
	HAL_UART_Transmit_DMA(&huart1,tx_buf,strlen((char *)tx_buf));
}
