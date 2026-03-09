/*
 * imagespro.h
 *
 *  Created on: 2024年4月8日
 *      Author: pq
 */

#ifndef CODE_PID_LQR_H_
#define CODE_PID_LQR_H_

#include "zf_common_headfile.h" // 包含通用头文件

// 定义宏函数，用于取最大值和最小值
#define max(a, b)        (a>b? a:b)  //限幅处理
#define min(a, b)        (a<b? a:b)
#define range(x, a, b)   (min(max(x, a), b)) // 限幅函数

// 声明全局变量
extern float speed1, speed2, speed3, speedk, startflag; // 定义右飞轮、左飞轮、行进轮编码器的值
extern int A, B;


#define IPS200_TYPE     (IPS200_TYPE_SPI)


// PID结构体
struct pid_MW
{
    float speedout;     // 速度环输出
    float angleout;     // 角度环输出
    float gyro_out;     // 角速度环输出

    // 速度环参数
    float speed_p;
    float speed_I;
    float speed_D;

    // 角度环参数
    float angle_p;
    float angle_d;
    float angle_i;

    // 角速度环参数
    float gyro_P;
    float gyro_i;
    float gyro_d;

    // 平衡角
    float balance_A;
    float balancelime;
    float balancelk;
    float turn_increase;

    // 转向
    float turn_pspeedk;
    float turn_dspeedk;
    float turn_p;       // 转向外环P
    float turn_i;       // 转向外环i
    float turn_ilimit;
    float turn_iaim;
    float turn_d;
    float yawan_p1;
    float yawan_p2;
    float yawan_aim1;
    float yawan_aim2;
    float yawan_max;
    float yawan_min;
    float turnspeed_p;  // 转向外环P
    float turnspeed_i;  // 转向外环i

    float turn_out;     // 外环输出
    float turnspeed_out; // 外环输出
    float aimgyro;      // 外环输出
    float qiangjing;
    float motor_die;
    float aim_velo;
    float velo_p;
    float velo_i;
    float velo_d;
    float velo_out;
};

struct pid_turn // 偏差改变平衡角转向PID
{
    float turn_p;       // 转向外环P
    float turn_out;     // 外环输出
    float turn_gyro_p; // 角速度内环P
    float turn_gyro_d; // 角速度内环D
    float final_out;    // 转向环输出（改变的平衡角
};

// 声明PID控制器结构体实例
extern struct pid_motor pid1;
extern struct pid_MW pid2;

// 函数声明
void pid2_speed(void);       // 速度环PID
void pid2_angle(void);       // 角度环PD
void pid2_gyro(void);        // 角速度环PI
void Turn_loop(void);        // 转向环PID
void Turnspeed_loop(void);   // 转向速度环PID
void pidget(void);           // PID控制总函数
void pid_velo(void);           // 速度闭环
#endif /* CODE_PID_LQR_H_ */

