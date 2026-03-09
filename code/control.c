#include "control.h"

//电机控制函数
//例： motor_control(motorA,5000);
void motor_control(MOTOR_TYPE motor,int16 duty)
{
    uint8 dir = (duty > 0) ? 1:0;  //根据占空比正负赋予电机旋转方向
    switch(motor)
    {
        case motorA: //左电机
            pwm_set_duty(MOTORA_PWM_PIN,abs(duty)); //赋予左电机占空比
            gpio_set_level(MOTORA_DIR_PIN,dir);//赋予左电机旋转方向
            break;
        case motorB: //右电机
            pwm_set_duty(MOTORB_PWM_PIN,abs(duty)); //赋予右电机占空比
            gpio_set_level(MOTORB_DIR_PIN,dir);//赋予右电机旋转方向
            break;
    }

}


//后轮控制函数
//例：swing_control(1000,Tduty);
int16 duty_A=0;//A电机占空比
int16 duty_B=0;//B电机占空比
void swing_control(int16 duty,int16 error)
{
    int16 duty_dva = 0;//电机差速
    uint8 ori = (error >= 0) ? 1:0; //根据差速判断摆动方向
    duty_dva = abs(error);
    switch(ori)
    {
        case 0:  //向左摆
            duty_A = duty - duty_dva;
            duty_B = duty + duty_dva;
            break;
        case 1:  //向右摆
            duty_A = duty + duty_dva;
            duty_B = duty - duty_dva;
            break;
    }
        motor_control(motorA,duty_A);//赋予A电机占空比
        motor_control(motorB,duty_B);//赋予B电机占空比
}







