//c文件

#include "zf_common_headfile.h" // 包含自定义的头文件，提供一些通用的宏定义和函数声明
#include "PID_LQR.h" // 包含 PID 和 LQR 控制的头文件，定义了一些结构体和变量

float speed1, speed2, speed3, startflag = 0; // 定义速度变量和起始标志位
float zhengspeed = 0, wangzhi1 = 0, wangzhi2 = 0, k1 = 0, k2 = 0, speedk = 5; // 定义正向速度、期望值和比例系数等变量
float zhili_out; // 直立控制输出变量
int A = -10, B = 10; // 定义 A 和 B 变量，用于限幅
int t=0;
int facheflag = 0; // 发车标志位
float turn_pwm,get_angle=0;
// 定义 pid2 结构体，包含角度环和角速度环的 PID 控制参数
pid_param_t P_turn_pid = {0.5 ,  0    ,  0     , 100    , 0,0,0,0,0,0,0};  //275.0 1.0 0 200
struct pid_MW pid2 = {
    .speed_p = -0.3,   // 速度环P
    .speed_I = 0,  // 速度环I
    .speed_D = 0.,      // 速度环D
    .angle_p = 4.8,       // 角度环P
    .angle_d = 0.2,          // 角度环D
    .angle_i = 0.,           // 角度环I
    .gyro_P = 0.315,          // 角速度环P
    .gyro_i = 0.70,           // 角速度环I
    .gyro_d = 0,               // 角速度环D
    .turn_pspeedk = 0, // 转向 P
    .turn_dspeedk = 0,  // 转向 D
    .turn_p = 0,         // 转向PID_P
    .turn_i = 0,          // 转向 PID I
    .turn_ilimit = 0,      // 转向 i限幅
    .turn_iaim = 0,         // 转向 PID 的目标积分
    .turn_d = 0,             // 转向 PID D
    .yawan_p1 = 0,  // 航向角 PID P
    .yawan_p2 = 0.0, // 航向角 PID P
    .yawan_aim1 = 0,  // 航向角 PID 的目标值1
    .yawan_aim2 = 0,   // 航向角 PID 的目标值2
    .yawan_max = 0.00,  // 航向角 PID 的最大值
    .yawan_min = 0.00,   // 航向角 PID 的最小值
    .turnspeed_p = 0,     // 转向速度 PID P
    .turnspeed_i = 0,      // 转向速度 PID I
    .aimgyro = 0,           // 目标角速度
    .balance_A = 1.1,  // 平衡 A
    .balancelime = 0, // 平衡时间
    .balancelk = 0.00, // 平衡比例系数
    .qiangjing = 0,     // 请进值
    .motor_die = 550,    //死区
    .aim_velo=0,
    . velo_p=0,
     . velo_i=0,
    . velo_d=0,
     . velo_out=0,
};


//--------------------------------------------------------------
// @brief     速度环 PID
// @param     Ecount 转速（编码器值）
// @return    void 没有返回值
// @note      最后所得为输出，在结构体 pid2 中可以参考相应注释。
//--------------------------------------------------------------
void pid2_speed()
{
    static float error, error_last, pid2_error_i = 0; // 定义静态变量，用于保存上一次的误差和积分值
    // 得到 PI 值
    error = speed1 +speed2 ; // 计算当前速度与目标速度之间的误差
    pid2_error_i += error; // 积分项累加
    pid2_error_i = range(pid2_error_i, -5000, 5000); // 限幅处理
    // PID 运算
    pid2.speedout = pid2.speed_p * error + pid2.speed_I * (pid2_error_i) + pid2.speed_D * (error - error_last);
    error_last = error; // 保存当前误差，供下一次使用
    pid2.speedout=range(pid2.speedout, -250, 250);
}

//--------------------------------------------------------------
// @brief     角度环 PD
// @param     void 没有参数
// @return    void 没有返回值
// @note      最后所得为输出，在结构体 pid2 中可以参考相应注释。
//--------------------------------------------------------------
volatile float error_p1, angle_p_new, angle_d_new, increase_sin;
void pid2_angle(void)
{
    static float error_p1_last, error_pi; // 定义静态变量，用于保存上一次的误差和积分值
    // 得到 PI 值，并限幅 I 值
    error_p1 = (pid2.speedout + pid2.balance_A - imu.pitch); // 计算角度环误差
    // PID 运算，D 采用陀螺仪单位换算后的角速度
    pid2.angleout = pid2.angle_p * error_p1 + pid2.angle_d * (error_p1 - error_p1_last) + error_pi * pid2.angle_i;
    error_p1_last = error_p1; // 保存当前误差，供下一次使用
    error_pi += error_p1; // 积分项累加
    error_pi = range(error_pi, -5000, 5000); // 限幅积分项
    // 对偏差进行变 P
    // 限幅，得到 PWM 值
    pid2.angleout = range(pid2.angleout, -20040, 20040);


}

//--------------------------------------------------------------
// @brief     角速度环 PI
// @param     void 没有参数
// @return    void 没有返回值
// @note      最后所得为输出，在结构体 pid2 中可以参考相应注释。
//--------------------------------------------------------------
volatile float pid2_gyro_error_i = 0; // 角速度环积分

void pid2_gyro(void)
{
    static float error_p; // 定义静态变量，用于保存上一次的误差
    static float error_p_last, pwm; ///,turni, pwm; // 定义静态变量，用于保存上一次的误差、积分值和 PWM 值
    static int z_P=2;
    // 得到 PI，并限幅
    error_p = pid2.angleout - imu.deg_s.x; // 计算角速度环误差
   // error_p = -imu.deg_s.x; // 计算角速度环误差
    pid2_gyro_error_i += error_p; // 积分项累加
    pid2_gyro_error_i = range(pid2_gyro_error_i, -8000, 8000); // 限幅积分项
    // PID 运算
    pid2.gyro_out = pid2.gyro_P * error_p + pid2.gyro_i * pid2_gyro_error_i + pid2.gyro_d * (error_p - error_p_last);
    pid2.gyro_out = range(pid2.gyro_out, -8000, 8000); // 限幅输出
    error_p_last = error_p; // 保存当前误差，供下一次使用
    pwm = pid2.gyro_out; // 获取 PWM 值

    t=z_P*imu.deg_s.z+0;
    t=range(t,-2000,2000);
    if(pwm>0)
    {
        pwm = pwm + t;
    swing_control(-1500,750+pwm);
    }else if(pwm<0)
    {
        pwm = pwm - t;
        swing_control(-1500,-750+pwm);

    }


   /* // 控制电机运动方向
    float moto1, moto2;
    //注意这里后期闭环之后pid2.qiangjing应该不要，应该只用速度环计算出来的pid2.velo_out
    moto2 = pid2.qiangjing - pwm+  pid2.velo_out;
    moto1 = pid2.qiangjing + pwm+  pid2.velo_out;
    moto1 = range(moto1, -9999 + pid2.motor_die, 9999 - pid2.motor_die);
    moto2 = range(moto2, -9999 + pid2.motor_die, 9999 - pid2.motor_die);
    if (moto1 > 0)
    {
        pwm_set_duty(ATOM0_CH2_P21_4, pid2.motor_die + moto1);
        gpio_set_level(P21_5, 0); // 向前向左
    }
    else
    {
        pwm_set_duty(ATOM0_CH2_P21_4, pid2.motor_die - moto1);
        gpio_set_level(P21_5, 1); // 向后向右
    }
    if (moto2 > 0)
    {
        pwm_set_duty(ATOM1_CH0_P21_2, pid2.motor_die + moto2);
        gpio_set_level(P21_3, 0); // 向前向右
    }
    else
    {
        pwm_set_duty(ATOM1_CH0_P21_2, pid2.motor_die - moto2);
        gpio_set_level(P21_3, 1); // 向后向左
    }*/
}

volatile float error_velo,error_velo_last,error_velo_i;
void pid_velo()           // 速度闭环上坡的关键
{

    error_velo=pid2.aim_velo+(speed1-speed2);
    error_velo_i+=error_velo;
    error_velo_i=range(error_velo_i,-8000,8000);
    pid2.velo_out=error_velo*pid2.velo_p+error_velo_i*pid2.velo_i;
    pid2.velo_out=range(pid2.velo_out,-5000,5000);
}
//--------------------------------------------------------------
// @brief     PID 控制总函数
// @param     void 没有参数
// @return    void 没有返回值
// @note      最后所得为输出，在结构体 pid2 中可以参考相应注释。
//--------------------------------------------------------------
int WDNM = 0, WCNM = 0, WRNM = 0; // 定义计数变量

void pidget()
{

    if(facheflag==0&&imu.pitch<20&&imu.pitch>-20)//发车标志位和角度保护
    {
        WDNM++;
        WCNM++;
        WRNM++;
        if (WDNM == 2)
        {
            WDNM = 0;
            pid2_gyro(); // 角速度环 PID
            turn_pwm=PidLocCtrl(&P_turn_pid,get_angle);
        }
        if (WCNM == 10)
        {
            WCNM = 0;
            pid2_angle(); // 角度环 PD
        }
        if (WRNM == 100)
        {
            WRNM = 0;
            pid2_speed(); // 速度环 PID
            pid_velo();//前进速度闭环
            encoder_clear_count(TIM2_ENCODER);
            encoder_clear_count(TIM5_ENCODER);
        }
    }
    else
    {
        // 如果不满足发车条件，停止电机
        swing_control(0,0);
    }
}




