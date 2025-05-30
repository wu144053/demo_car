#ifndef _BSP_UART_H_
#define _BSP_UART_H_
/* user code begin include*/

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "usart.h"
#include "stm32f1xx_it.h"
#include "string.h"

/* user code end include*/

/* user code begin define */
#define RX_BUF_SIZE 100
#define TX_BUF_SIZE 100
/* user code end define */

/* user code begin PV*/

extern uint8_t rx_buf[];
extern uint8_t tx_buf[];

/* user code end PV*/

/*Exported functions prototypes-----------------------------------------------*/
void HAL_UART_IDLE_IRQHandler(UART_HandleTypeDef *huart);
void bsp_blue_recive_packet(uint8_t * rx_buf , uint8_t len);
        
#endif // !_BSP_UART_H_
