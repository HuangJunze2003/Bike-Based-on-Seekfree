//-------------------------------------------------------------------------------------------------------------------
//  绠�浠�:鍏偦鍩熷浘鍍忓鐞�

//------------------------------------------------------------------------------------------------------------------
#include "image.h"
extern float get_angle;
float value;
/*
鍑芥暟鍚嶇О锛歩nt my_abs(int value)
鍔熻兘璇存槑锛氭眰缁濆鍊�
鍙傛暟璇存槑锛�
鍑芥暟杩斿洖锛氱粷瀵瑰��
淇敼鏃堕棿锛�2022骞�9鏈�8鏃�
澶�    娉細
example锛�  my_abs( x)锛�
 */
int my_abs(int value)
{
if(value>=0) return value;
else return -value;
}

int16 limit_a_b(int16 x, int a, int b)
{
    if(x<a) x = a;
    if(x>b) x = b;
    return x;
}

/*
鍑芥暟鍚嶇О锛歩nt16 limit(int16 x, int16 y)
鍔熻兘璇存槑锛氭眰x,y涓殑鏈�灏忓��
鍙傛暟璇存槑锛�
鍑芥暟杩斿洖锛氳繑鍥炰袱鍊间腑鐨勬渶灏忓��
淇敼鏃堕棿锛�2022骞�9鏈�8鏃�
澶�    娉細
example锛�  limit( x,  y)
 */
int16 limit1(int16 x, int16 y)
{
	if (x > y)             return y;
	else if (x < -y)       return -y;
	else                return x;
}


/*鍙橀噺澹版槑*/
uint8 original_image[image_h][image_w];
uint8 image_thereshold;//鍥惧儚鍒嗗壊闃堝��
//------------------------------------------------------------------------------------------------------------------
//  @brief      鑾峰緱涓�鍓伆搴﹀浘鍍�
//  @since      v1.0 
//------------------------------------------------------------------------------------------------------------------
void Get_image(uint8(*mt9v03x_image)[image_w])
{
#define use_num		1	//1灏辨槸涓嶅帇缂╋紝2灏辨槸鍘嬬缉涓�鍊�
	uint8 i = 0, j = 0, row = 0, line = 0;
    for (i = 0; i < image_h; i += use_num)          //
    {
        for (j = 0; j <image_w; j += use_num)     //
        {
            original_image[row][line] = mt9v03x_image[i][j];//杩欓噷鐨勫弬鏁板～鍐欎綘鐨勬憚鍍忓ご閲囬泦鍒扮殑鍥惧儚
			line++;
        }
        line = 0;
        row++;
    }
}
//------------------------------------------------------------------------------------------------------------------
//  @brief     鍔ㄦ�侀槇鍊�
//  @since      v1.0 
//------------------------------------------------------------------------------------------------------------------
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
{
#define GrayScale 256
    uint16 Image_Width  = col;
    uint16 Image_Height = row;
    int X; uint16 Y;
    uint8* data = image;
    int HistGram[GrayScale] = {0};
	
	uint32 Amount = 0;
    uint32 PixelBack = 0;
    uint32 PixelIntegralBack = 0;
    uint32 PixelIntegral = 0;
    int32 PixelIntegralFore = 0;
    int32 PixelFore = 0;
    double OmegaBack=0, OmegaFore=0, MicroBack=0, MicroFore=0, SigmaB=0, Sigma=0; // 绫婚棿鏂瑰樊;
    uint8 MinValue=0, MaxValue=0;
    uint8 Threshold = 0;
	
	
    for (Y = 0; Y <Image_Height; Y++) //Y<Image_Height鏀逛负Y =Image_Height锛涗互渚胯繘琛� 琛屼簩鍊煎寲
    {
        //Y=Image_Height;
        for (X = 0; X < Image_Width; X++)
        {
        HistGram[(int)data[Y*Image_Width + X]]++; //缁熻姣忎釜鐏板害鍊肩殑涓暟淇℃伅
        }
    }




    for (MinValue = 0; MinValue < 256 && HistGram[MinValue] == 0; MinValue++) ;        //鑾峰彇鏈�灏忕伆搴︾殑鍊�
    for (MaxValue = 255; MaxValue > MinValue && HistGram[MinValue] == 0; MaxValue--) ; //鑾峰彇鏈�澶х伆搴︾殑鍊�

    if (MaxValue == MinValue)
    {
        return MaxValue;          // 鍥惧儚涓彧鏈変竴涓鑹�
    }
    if (MinValue + 1 == MaxValue)
    {
        return MinValue;      // 鍥惧儚涓彧鏈変簩涓鑹�
    }

    for (Y = MinValue; Y <= MaxValue; Y++)
    {
        Amount += HistGram[Y];        //  鍍忕礌鎬绘暟
    }

    PixelIntegral = 0;
    for (Y = MinValue; Y <= MaxValue; Y++)
    {
        PixelIntegral += HistGram[Y] * Y;//鐏板害鍊兼�绘暟
    }
    SigmaB = -1;
    for (Y = MinValue; Y < MaxValue; Y++)
    {
          PixelBack = PixelBack + HistGram[Y];    //鍓嶆櫙鍍忕礌鐐规暟
          PixelFore = Amount - PixelBack;         //鑳屾櫙鍍忕礌鐐规暟
          OmegaBack = (double)PixelBack / Amount;//鍓嶆櫙鍍忕礌鐧惧垎姣�
          OmegaFore = (double)PixelFore / Amount;//鑳屾櫙鍍忕礌鐧惧垎姣�
          PixelIntegralBack += HistGram[Y] * Y;  //鍓嶆櫙鐏板害鍊�
          PixelIntegralFore = PixelIntegral - PixelIntegralBack;//鑳屾櫙鐏板害鍊�
          MicroBack = (double)PixelIntegralBack / PixelBack;//鍓嶆櫙鐏板害鐧惧垎姣�
          MicroFore = (double)PixelIntegralFore / PixelFore;//鑳屾櫙鐏板害鐧惧垎姣�
          Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//g
          if (Sigma > SigmaB)//閬嶅巻鏈�澶х殑绫婚棿鏂瑰樊g
          {
              SigmaB = Sigma;
              Threshold = (uint8)Y;
          }
    }
   return Threshold;
}
//------------------------------------------------------------------------------------------------------------------
//  @brief      鍥惧儚浜屽�煎寲锛岃繖閲岀敤鐨勬槸澶ф触娉曚簩鍊煎寲銆�
//  @since      v1.0 
//------------------------------------------------------------------------------------------------------------------
uint8 bin_image[image_h][image_w];//鍥惧儚鏁扮粍
void turn_to_bin(void)
{
  uint8 i,j;
 image_thereshold = otsuThreshold(original_image[0], image_w, image_h);
  for(i = 0;i<image_h;i++)
  {
      for(j = 0;j<image_w;j++)
      {
          if(original_image[i][j]>image_thereshold)bin_image[i][j] = white_pixel;
          else bin_image[i][j] = black_pixel;
      }
  }
}


/*
鍑芥暟鍚嶇О锛歷oid get_start_point(uint8 start_row)
鍔熻兘璇存槑锛氬鎵句袱涓竟鐣岀殑杈圭晫鐐逛綔涓哄叓閭诲煙寰幆鐨勮捣濮嬬偣
鍙傛暟璇存槑锛氳緭鍏ヤ换鎰忚鏁�
鍑芥暟杩斿洖锛氭棤
淇敼鏃堕棿锛�2022骞�9鏈�8鏃�
澶�    娉細
example锛�  get_start_point(image_h-2)
 */
uint8 start_point_l[2] = { 0 };//宸﹁竟璧风偣鐨剎锛寉鍊�
uint8 start_point_r[2] = { 0 };//鍙宠竟璧风偣鐨剎锛寉鍊�
uint8 get_start_point(uint8 start_row)
{
	uint8 i = 0,l_found = 0,r_found = 0;
	//娓呴浂
	start_point_l[0] = 0;//x
	start_point_l[1] = 0;//y

	start_point_r[0] = 0;//x
	start_point_r[1] = 0;//y

		//浠庝腑闂村線宸﹁竟锛屽厛鎵捐捣鐐�
	for (i = image_w / 2; i > border_min; i--)
	{
		start_point_l[0] = i;//x
		start_point_l[1] = start_row;//y
		if (bin_image[start_row][i] == 255 && bin_image[start_row][i - 1] == 0)
		{
			//printf("鎵惧埌宸﹁竟璧风偣image[%d][%d]\n", start_row,i);
			l_found = 1;
			break;
		}
	}

	for (i = image_w / 2; i < border_max; i++)
	{
		start_point_r[0] = i;//x
		start_point_r[1] = start_row;//y
		if (bin_image[start_row][i] == 255 && bin_image[start_row][i + 1] == 0)
		{
			//printf("鎵惧埌鍙宠竟璧风偣image[%d][%d]\n",start_row, i);
			r_found = 1;
			break;
		}
	}

	if(l_found&&r_found)return 1;
	else {
		//printf("鏈壘鍒拌捣鐐筡n");
		return 0;
	} 
}

/*
鍑芥暟鍚嶇О锛歷oid search_l_r(uint16 break_flag, uint8(*image)[image_w],uint16 *l_stastic, uint16 *r_stastic,
							uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y,uint8*hightest)

鍔熻兘璇存槑锛氬叓閭诲煙姝ｅ紡寮�濮嬫壘鍙宠竟鐐圭殑鍑芥暟锛岃緭鍏ュ弬鏁版湁鐐瑰锛岃皟鐢ㄧ殑鏃跺�欎笉瑕佹紡浜嗭紝杩欎釜鏄乏鍙崇嚎涓�娆℃�ф壘瀹屻��
鍙傛暟璇存槑锛�
break_flag_r			锛氭渶澶氶渶瑕佸惊鐜殑娆℃暟
(*image)[image_w]		锛氶渶瑕佽繘琛屾壘鐐圭殑鍥惧儚鏁扮粍锛屽繀椤绘槸浜屽�煎浘,濉叆鏁扮粍鍚嶇О鍗冲彲
					   鐗瑰埆娉ㄦ剰锛屼笉瑕佹嬁瀹忓畾涔夊悕瀛椾綔涓鸿緭鍏ュ弬鏁帮紝鍚﹀垯鏁版嵁鍙兘鏃犳硶浼犻�掕繃鏉�
*l_stastic				锛氱粺璁″乏杈规暟鎹紝鐢ㄦ潵杈撳叆鍒濆鏁扮粍鎴愬憳鐨勫簭鍙峰拰鍙栧嚭寰幆娆℃暟
*r_stastic				锛氱粺璁″彸杈规暟鎹紝鐢ㄦ潵杈撳叆鍒濆鏁扮粍鎴愬憳鐨勫簭鍙峰拰鍙栧嚭寰幆娆℃暟
l_start_x				锛氬乏杈硅捣鐐规í鍧愭爣
l_start_y				锛氬乏杈硅捣鐐圭旱鍧愭爣
r_start_x				锛氬彸杈硅捣鐐规í鍧愭爣
r_start_y				锛氬彸杈硅捣鐐圭旱鍧愭爣
hightest				锛氬惊鐜粨鏉熸墍寰楀埌鐨勬渶楂橀珮搴�
鍑芥暟杩斿洖锛氭棤
淇敼鏃堕棿锛�2022骞�9鏈�25鏃�
澶�    娉細
example锛�
	search_l_r((uint16)USE_num,image,&data_stastics_l, &data_stastics_r,start_point_l[0],
				start_point_l[1], start_point_r[0], start_point_r[1],&hightest);
 */
#define USE_num	image_h*3	//瀹氫箟鎵剧偣鐨勬暟缁勬垚鍛樹釜鏁版寜鐞嗚300涓偣鑳芥斁涓嬶紝浣嗘槸鏈変簺鐗规畩鎯呭喌纭疄闅鹃《锛屽瀹氫箟浜嗕竴鐐�

 //瀛樻斁鐐圭殑x锛寉鍧愭爣
uint16 points_l[(uint16)USE_num][2] = { {  0 } };//宸︾嚎
uint16 points_r[(uint16)USE_num][2] = { {  0 } };//鍙崇嚎
uint16 dir_r[(uint16)USE_num] = { 0 };//鐢ㄦ潵瀛樺偍鍙宠竟鐢熼暱鏂瑰悜
uint16 dir_l[(uint16)USE_num] = { 0 };//鐢ㄦ潵瀛樺偍宸﹁竟鐢熼暱鏂瑰悜
uint16 data_stastics_l = 0;//缁熻宸﹁竟鎵惧埌鐐圭殑涓暟
uint16 data_stastics_r = 0;//缁熻鍙宠竟鎵惧埌鐐圭殑涓暟
uint8 hightest = 0;//鏈�楂樼偣
void search_l_r(uint16 break_flag, uint8(*image)[image_w], uint16 *l_stastic, uint16 *r_stastic, uint8 l_start_x, uint8 l_start_y, uint8 r_start_x, uint8 r_start_y, uint8*hightest)
{

	uint8 i = 0, j = 0;

	//宸﹁竟鍙橀噺
	uint8 search_filds_l[8][2] = { {  0 } };
	uint8 index_l = 0;
	uint8 temp_l[8][2] = { {  0 } };
	uint8 center_point_l[2] = {  0 };
	uint16 l_data_statics;//缁熻宸﹁竟
	//瀹氫箟鍏釜閭诲煙
	static int8 seeds_l[8][2] = { {0,  1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1},{1,  0},{1, 1}, };
	//{-1,-1},{0,-1},{+1,-1},
	//{-1, 0},	     {+1, 0},
	//{-1,+1},{0,+1},{+1,+1},
	//杩欎釜鏄『鏃堕拡

	//鍙宠竟鍙橀噺
	uint8 search_filds_r[8][2] = { {  0 } };
	uint8 center_point_r[2] = { 0 };//涓績鍧愭爣鐐�
	uint8 index_r = 0;//绱㈠紩涓嬫爣
	uint8 temp_r[8][2] = { {  0 } };
	uint16 r_data_statics;//缁熻鍙宠竟
	//瀹氫箟鍏釜閭诲煙
	static int8 seeds_r[8][2] = { {0,  1},{1,1},{1,0}, {1,-1},{0,-1},{-1,-1}, {-1,  0},{-1, 1}, };
	//{-1,-1},{0,-1},{+1,-1},
	//{-1, 0},	     {+1, 0},
	//{-1,+1},{0,+1},{+1,+1},
	//杩欎釜鏄�嗘椂閽�

	l_data_statics = *l_stastic;//缁熻鎵惧埌浜嗗灏戜釜鐐癸紝鏂逛究鍚庣画鎶婄偣鍏ㄩ儴鐢诲嚭鏉�
	r_data_statics = *r_stastic;//缁熻鎵惧埌浜嗗灏戜釜鐐癸紝鏂逛究鍚庣画鎶婄偣鍏ㄩ儴鐢诲嚭鏉�

	//绗竴娆℃洿鏂板潗鏍囩偣  灏嗘壘鍒扮殑璧风偣鍊间紶杩涙潵
	center_point_l[0] = l_start_x;//x
	center_point_l[1] = l_start_y;//y
	center_point_r[0] = r_start_x;//x
	center_point_r[1] = r_start_y;//y

		//寮�鍚偦鍩熷惊鐜�
	while (break_flag--)
	{

		//宸﹁竟
		for (i = 0; i < 8; i++)//浼犻��8F鍧愭爣
		{
			search_filds_l[i][0] = center_point_l[0] + seeds_l[i][0];//x
			search_filds_l[i][1] = center_point_l[1] + seeds_l[i][1];//y
		}
		//涓績鍧愭爣鐐瑰～鍏呭埌宸茬粡鎵惧埌鐨勭偣鍐�
		points_l[l_data_statics][0] = center_point_l[0];//x
		points_l[l_data_statics][1] = center_point_l[1];//y
		l_data_statics++;//绱㈠紩鍔犱竴

		//鍙宠竟
		for (i = 0; i < 8; i++)//浼犻��8F鍧愭爣
		{
			search_filds_r[i][0] = center_point_r[0] + seeds_r[i][0];//x
			search_filds_r[i][1] = center_point_r[1] + seeds_r[i][1];//y
		}
		//涓績鍧愭爣鐐瑰～鍏呭埌宸茬粡鎵惧埌鐨勭偣鍐�
		points_r[r_data_statics][0] = center_point_r[0];//x
		points_r[r_data_statics][1] = center_point_r[1];//y

		index_l = 0;//鍏堟竻闆讹紝鍚庝娇鐢�
		for (i = 0; i < 8; i++)
		{
			temp_l[i][0] = 0;//鍏堟竻闆讹紝鍚庝娇鐢�
			temp_l[i][1] = 0;//鍏堟竻闆讹紝鍚庝娇鐢�
		}

		//宸﹁竟鍒ゆ柇
		for (i = 0; i < 8; i++)
		{
			if (image[search_filds_l[i][1]][search_filds_l[i][0]] == 0
				&& image[search_filds_l[(i + 1) & 7][1]][search_filds_l[(i + 1) & 7][0]] == 255)
			{
				temp_l[index_l][0] = search_filds_l[(i)][0];
				temp_l[index_l][1] = search_filds_l[(i)][1];
				index_l++;
				dir_l[l_data_statics - 1] = (i);//璁板綍鐢熼暱鏂瑰悜
			}

			if (index_l)
			{
				//鏇存柊鍧愭爣鐐�
				center_point_l[0] = temp_l[0][0];//x
				center_point_l[1] = temp_l[0][1];//y
				for (j = 0; j < index_l; j++)
				{
					if (center_point_l[1] > temp_l[j][1])
					{
						center_point_l[0] = temp_l[j][0];//x
						center_point_l[1] = temp_l[j][1];//y
					}
				}
			}

		}
		if ((points_r[r_data_statics][0]== points_r[r_data_statics-1][0]&& points_r[r_data_statics][0] == points_r[r_data_statics - 2][0]
			&& points_r[r_data_statics][1] == points_r[r_data_statics - 1][1] && points_r[r_data_statics][1] == points_r[r_data_statics - 2][1])
			||(points_l[l_data_statics-1][0] == points_l[l_data_statics - 2][0] && points_l[l_data_statics-1][0] == points_l[l_data_statics - 3][0]
				&& points_l[l_data_statics-1][1] == points_l[l_data_statics - 2][1] && points_l[l_data_statics-1][1] == points_l[l_data_statics - 3][1]))
		{
			//printf("涓夋杩涘叆鍚屼竴涓偣锛岄��鍑篭n");
			break;
		}
		if (my_abs(points_r[r_data_statics][0] - points_l[l_data_statics - 1][0]) < 2
			&& my_abs(points_r[r_data_statics][1] - points_l[l_data_statics - 1][1] < 2)
			)
		{
			//printf("\n宸﹀彸鐩搁亣閫�鍑篭n");
			*hightest = (points_r[r_data_statics][1] + points_l[l_data_statics - 1][1]) >> 1;//鍙栧嚭鏈�楂樼偣
			//printf("\n鍦▂=%d澶勯��鍑篭n",*hightest);
			break;
		}
		if ((points_r[r_data_statics][1] < points_l[l_data_statics - 1][1]))
		{
			printf("\n濡傛灉宸﹁竟姣斿彸杈归珮浜嗭紝宸﹁竟绛夊緟鍙宠竟\n");
			continue;//濡傛灉宸﹁竟姣斿彸杈归珮浜嗭紝宸﹁竟绛夊緟鍙宠竟
		}
		if (dir_l[l_data_statics - 1] == 7
			&& (points_r[r_data_statics][1] > points_l[l_data_statics - 1][1]))//宸﹁竟姣斿彸杈归珮涓斿凡缁忓悜涓嬬敓闀夸簡
		{
			//printf("\n宸﹁竟寮�濮嬪悜涓嬩簡锛岀瓑寰呭彸杈癸紝绛夊緟涓�... \n");
			center_point_l[0] = points_l[l_data_statics - 1][0];//x
			center_point_l[1] = points_l[l_data_statics - 1][1];//y
			l_data_statics--;
		}
		r_data_statics++;//绱㈠紩鍔犱竴

		index_r = 0;//鍏堟竻闆讹紝鍚庝娇鐢�
		for (i = 0; i < 8; i++)
		{
			temp_r[i][0] = 0;//鍏堟竻闆讹紝鍚庝娇鐢�
			temp_r[i][1] = 0;//鍏堟竻闆讹紝鍚庝娇鐢�
		}

		//鍙宠竟鍒ゆ柇
		for (i = 0; i < 8; i++)
		{
			if (image[search_filds_r[i][1]][search_filds_r[i][0]] == 0
				&& image[search_filds_r[(i + 1) & 7][1]][search_filds_r[(i + 1) & 7][0]] == 255)
			{
				temp_r[index_r][0] = search_filds_r[(i)][0];
				temp_r[index_r][1] = search_filds_r[(i)][1];
				index_r++;//绱㈠紩鍔犱竴
				dir_r[r_data_statics - 1] = (i);//璁板綍鐢熼暱鏂瑰悜
				//printf("dir[%d]:%d\n", r_data_statics - 1, dir_r[r_data_statics - 1]);
			}
			if (index_r)
			{

				//鏇存柊鍧愭爣鐐�
				center_point_r[0] = temp_r[0][0];//x
				center_point_r[1] = temp_r[0][1];//y
				for (j = 0; j < index_r; j++)
				{
					if (center_point_r[1] > temp_r[j][1])
					{
						center_point_r[0] = temp_r[j][0];//x
						center_point_r[1] = temp_r[j][1];//y
					}
				}

			}
		}


	}


	//鍙栧嚭寰幆娆℃暟
	*l_stastic = l_data_statics;
	*r_stastic = r_data_statics;

}
/*
鍑芥暟鍚嶇О锛歷oid get_left(uint16 total_L)
鍔熻兘璇存槑锛氫粠鍏偦鍩熻竟鐣岄噷鎻愬彇闇�瑕佺殑杈圭嚎
鍙傛暟璇存槑锛�
total_L	锛氭壘鍒扮殑鐐圭殑鎬绘暟
鍑芥暟杩斿洖锛氭棤
淇敼鏃堕棿锛�2022骞�9鏈�25鏃�
澶�    娉細
example锛� get_left(data_stastics_l );
 */
uint8 l_border[image_h];//宸︾嚎鏁扮粍
uint8 r_border[image_h];//鍙崇嚎鏁扮粍
uint8 center_line[image_h];//涓嚎鏁扮粍
void get_left(uint16 total_L)
{
	uint8 i = 0;
	uint16 j = 0;
	uint8 h = 0;
	//鍒濆鍖�
	for (i = 0;i<image_h;i++)
	{
		l_border[i] = border_min;
	}
	h = image_h - 2;
	//宸﹁竟
	for (j = 0; j < total_L; j++)
	{
		//printf("%d\n", j);
		if (points_l[j][1] == h)
		{
			l_border[h] = points_l[j][0]+1;
		}
		else continue; //姣忚鍙彇涓�涓偣锛屾病鍒颁笅涓�琛屽氨涓嶈褰�
		h--;
		if (h == 0) 
		{
			break;//鍒版渶鍚庝竴琛岄��鍑�
		}
	}
}
/*
鍑芥暟鍚嶇О锛歷oid get_right(uint16 total_R)
鍔熻兘璇存槑锛氫粠鍏偦鍩熻竟鐣岄噷鎻愬彇闇�瑕佺殑杈圭嚎
鍙傛暟璇存槑锛�
total_R  锛氭壘鍒扮殑鐐圭殑鎬绘暟
鍑芥暟杩斿洖锛氭棤
淇敼鏃堕棿锛�2022骞�9鏈�25鏃�
澶�    娉細
example锛歡et_right(data_stastics_r);
 */
void get_right(uint16 total_R)
{
	uint8 i = 0;
	uint16 j = 0;
	uint8 h = 0;
	for (i = 0; i < image_h; i++)
	{
		r_border[i] = border_max;//鍙宠竟绾垮垵濮嬪寲鏀惧埌鏈�鍙宠竟锛屽乏杈圭嚎鏀惧埌鏈�宸﹁竟锛岃繖鏍峰叓閭诲煙闂悎鍖哄煙澶栫殑涓嚎灏变細鍦ㄤ腑闂达紝涓嶄細骞叉壈寰楀埌鐨勬暟鎹�
	}
	h = image_h - 2;
	//鍙宠竟
	for (j = 0; j < total_R; j++)
	{
		if (points_r[j][1] == h)
		{
			r_border[h] = points_r[j][0] - 1;
		}
		else continue;//姣忚鍙彇涓�涓偣锛屾病鍒颁笅涓�琛屽氨涓嶈褰�
		h--;
		if (h == 0)break;//鍒版渶鍚庝竴琛岄��鍑�
	}
}

//瀹氫箟鑶ㄨ儉鍜岃厫铓�鐨勯槇鍊煎尯闂�
#define threshold_max	255*5//姝ゅ弬鏁板彲鏍规嵁鑷繁鐨勯渶姹傝皟鑺�
#define threshold_min	255*2//姝ゅ弬鏁板彲鏍规嵁鑷繁鐨勯渶姹傝皟鑺�
void image_filter(uint8(*bin_image)[image_w])//褰㈡�佸婊ゆ尝锛岀畝鍗曟潵璇村氨鏄啫鑳�鍜岃厫铓�鐨勬�濇兂
{
	uint16 i, j;
	uint32 num = 0;


	for (i = 1; i < image_h - 1; i++)
	{
		for (j = 1; j < (image_w - 1); j++)
		{
			//缁熻鍏釜鏂瑰悜鐨勫儚绱犲��
			num =
				bin_image[i - 1][j - 1] + bin_image[i - 1][j] + bin_image[i - 1][j + 1]
				+ bin_image[i][j - 1] + bin_image[i][j + 1]
				+ bin_image[i + 1][j - 1] + bin_image[i + 1][j] + bin_image[i + 1][j + 1];


			if (num >= threshold_max && bin_image[i][j] == 0)
			{

				bin_image[i][j] = 255;//鐧�  鍙互鎼炴垚瀹忓畾涔夛紝鏂逛究鏇存敼

			}
			if (num <= threshold_min && bin_image[i][j] == 255)
			{

				bin_image[i][j] = 0;//榛�

			}

		}
	}

}

/*
鍑芥暟鍚嶇О锛歷oid image_draw_rectan(uint8(*image)[image_w])
鍔熻兘璇存槑锛氱粰鍥惧儚鐢讳竴涓粦妗�
鍙傛暟璇存槑锛歶int8(*image)[image_w]	鍥惧儚棣栧湴鍧�
鍑芥暟杩斿洖锛氭棤
淇敼鏃堕棿锛�2022骞�9鏈�8鏃�
澶�    娉細
example锛� image_draw_rectan(bin_image);
 */
void image_draw_rectan(uint8(*image)[image_w])
{

	uint8 i = 0;
	for (i = 0; i < image_h; i++)
	{
		image[i][0] = 0;
		image[i][1] = 0;
		image[i][image_w - 1] = 0;
		image[i][image_w - 2] = 0;

	}
	for (i = 0; i < image_w; i++)
	{
		image[0][i] = 0;
		image[1][i] = 0;
		//image[image_h-1][i] = 0;

	}
}

/*
鍑芥暟鍚嶇О锛歷oid image_process(void)
鍔熻兘璇存槑锛氭渶缁堝鐞嗗嚱鏁�
鍙傛暟璇存槑锛氭棤
鍑芥暟杩斿洖锛氭棤
淇敼鏃堕棿锛�2022骞�9鏈�8鏃�
澶�    娉細
example锛� image_process();
 */
void image_process(void)
{
uint16 i;
uint8 hightest = 0;//瀹氫箟涓�涓渶楂樿锛宼ip锛氳繖閲岀殑鏈�楂樻寚鐨勬槸y鍊肩殑鏈�灏�
/*杩欐槸绂荤嚎璋冭瘯鐢ㄧ殑*/
Get_image(image_copy);
turn_to_bin();
/*鎻愬彇璧涢亾杈圭晫*/
image_filter(bin_image);//婊ゆ尝
image_draw_rectan(bin_image);//棰勫鐞�
//娓呴浂
data_stastics_l = 0;
data_stastics_r = 0;
if (get_start_point(image_h - 2))//鎵惧埌璧风偣浜嗭紝鍐嶆墽琛屽叓棰嗗煙锛屾病鎵惧埌灏变竴鐩存壘
{
	//printf("姝ｅ湪寮�濮嬪叓棰嗗煙\n");
	search_l_r((uint16)USE_num, bin_image, &data_stastics_l, &data_stastics_r, start_point_l[0], start_point_l[1], start_point_r[0], start_point_r[1], &hightest);
	//printf("鍏偦鍩熷凡缁撴潫\n");
	// 浠庣埇鍙栫殑杈圭晫绾垮唴鎻愬彇杈圭嚎 锛� 杩欎釜鎵嶆槸鏈�缁堟湁鐢ㄧ殑杈圭嚎
	get_left(data_stastics_l);
	get_right(data_stastics_r);
	//澶勭悊鍑芥暟鏀捐繖閲岋紝涓嶈鏀惧埌if澶栭潰鍘讳簡锛屼笉瑕佹斁鍒癷f澶栭潰鍘讳簡锛屼笉瑕佹斁鍒癷f澶栭潰鍘讳簡锛岄噸瑕佺殑浜嬭涓夐亶

}
for(i=60;i++;i<120)
{
    value+=center_line[i];

}
    get_angle=(value/60)-94;


    value=0;
//
//ips200_clear();
//
//ips200_show_rgb565_image(10, 20, bin_image[0], image_w, image_h, image_w, image_h, 0);

//	//鏍规嵁鏈�缁堝惊鐜鏁扮敾鍑鸿竟鐣岀偣
//	for (i = 0; i < data_stastics_l; i++)
//	{
//	    ips200_draw_point(points_l[i][0]+2, points_l[i][1], uesr_BLUE);//鏄剧ず璧风偣
//	}
//	for (i = 0; i < data_stastics_r; i++)
//	{
//	    ips200_draw_point(points_r[i][0]-2, points_r[i][1], uesr_RED);//鏄剧ず璧风偣
//	}
//
//	for (i = hightest; i < image_h-1; i++)
//	{
//		center_line[i] = (l_border[i] + r_border[i]) >> 1;//姹備腑绾�
//		//姹備腑绾挎渶濂芥渶鍚庢眰锛屼笉绠℃槸琛ョ嚎杩樻槸鍋氱姸鎬佹満锛屽叏绋嬫渶濂戒娇鐢ㄤ竴缁勮竟绾匡紝涓嚎鏈�鍚庢眰鍑猴紝涓嶈兘骞叉壈鏈�鍚庣殑杈撳嚭
//		//褰撶劧涔熸湁澶氱粍杈圭嚎鐨勬壘娉曪紝浣嗘槸涓汉鎰熻寰堢箒鐞愶紝涓嶅缓璁�
//		ips200_draw_point(center_line[i], i, uesr_GREEN);//鏄剧ず璧风偣 鏄剧ず涓嚎
//		ips200_draw_point(l_border[i], i, uesr_GREEN);//鏄剧ず璧风偣 鏄剧ず宸﹁竟绾�
//		ips200_draw_point(r_border[i], i, uesr_GREEN);//鏄剧ず璧风偣 鏄剧ず鍙宠竟绾�
//	}


}





/*

杩欓噷鏄捣鐐癸紙0.0锛�***************鈥斺��>*************x鍊兼渶澶�
************************************************************
************************************************************
************************************************************
************************************************************
******************鍋囧杩欐槸涓�鍓浘鍍�*************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
***********************************************************
y鍊兼渶澶�*******************************************(188.120)

*/


