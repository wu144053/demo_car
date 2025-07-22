#ifndef _BSP_MONTER_H_
#define _BSP_MONTER_H_

#include "tim.h"

typedef struct 
{
    float ki ;
    float kp ;
    int16_t kd ;
    int16_t Acture;
    int16_t Target;
    int16_t Error;
    int16_t Output;
    /* data */
}Pid_InitTypedef;
#define LEFT 0
#define RIGHT 1

extern int16_t Error_left_int,Error_right_int;

extern Pid_InitTypedef speed_left_pid;
extern Pid_InitTypedef location_pid;
extern Pid_InitTypedef speed_right_pid;

void car_speed_set(int16_t monter_pwm);
void car_left();
void car_right();
void car_back();
void car_stright();
void car_still();
void Speed_Pid(int16_t speed,Pid_InitTypedef* car_pid,uint32_t channel,uint16_t wheels);
void Speed_pid_init();
void car_pid_speed(int16_t car_pid_out,int16_t * monter_pwm);
void location_pid_control(int16_t location_count,Pid_InitTypedef * car_pid);
void location_pid_init();
void car_set_left_pwm(int16_t PWM,uint32_t CHANNEL);
void car_set_right_pwm(int16_t PWM,uint32_t CHANNEL);
#endif // !_BSP_MONTER_H_
