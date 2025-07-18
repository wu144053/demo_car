#ifndef _BSP_UART_H_
#define _BSP_UART_H_
/* user code begin include*/

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "usart.h"
#include "stm32f1xx_it.h"
#include "string.h"
#include "stdio.h"
#include "main.h"

/* user code end include*/

/* user code begin define */
#define RX_BUF_SIZE 120
#define TX_BUF_SIZE 100
/* user code end define */

/* user code begin PV*/

extern uint8_t rx_buf[];
extern uint8_t tx_buf[];
extern uint8_t rx_buf3[];
extern uint8_t packnew[RX_BUF_SIZE];
extern uint8_t recive_len;

/* user code end PV*/

//typedef uint8_t u8;

/*Exported functions prototypes-----------------------------------------------*/
void HAL_UART_IDLE_IRQHandler(UART_HandleTypeDef *huart);
void bsp_blue_recive_packet(uint8_t * rx_buf , uint8_t len);
void bsp_bluetooth_commond();
void bsp_blue_send_number(int32_t number);
void bsp_Serial_printf(char* format,...);
void bsp_uart_string(char * string);
void bsp_blue_send(uint8_t* tx_blue_buf);
void send_control_data(uint8_t adjust,uint8_t aData,uint8_t dData);
void bsp_uart3_send(uint8_t* tx_blue_buf);


#endif // !_BSP_UART_H_

