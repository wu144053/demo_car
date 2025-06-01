#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"
#include "tim.h"

/**
 * @brief 电机调速
 * 
 * @param monter_pwm  pwm占空比 范围是0-1000
 */
void car_speed_set(uint16_t monter_pwm){
    __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,monter_pwm);
}
