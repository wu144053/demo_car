#ifndef _BSP_ENCONDER_H_
#define _BSP_ENCONDER_H_

/* user include begin*/

#include "stm32f1xx_hal.h"
#include "tim.h"
#include "bsp_uart.h"

/* user include end*/

/* user code begin */

void Enconder_Uart_send();
//int32_t Enconder_get(TIM_HandleTypeDef* htimx);
//int32_t Enconder_get(TIM_HandleTypeDef* htimx);
int32_t Enconder_Get(TIM_HandleTypeDef* htimxd);
void Enconder_init();

/* user code end*/

#endif // !BSP_ENCONDER_H_
