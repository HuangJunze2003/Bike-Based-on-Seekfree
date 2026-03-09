#include "zf_common_headfile.h"
#ifndef CODE_CONTROL_H_
#define CODE_CONTROL_H_

typedef enum
{
    motorA,//A电机
    motorB,//B电机
} MOTOR_TYPE;// 电机结构体


void motor_control(MOTOR_TYPE motor,int16 duty);    //电机控制函数
void swing_control(int16 duty,int16 error);        //后轮控制函数
#endif /* CODE_CONTROL_H_ */
