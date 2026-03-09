#ifndef _IMAGE_H
#define _IMAGE_H

#include "cpu1_main.h"

//妫版粏澹婄�规矮绠�  閸ョ姳璐熼張澶婂帥娓氬绱濇潻鐐侯杹閼规煡鍏橀弨閫涚瑝閺夈儻绱濋幋鎴犳纯閹恒儲鏂佹潻娆庣啊
#define uesr_RED     0XF800    //缁俱垼澹�
#define uesr_GREEN   0X07E0    //缂佽儻澹�
#define uesr_BLUE    0X001F    //閽冩繆澹�




//鐎瑰繐鐣炬稊锟�
#define image_h	120//閸ユ儳鍎氭妯哄
#define image_w	188//閸ユ儳鍎氱�硅棄瀹�

#define white_pixel	255
#define black_pixel	0

#define bin_jump_num	1//鐠哄疇绻冮惃鍕仯閺侊拷
#define border_max	image_w-2 //鏉堝湱鏅張锟芥径褍锟斤拷
#define border_min	1	//鏉堝湱鏅張锟界亸蹇擄拷锟�
extern uint8 original_image[image_h][image_w];
extern uint8 bin_image[image_h][image_w];//閸ユ儳鍎氶弫鎵矋
extern uint8 l_border[image_h];//左线数组
extern uint8 r_border[image_h];//右线数组
extern uint8 center_line[image_h];//中线数组
extern void image_process(void); //閻╁瓨甯撮崷銊よ厬閺傤厽鍨ㄥ顏嗗箚闁插矁鐨熼悽銊︻劃缁嬪绨亸鍗炲讲娴犮儱鎯婇悳顖涘⒔鐞涘奔绨�

#endif /*_IMAGE_H*/

