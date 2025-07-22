/* user code begin include */

#include "bsp_uart.h"
#include "stdio.h"
#include "stdarg.h"
#include "commond.h"
//#include "stdint.h"

/* user code end include*/

///typedef uint8_t u8 ;
uint8_t g_Amode_Data = 0;
uint8_t g_Dmode_Data = 0;

/* user code begine PV*/
uint8_t rx_buf[RX_BUF_SIZE];
uint8_t rx_buf3[RX_BUF_SIZE];
uint8_t tx_buf[TX_BUF_SIZE];
uint8_t process_buf[RX_BUF_SIZE];  //将rx_buf接收到的字节拷贝到process_buf
uint8_t packnew[RX_BUF_SIZE];
uint8_t recive_len;
uint16_t recive3_len;
uint8_t* start_index;
uint8_t stop_index;
uint16_t data_length;//字符长度
uint8_t merge_flag = 0;
int8_t uart_tx_done = 1;
int8_t uart_tx_done1 = 1;
int8_t uart_tx_done2 = 1;
uint8_t commend_buf[30];
//uint8_t send_buf[8];
/* user code begin include */

#include "bsp_uart.h"
#include "stdio.h"
#include "stdarg.h"

/* user code end include*/

/* user code begine PV*/

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
        recive_len = RX_BUF_SIZE - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
        length = Commond_GetCommond_led();  
        Commond_Write(rx_buf,recive_len);
        commond_buffer[length] = '\r';
        commond_buffer[length+1] = '\n';
        if(length != 0){
           //HAL_UART_Transmit_DMA(&huart3 , commond_buffer, length+2);//发送接收到的数据
        }
        //rx_buf[recive_len] = '\0';
        //Commond_GetCommond_led();
        // if(length != 0){
           // HAL_UART_Transmit_DMA(&huart3 , rx_buf ,recive_len) ;//发送接收到的数据
        // }
        //Commond_Write(rx_buf,recive_len);
        memcpy(process_buf,rx_buf,recive_len);
        //process_buf[recive_len] = '\r';
        //process_buf[recive_len + 1] = '\n';
        //HAL_UART_Transmit_DMA(&huart3 , process_buf , recive_len );//发送接收到的数据
        //重新启动dma接收数据
        HAL_UART_Receive_DMA(&huart1 , rx_buf,RX_BUF_SIZE);
    }
    if(huart->Instance == USART3){
        HAL_UART_DMAStop(&huart3);
        recive3_len = RX_BUF_SIZE - __HAL_DMA_GET_COUNTER(huart3.hdmarx);
        rx_buf3[recive3_len] = '\0';
        HAL_UART_Transmit_DMA(&huart3,rx_buf3,recive3_len);
        HAL_UART_Receive_DMA(&huart3,rx_buf3,RX_BUF_SIZE);
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
    //while(HAL_UART_GetState(&huart1)!=HAL_UART_STATE_READY);
    HAL_UART_Transmit_DMA(&huart1 , tx_blue_buf ,i /*strlen((const char *)tx_buf)+1*/);
    //HAL_UART_Transmit(&huart1,tx_buf,i,100);
}

void bsp_uart3_send(uint8_t* tx_blue_buf){
    uint16_t i = 0;
    while (tx_blue_buf[i] != '\0')
    {
        i++;/* code */
    }
    HAL_UART_Transmit_DMA(&huart3,tx_blue_buf,i);
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
    HAL_UART_Transmit_DMA(&huart3 ,(uint8_t *)string,i);
}

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
        //HAL_UART_Receive_DMA(&huart1,rx_buf,RX_BUF_SIZE);
        //uart_tx_done = 1;
        uart_tx_done1 = 1;
        uart_tx_done2 = 1;
        //HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,SET);
    }
    if(huart->Instance == USART3)
    {
        uart_tx_done = 1;    
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if(huart->Instance==USART1){
        //HAL_UART_DMAStop(&huart1);
        //HAL_UART_Transmit_DMA(&huart1,"wujingfe",30);
        //HAL_UART_Receive_DMA(&huart1,rx_buf,30);
        
    }
}

char send_buf[] = "$0,0,0#";

void send_control_data(uint8_t adjust,uint8_t aData,uint8_t dData)
{
    while(!uart_tx_done1);
    uart_tx_done1 = 0;
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
    bsp_blue_send((uint8_t*)send_buf);
}


/* user code end */
