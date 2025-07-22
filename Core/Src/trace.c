#include "trace.h"

uint8_t trace_data[7] = {0};

/**
 * @brief 提取串口接收到的数据
* 
 * @param uart_data 串口数据
 */
void Trace_Data_analyse(uint8_t* uart_data){
    for(uint8_t i = 1 ; i < 7 ; i ++){
        if (commond_buffer[5*i] == '0'){
            trace_data[i-1] = 0;
        }else{
            trace_data[i-1] = 1;
        }
    }
}