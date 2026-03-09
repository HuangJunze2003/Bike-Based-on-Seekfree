/*********************************************************************************************************************
* TC264 Opensourec Library 即（TC264 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC264 开源库的一部分
*
* TC264 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          cpu0_main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.4
* 适用平台          TC264D
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-09-15       pudding            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"
#include "zf_device_tld7002.h"
#include "zf_device_dot_matrix_screen.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
// 本例程是开源库空工程 可用作移植或者测试各类内外设
const char  temp_string[] = "manba out!";

uint32      stime;
uint8       pit_10ms_flag;
uint8       pit_500ms_flag;
uint8       duty_dir = 1;       // 占空比改变的方向
uint8       display_mode = 3;   // 显示模式 0:轮流将4个模式进行显示  1：依次显示OK 、NG、 A1、 B2  2：显示字符666，并带有呼吸效果 3：显示字符888，并带有闪烁效果  4：依次显示取模中所有的字符
uint16      led_duty = 1500;    // 呼吸灯模式时 控制点阵亮度

// **************************** 代码区域 ****************************


extern float speed1;
extern float speed2;

void display_example1(void);
void display_example2(void);
void display_example3(void);
void display_example4(void);

void pit_10ms_isr(void)
{
    key_scanner();
    stime++;
    pit_10ms_flag = 1;

    if(0 == (stime % 50))
    {
        pit_500ms_flag = 1;
    }

    if(KEY_SHORT_PRESS == key_get_state(KEY_1))
    {
        key_clear_state(KEY_1);
        display_mode = 1;
        stime = 0;
    }
    else if(KEY_SHORT_PRESS == key_get_state(KEY_2))
    {
        key_clear_state(KEY_2);
        display_mode = 2;
        stime = 0;
    }
    else if(KEY_SHORT_PRESS == key_get_state(KEY_3))
    {
        key_clear_state(KEY_3);
        display_mode = 3;
        stime = 0;
    }
    else if(KEY_SHORT_PRESS == key_get_state(KEY_4))
    {
        key_clear_state(KEY_4);
        display_mode = 4;
        stime = 0;
    }
}



int core0_main(void)
{
    clock_init();                   // 获取时钟频率<务必保留>
    debug_init();                   // 初始化默认调试串口
    // 此处编写用户代码 例如外设初始化代码等
    all_init();
    gpio_init(P21_4, GPO, 1, GPO_PUSH_PULL);
    //swing_control(0,800);
    system_delay_ms(100);           // 适当的延时后在进行初始化
    key_init(10);                   // 初始化按键，按键扫描程序调用周期为10ms
    dot_matrix_screen_init();       // 点阵屏幕初始化
    pit_ms_init(CCU60_CH0, 10);     // 周期定时器初始化

    // 此处编写用户代码 例如外设初始化代码等
    cpu_wait_event_ready();         // 等待所有核心初始化完毕
    while (TRUE)
    {
       // printf("%f\r\n",imu.pitch);
        speed1 = encoder_get_count(TIM2_ENCODER);
        speed2 = encoder_get_count(TIM5_ENCODER);

//        printf("%f,%f,%f\r\n",speed1,speed2,pid2.speedout);
//        // 此处编写需要循环执行的代码
//        ips200_show_float(20, 0, imu.pitch, 2, 3);
//        ips200_show_float(20, 20, imu.yaw, 2, 3);
//        ips200_show_float(20,40,pid2.speedout,2,3);
//        ips200_show_float(20,60,speed1,2,3);
//        ips200_show_float(20,80,speed2,2,3);

       // swing_control(0,1500);
       // printf("%f\r\n",speed2);

        // 此处编写需要循环执行的代码
        switch(display_mode)
                {
                    case 1:
                    {
                        display_example1();
                    }break;

                    case 2:
                    {
                        display_example2();
                    }break;

                    case 3:
                    {
                        display_example3();
                    }break;

                    case 4:
                    {
                        display_example4();
                    }break;

                    default:
                    {
                        // 轮流显示4个模式
                        if(200 > (stime%2600))
                        {
                            display_example1();
                        }
                        else if(600 > (stime%2600))
                        {
                            display_example2();
                        }
                        else if(800 > (stime%2600))
                        {
                            display_example3();
                        }
                        else if(2600 > (stime%2600))
                        {
                            display_example4();
                        }
                    }
                }
    }
}

void display_example1(void)
{
    // 设置点阵亮度
    dot_matrix_screen_set_brightness(5000);

    // 依次显示OK 、NG、 A1、 B2
    if(0 == (stime%200))
    {
        dot_matrix_screen_show_string("OK ");
    }
    else if(50 == (stime%200))
    {
        dot_matrix_screen_show_string("NG ");
    }
    else if(100 == (stime%200))
    {
        dot_matrix_screen_show_string("A1 ");
    }
    else if(150 == (stime%200))
    {
        dot_matrix_screen_show_string("B2 ");
    }
}

void display_example2(void)
{
    // 显示字符 666
    dot_matrix_screen_show_string("666");

    if(1 == pit_10ms_flag)
    {
        pit_10ms_flag = 0;

        if(duty_dir)
        {
            led_duty += 50;
            if(9500 < led_duty)
            {
                duty_dir = 0;
            }
        }
        else
        {
            led_duty -= 50;
            if(1500 > led_duty)
            {
                duty_dir = 1;
            }
        }
        // 设置点阵亮度
        dot_matrix_screen_set_brightness(led_duty);
    }
}

void display_example3(void)
{
    // 显示字符 888
    dot_matrix_screen_show_string("888");

    if(0 == (stime%100))
    {
        // 设置点阵亮度
        dot_matrix_screen_set_brightness(9500);
    }
    else if(50 == (stime%100))
    {
        // 设置点阵亮度
        dot_matrix_screen_set_brightness(1500);
    }
}

void display_example4(void)
{
    static uint8 temp_position = 0;

    if(pit_500ms_flag)
    {
        dot_matrix_screen_set_brightness(5000);

        pit_500ms_flag = 0;

        // 显示字符
        dot_matrix_screen_show_string(&temp_string[temp_position]);
        temp_position++;

        if((temp_position + 3) >= sizeof(temp_string))
        {
            temp_position = 0;
        }
    }
}

#pragma section all restore


// **************************** 代码区域 ****************************
