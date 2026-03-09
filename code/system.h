#include "zf_common_headfile.h"
#ifndef CODE_SYSTEM_H_
#define CODE_SYSTEM_H_

#define MOTORA_PWM_PIN ATOM1_CH7_P02_7      //左电机pwm引脚
#define MOTORA_DIR_PIN P02_6               //左电机方向引脚
#define MOTORB_PWM_PIN ATOM1_CH5_P02_5    //右电机pwm引脚
#define MOTORB_DIR_PIN P02_4             //右电机方向引脚
#define SEVER_PWM_PIN ATOM0_CH1_P33_9   //舵机pwm引脚
#define SEVER_CENTER   740             //舵机中值
#define SEVER_LEFT_MAX   300          //舵机左极限值
#define SEVER_RIGHT_MAX  700         //舵机右极限值






void all_init(void);        //总初始化函数
void motor_init(void);     //电机初始化函数
void sever_init(void);    //舵机初始化函数
void encoder_init(void); //编码器初始化函数
void time_init(void);   //定时器初始化函数
#endif /* CODE_SYSTEM_H_ */
