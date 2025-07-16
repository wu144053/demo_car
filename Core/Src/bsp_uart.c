/* user code begin include */

#include "bsp_uart.h"
#include "stdio.h"
#include "stdarg.h"
//#include "stdint.h"

/* user code end include*/

///typedef uint8_t u8 ;
uint8_t g_Amode_Data = 0;
uint8_t g_Dmode_Data = 0;

/* user code begine PV*/
uint8_t rx_buf[RX_BUF_SIZE];
uint8_t tx_buf[TX_BUF_SIZE];
uint8_t process_buf[RX_BUF_SIZE];  //将rx_buf接收到的字节拷贝到process_buf
uint16_t recive_len;
uint8_t send_buf[8];
/* user code begin include */

#include "bsp_uart.h"
#include "stdio.h"
#include "stdarg.h"

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
 * @brief 将整数转换成字符串通过串口dma发送
 * 
 * @param number 需要转换的数字
 */
void bsp_blue_send_number(int32_t number){
    uint8_t buffer[10];
    int length =  sprintf((char*) buffer,"%ld",number);
    HAL_UART_Transmit_DMA(&huart1,buffer,length);
}

/**
 * @brief 通过dma使用蓝牙串口发送数据
 * 
 * @param tx_blue_buf 将要发送的数据
 */
void bsp_blue_send(uint8_t* tx_blue_buf){
    uint16_t i = 0;
    while (tx_blue_buf[i] != '\0')
    {
        i ++;
        
    }
    HAL_UART_Transmit_DMA(&huart1 , tx_blue_buf ,i /*strlen((const char *)tx_buf)+1*/);
}

/**
 * @brief 使用串口发送一个字符串
 * 
 * @param string 
 */
void bsp_uart_string(char * string){
    uint8_t i = 0 ;
    while ( string[i] != '\0')
    {
        i++;
    }
    HAL_UART_Transmit_DMA(&huart1 ,(uint8_t *)string,i);
}

int8_t uart_tx_done = 1;
/**
 * @brief 将串口发送数据格式化
 * 
 * @param format 需要格式化输出的字符串
 * @param ... 
 */
void bsp_Serial_printf(char* format,...){
    while (!uart_tx_done );
    uart_tx_done = 0;
    static char string[100] = {0};
    va_list arg;
    va_start(arg,format);
    vsprintf(string,format,arg);
    va_end(arg);
    bsp_uart_string(string);
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

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        uart_tx_done = 1;
    }
}


void send_control_data(uint8_t adjust,uint8_t aData,uint8_t dData)
{
	uint8_t send_buf[8] = "$0,0,0#";
	if(adjust == 1)//校准命令
	{
		send_buf[1] = '1';
	}
	else
	{
		send_buf[1] = '0';
	}
	if(aData == 1)//模拟值数据
	{
		send_buf[3] = '1';
		g_Amode_Data = 1;
	}
	else
	{
		send_buf[3] = '0';
		g_Amode_Data = 0;
	}
	if(dData == 1)//数字值数据
	{
		send_buf[5] = '1';
		g_Dmode_Data = 1;
	}
	else
	{
		send_buf[5] = '0';
		g_Dmode_Data = 0;
	}
    bsp_blue_send(send_buf);
}

/* user code end */
