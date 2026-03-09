#include "system.h"



#define MOTORA_PWM_PIN ATOM1_CH7_P02_7      //左电机pwm引脚
#define MOTORA_DIR_PIN P02_6               //左电机方向引脚
#define MOTORB_PWM_PIN ATOM1_CH5_P02_5    //右电机pwm引脚
#define MOTORB_DIR_PIN P02_4             //右电机方向引脚
#define SEVER_PWM_PIN ATOM0_CH1_P33_9   //舵机pwm引脚
#define SEVER_CENTER   740             //舵机中值
#define SEVER_LEFT_MAX   300          //舵机左极限值
#define SEVER_RIGHT_MAX  700         //舵机右极限值


//总初始化函数
void all_init(void)
{
    IIR_imu();
    imu660ra_init();
    ips200_init(IPS200_TYPE_PARALLEL8);//2.0寸屏幕双排初始化
    motor_init(); //电机初始化

   // mt9v03x_init();// 摄像头初始化
    sever_init();//舵机初始化

    encoder_quad_init(TIM5_ENCODER, TIM5_ENCODER_CH1_P10_3, TIM5_ENCODER_CH2_P10_1);
    encoder_quad_init(TIM2_ENCODER, TIM2_ENCODER_CH2_P33_6, TIM2_ENCODER_CH1_P33_7);
    pit_ms_init(CCU61_CH1, 1);//编器数据采集
    pit_ms_init(CCU60_CH0, 100);//编码器数据清除
    pit_ms_init(CCU60_CH1, 1);//imu660数据采集
    pit_ms_init(CCU61_CH0, 1);//pid控制器
}

//电机初始化函数
void motor_init(void)
{
    pwm_init(MOTORA_PWM_PIN,500,0);//左电机pwm初始化
    gpio_init(MOTORA_DIR_PIN,GPO,1,GPO_PUSH_PULL);//左电机方向初始化
    pwm_init(MOTORB_PWM_PIN,500,0);//右电机pwm初始化
    gpio_init(MOTORB_DIR_PIN,GPO,1,GPO_PUSH_PULL);//右电机方向初始化

}

//舵机初始化函数
void sever_init(void)
{
    pwm_init(SEVER_PWM_PIN,50,SEVER_CENTER); //舵机初始化在中值位置
}

//编码器初始化函数
void encoder_init(void)
{
    encoder_dir_init(TIM2_ENCODER,TIM2_ENCODER_CH1_P33_7,TIM2_ENCODER_CH2_P33_6);//左编码器初始化
    encoder_dir_init(TIM5_ENCODER,TIM5_ENCODER_CH1_P10_3,TIM5_ENCODER_CH2_P10_1);//右编码器初始化
}

//定时器初始化函数
void time_init(void)
{
    pit_ms_init(CCU60_CH0,1); //1ms周期中断
}
