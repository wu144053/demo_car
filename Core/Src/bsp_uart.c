/* user code begin include */

#include "bsp_uart.h"

/* user code end include*/

/* user code begine PV*/
uint8_t rx_buf[RX_BUF_SIZE];
uint8_t tx_buf[TX_BUF_SIZE];
uint8_t process_buf[RX_BUF_SIZE];  //将rx_buf接收到的字节拷贝到process_buf
uint16_t recive_len;
/* user code end PV*/

/* user code begin */

//进入空闲中断处理函数
/**
 * @brief Construct a new hal uart idle irqhandler object 
 * 
 * @param huart 
 */
void HAL_UART_IDLE_IRQHandler(UART_HandleTypeDef *huart){
    if(huart->Instance == USART1){
        HAL_UART_DMAStop(&huart1);
        bsp_bluetooth_commond();
        recive_len = RX_BUF_SIZE - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
        memcpy(process_buf,rx_buf,recive_len);
        process_buf[recive_len] = '\0';
        HAL_UART_Transmit_DMA(&huart1 , process_buf , recive_len );//发送接收到的数据
        //重新启动dma接收数据
        HAL_UART_Receive_DMA(&huart1 , rx_buf,RX_BUF_SIZE);
    }
}

/**
 * @brief 通过dma使用蓝牙串口发送数据
 * 
 * @param tx_blue_buf 将要发送的数据
 */
void bsp_blue_send(uint8_t* tx_blue_buf){
    HAL_UART_Transmit_DMA(&huart1 , tx_blue_buf , sizeof(tx_buf));
}

/**
 * @brief 接收数据包，数据包包头是@包尾是/n换行符,并对符合的数据包进行处理
 * 
 */
void bsp_blue_recive_packet(uint8_t * rx_buf , uint8_t len){
    if(rx_buf[0] == '@' && rx_buf [len - 1] == '\n' /*&& rx_buf [len - 2] == 'r'*/){
        bsp_blue_send(rx_buf);
    }
}

/**
 * @brief 接收串口的命令并作出反应
 * 
 */
void bsp_bluetooth_commond(){
     if(rx_buf[0] == 0x11){
        car_stright();
     }else if(rx_buf[0] == 0x22){
        car_right();
     }else if(rx_buf[0] == 0x33){
        car_left();
     }else if(rx_buf[0] == 0x44){
        car_back();
     }else if(rx_buf[0] == 0x55){
        car_still();
     }
}

/* user code end */