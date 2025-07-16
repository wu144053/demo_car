/* user include begin */
#include "bsp_enconder.h"

/* user include end*/

/* user code begin */

/**
 * @brief  初始化encoder
 * 
 */
void Enconder_init(){
    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_1);//开启定时器3通道1
    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_2);//开启定时器3通道2
    HAL_TIM_Base_Start_IT(&htim3) ; //开启定时器3的中断
    // HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_1);
    // HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_2);
    HAL_TIM_Base_Start_IT(&htim1);
}

/**
 * @brief  获取编码器的tim2编码器的数值
 * 
 * @return int32_t  编码器的数值
 */
int32_t Enconder_Get(TIM_HandleTypeDef* htimxd){
    int32_t counter;
    counter = (int16_t)__HAL_TIM_GetCounter(htimxd);
    return counter;
}


/**
 * @brief 将编码器的数值转换成字符串并通过串口发送出去
 * 
 */
void Enconder_Uart_send(){
    int32_t number;
    number = Enconder_Get(&htim1);
    bsp_blue_send_number(number);
    
}

/* user code end*/
