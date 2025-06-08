#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"
#include "tim.h"


/* user code define begin*/
#define MOVE_FORWARD 0
#define STILL 1
#define BACKWARD 2

/* user code define end */
/**
 * @brief 电机调速
 * 
 * @param monter_pwm  pwm占空比 范围是0-1000
 */
void car_speed_set(uint16_t monter_pwm){
    __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,monter_pwm);
}

void left_wheel(uint16_t status){
    if(status == MOVE_FORWARD ){
        HAL_GPIO_WritePin(GPIOA,monter_left_1_Pin,SET);
        HAL_GPIO_WritePin(GPIOA,monter_left_2_Pin,RESET);
    }else if(status == STILL){
        HAL_GPIO_WritePin(GPIOA,monter_left_1_Pin,RESET);
        HAL_GPIO_WritePin(GPIOA,monter_left_2_Pin,RESET);
    }else if(status == BACKWARD){
        HAL_GPIO_WritePin(GPIOA,monter_left_2_Pin,RESET);
        HAL_GPIO_WritePin(GPIOA,monter_left_1_Pin,SET);
    }
}

void right_wheel(uint16_t status){
    if(status == MOVE_FORWARD){
        HAL_GPIO_WritePin(GPIOA,monter_right_1_Pin,SET);
        HAL_GPIO_WritePin(GPIOA,monter_right_2_Pin,RESET);
    }else if(status == STILL){
        HAL_GPIO_WritePin(GPIOA,monter_right_2_Pin,RESET);
        HAL_GPIO_WritePin(GPIOA,monter_right_2_Pin,RESET);
    }else if(status == BACKWARD){
        HAL_GPIO_WritePin(GPIOA,monter_right_1_Pin,RESET);
        HAL_GPIO_WritePin(GPIOA,monter_right_2_Pin,SET);
    }
}

/**
 * @brief 小车左转
 * 
 */
void car_left(){
    left_wheel(MOVE_FORWARD);
    right_wheel(STILL);
}

/**
 * @brief 小车右转
 * 
 */
void car_right(){
    left_wheel(STILL);
    right_wheel(MOVE_FORWARD);
}

/**
 * @brief 小车后退 
 * 
 */
void car_back(){
    left_wheel(BACKWARD);
    right_wheel(BACKWARD);
}

/**
 * @brief 小车直行
 * 
 */
void car_stright(){
    left_wheel(MOVE_FORWARD);
    right_wheel(MOVE_FORWARD);
}

void car_still(){
    left_wheel(STILL);
    right_wheel(STILL);
}