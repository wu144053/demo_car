#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"
#include "tim.h"
#include "bsp_monter.h"

/* user code define begin*/
#define MOVE_FORWARD 0
#define STILL        1
#define BACKWARD     2
#define LEFT 0
#define RIGHT 1

Pid_InitTypedef speed_left_pid;
Pid_InitTypedef location_pid;
Pid_InitTypedef speed_right_pid = {
    .ki     = 3,
    .kp     = 30,
    .Target = 60,
    .kd     = 0.6,
};

/* user code define end */
/**
 * @brief 电机调速
 *
 * @param monter_pwm  pwm占空比 范围是0-1000
 */
void car_speed_set(int16_t monter_pwm)
{
    // if(monter_pwm > 0){
    //     car_stright();
    // }else if (monter_pwm < 0){
    //     car_back();
    // }
    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_3, monter_pwm);
}

/**
 * @brief pid调节小车的速度
 *
 * @param car_pid_out 小车的pid速度输出
 * @param monter_pwm 小车的电机pwm
 */
void car_pid_speed(int16_t car_pid_out, int16_t *monter_pwm)
{
    *monter_pwm += car_pid_out;
    if (*monter_pwm <= 0) {
        *monter_pwm = 0;
    } else if (*monter_pwm >= 1000) {
        *monter_pwm = 1000;
    }
    car_speed_set(*monter_pwm);
}

void left_wheel(uint16_t status)
{
    if (status == MOVE_FORWARD) {
        HAL_GPIO_WritePin(GPIOA, monter_left_1_Pin, SET);
        HAL_GPIO_WritePin(GPIOA, monter_left_2_Pin, RESET);
    } else if (status == STILL) {
        HAL_GPIO_WritePin(GPIOA, monter_left_1_Pin, RESET);
        HAL_GPIO_WritePin(GPIOA, monter_left_2_Pin, RESET);
    } else if (status == BACKWARD) {
        HAL_GPIO_WritePin(GPIOA, monter_left_2_Pin, SET);
        HAL_GPIO_WritePin(GPIOA, monter_left_1_Pin, RESET);
    }
}

void right_wheel(uint16_t status)
{
    if (status == MOVE_FORWARD) {
        HAL_GPIO_WritePin(GPIOA, monter_right_1_Pin, SET);
        HAL_GPIO_WritePin(GPIOA, monter_right_2_Pin, RESET);
    } else if (status == STILL) {
        HAL_GPIO_WritePin(GPIOA, monter_right_2_Pin, RESET);
        HAL_GPIO_WritePin(GPIOA, monter_right_2_Pin, RESET);
    } else if (status == BACKWARD) {
        HAL_GPIO_WritePin(GPIOA, monter_right_1_Pin, RESET);
        HAL_GPIO_WritePin(GPIOA, monter_right_2_Pin, SET);
    }
}

/**
 * @brief 小车左转
 *
 */
void car_left()
{
    left_wheel(MOVE_FORWARD);
    right_wheel(STILL);
}

/**
 * @brief 小车右转
 *
 */
void car_right()
{
    left_wheel(STILL);
    right_wheel(MOVE_FORWARD);
}

/**
 * @brief 小车后退
 *
 */
void car_back()
{
    left_wheel(BACKWARD);
    right_wheel(BACKWARD);
}

/**
 * @brief 小车直行
 *
 */
void car_stright()
{
    left_wheel(MOVE_FORWARD);
    right_wheel(MOVE_FORWARD);
}

void car_still()
{
    left_wheel(STILL);
    right_wheel(STILL);
}

void car_set_left_pwm(int16_t PWM,uint32_t CHANNEL)
{
    if (PWM > 0) {
        HAL_GPIO_WritePin(GPIOA, monter_left_1_Pin, SET);
        HAL_GPIO_WritePin(GPIOA, monter_left_2_Pin, RESET);
        __HAL_TIM_SetCompare(&htim2,CHANNEL, PWM);
    } else {
        HAL_GPIO_WritePin(GPIOA, monter_left_1_Pin, RESET);
        HAL_GPIO_WritePin(GPIOA, monter_left_2_Pin, SET);
        __HAL_TIM_SetCompare(&htim2, CHANNEL, -PWM);
    }
}

/**
 * @brief 设置右轮PWM
 * 
 * @param PWM 
 * @param CHANNEL 
 */
void car_set_right_pwm(int16_t PWM,uint32_t CHANNEL){
    if(PWM > 0){
        HAL_GPIO_WritePin(GPIOA,monter_right_1_Pin,SET);
        HAL_GPIO_WritePin(GPIOA,monter_right_2_Pin,RESET);
        __HAL_TIM_SetCompare(&htim2,CHANNEL,PWM);
    }else{
        HAL_GPIO_WritePin(GPIOA,monter_right_2_Pin,SET);
        HAL_GPIO_WritePin(GPIOA,monter_right_1_Pin,RESET);
        __HAL_TIM_SetCompare(&htim2,CHANNEL,-PWM);
    }
}
/**
 * @brief 速度环初始化
 *
 */
void Speed_pid_init()
{
    speed_left_pid.ki     = 3;
    speed_left_pid.kp     = 30;
    speed_left_pid.Target = 40;
    speed_left_pid.kd     = 0.6;
}

int16_t Error_left_int,Error_right_int;

/**
 * @brief pid速度环控制
 *
 * @param speed 将要调控的速度
 */
void Speed_Pid(int16_t speed,Pid_InitTypedef* car_pid,uint32_t channel,uint16_t wheels)
{
    static int16_t Error_left_0,Error_right_0;
    static int16_t Error_left_1,Error_right_1;
    //static int16_t Error_left_int,Error_right_int;
    static int16_t Error_right_filterling,Error_left_filterling;
    
    int16_t *pError0   = (wheels == 0)?&Error_left_0:&Error_right_0;
    int16_t *pError1   = (wheels == 0)?&Error_left_1:&Error_right_1;
    int16_t *pErrorint = (wheels == 0)?&Error_left_int:&Error_right_int;
    int16_t *filterling = (wheels == 0)?&Error_left_filterling:&Error_right_filterling;
    // int16_t car_pwm = __HAL_TIM_GET_COMPARE(&htim2,TIM_CHANNEL_3);
    car_pid->Acture = speed;
    *pError1           = *pError0;
    *pError0           = car_pid->Target - car_pid->Acture;
    
    /* 输入滤波 */
    *filterling = (0.7)*(*pError0) + (0.3)*(*pError1);

    /* 积分分离 */
    // if(*pError0 > 3 || *pError0 < -3){
        *pErrorint += *pError0;
    // }else{
    //     *pError0 *=0.9;
    // }
    
    /*积分限幅*/
    if (*pErrorint >= 400) {
        *pErrorint = 400;
    }else if(*pErrorint <= -500){
        *pErrorint = -500;
    }
    car_pid->Output = (int16_t)(car_pid->kp * *pError0/*(*filterling)*/ + car_pid->ki * *pErrorint + car_pid->kd * (*pError0 - *pError1)) ;
    // if(*pError0 > 10){
    //    car_pid->Output = (int16_t)(car_pid->kp * *pError0/*(*filterling)*/ + car_pid->ki * *pErrorint + car_pid->kd * (*pError0 - *pError1)) + 200;
    // }else if(*pError0 < -10){
    //     car_pid->Output = (int16_t)(car_pid->kp * (*filterling) + car_pid->ki * *pErrorint + car_pid->kd * (*pError0 - *pError1)) - 200;
    // }else {
    //    car_pid->Output = (int16_t)(car_pid->kp * (*filterling) + car_pid->ki * *pErrorint + car_pid->kd * (*pError0 - *pError1)) ;
    // }
    // if(car_pid.Output < 0){
    //      car_pid.Output = 0;
    //  }else
    /*输出限幅 */
    if (car_pid->Output > 500) {
        car_pid->Output = 500;
    }
    if (car_pid->Output < -500) {
        car_pid->Output = -500;
    }
    if(wheels == 0){
        car_set_left_pwm(car_pid->Output,channel);
    }else {
        car_set_right_pwm(car_pid->Output,channel);
    }
}

/**
 * @brief 位置环初始化
 *
 */
void location_pid_init()
{
    location_pid.ki     = 0.01;
    location_pid.kp     = 5;
    location_pid.kd     = 1;
    location_pid.Target = 500;
}

/**
 * @brief 外环控制pid位置环
 *
 * @param location_count
 */
void location_pid_control(int16_t location_count,Pid_InitTypedef* car_pid)
{
    static float error_loc0;
    static float error_loc1;
    static float error_locin;
    error_loc1 = error_loc0;
    car_pid->Acture += location_count;
    error_loc0 = (float)(car_pid->Target - car_pid->Acture);
    // 设置积分死区
    if (error_loc0 < 200 && error_loc0 > -200 && speed_left_pid.Acture < 30 && speed_left_pid.Acture > -30) {
        error_locin += error_loc0 * 0.5;
    }
    // 积分限幅
    if (error_locin >= 30) {
        error_locin = 30;
    } else if (error_locin < -30) {
        error_locin = -30;
    }
    //
    if (error_loc0 > 200 || error_loc0 < -200) {
        car_pid->Output = error_loc0 * car_pid->kp + error_locin * car_pid->ki + (error_loc0 - error_loc1) * (car_pid->kd);
    }
    if (car_pid->Output >= 90) {
        car_pid->Output = 90;
    } else if (car_pid->Output <= -90) {
        car_pid->Output = -90;
    }
    if (error_loc0 < 200 && error_loc0 > -200) {
        car_pid->Output = error_loc0 * 0.1 + error_locin * car_pid->ki /*+ (error_loc0 - error_loc1)*(car_pid->kd)*/;
        if (car_pid->Output >= 40) {
            car_pid->Output = 40;
        } else if (car_pid->Output <= -40) {
            car_pid->Output = -40;
        }
    }
}