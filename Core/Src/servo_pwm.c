#include "servo_pwm.h"
#include "tim.h"
#include "stm32f1xx_hal.h"
#include"stdint.h"

/**
 * @brief 设置小车的pwm输出值
 * 
 * @param compare 范围在0到100之间
 */
void Servo_PWM_Set(uint16_t compare){
    __HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_3,compare);
}
