#include "stm32f1xx_hal.h"
#include "bsp_init.h"
#include "usart.h"
#include "stm32f1xx_it.h"


/**
 * @brief 板级模块初始化
 * 
 * @note 初始化串口+dma接收数据加idle空闲中断
 */
void bsp_init(){
    HAL_UART_Receive_DMA(&huart1,rx_buf,RX_BUF_SIZE);   //开启串口1dma接收数据
    HAL_UART_Receive_DMA(&huart3,rx_buf3,RX_BUF_SIZE);  //开启串口2dma接收数据
    __HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);         //开启串口1空闲中断
    __HAL_UART_ENABLE_IT(&huart3,UART_IT_IDLE);
}
