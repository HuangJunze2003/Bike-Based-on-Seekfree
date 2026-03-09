/*********************************************************************************************************************
* TC264 Opensourec Library 鍗筹紙TC264 寮�婧愬簱锛夋槸涓�涓熀浜庡畼鏂� SDK 鎺ュ彛鐨勭涓夋柟寮�婧愬簱
* Copyright (c) 2022 SEEKFREE 閫愰绉戞妧
*
* 鏈枃浠舵槸 TC264 寮�婧愬簱鐨勪竴閮ㄥ垎
*
* TC264 寮�婧愬簱 鏄厤璐硅蒋浠�
* 鎮ㄥ彲浠ユ牴鎹嚜鐢辫蒋浠跺熀閲戜細鍙戝竷鐨� GPL锛圙NU General Public License锛屽嵆 GNU閫氱敤鍏叡璁稿彲璇侊級鐨勬潯娆�
* 鍗� GPL 鐨勭3鐗堬紙鍗� GPL3.0锛夋垨锛堟偍閫夋嫨鐨勶級浠讳綍鍚庢潵鐨勭増鏈紝閲嶆柊鍙戝竷鍜�/鎴栦慨鏀瑰畠
*
* 鏈紑婧愬簱鐨勫彂甯冩槸甯屾湜瀹冭兘鍙戞尌浣滅敤锛屼絾骞舵湭瀵瑰叾浣滀换浣曠殑淇濊瘉
* 鐢氳嚦娌℃湁闅愬惈鐨勯�傞攢鎬ф垨閫傚悎鐗瑰畾鐢ㄩ�旂殑淇濊瘉
* 鏇村缁嗚妭璇峰弬瑙� GPL
*
* 鎮ㄥ簲璇ュ湪鏀跺埌鏈紑婧愬簱鐨勫悓鏃舵敹鍒颁竴浠� GPL 鐨勫壇鏈�
* 濡傛灉娌℃湁锛岃鍙傞槄<https://www.gnu.org/licenses/>
*
* 棰濆娉ㄦ槑锛�
* 鏈紑婧愬簱浣跨敤 GPL3.0 寮�婧愯鍙瘉鍗忚 浠ヤ笂璁稿彲鐢虫槑涓鸿瘧鏂囩増鏈�
* 璁稿彲鐢虫槑鑻辨枃鐗堝湪 libraries/doc 鏂囦欢澶逛笅鐨� GPL3_permission_statement.txt 鏂囦欢涓�
* 璁稿彲璇佸壇鏈湪 libraries 鏂囦欢澶逛笅 鍗宠鏂囦欢澶逛笅鐨� LICENSE 鏂囦欢
* 娆㈣繋鍚勪綅浣跨敤骞朵紶鎾湰绋嬪簭 浣嗕慨鏀瑰唴瀹规椂蹇呴』淇濈暀閫愰绉戞妧鐨勭増鏉冨０鏄庯紙鍗虫湰澹版槑锛�
*
* 鏂囦欢鍚嶇О          cpu1_main
* 鍏徃鍚嶇О          鎴愰兘閫愰绉戞妧鏈夐檺鍏徃
* 鐗堟湰淇℃伅          鏌ョ湅 libraries/doc 鏂囦欢澶瑰唴 version 鏂囦欢 鐗堟湰璇存槑
* 寮�鍙戠幆澧�          ADS v1.9.4
* 閫傜敤骞冲彴          TC264D
* 搴楅摵閾炬帴          https://seekfree.taobao.com/
*
* 淇敼璁板綍
* 鏃ユ湡              浣滆��                澶囨敞
* 2022-09-15       pudding            first version
********************************************************************************************************************/

#include "cpu1_main.h"


#pragma section all "cpu1_dsram"



// 灏嗘湰璇彞涓�#pragma section all restore璇彞涔嬮棿鐨勫叏灞�鍙橀噺閮芥斁鍦–PU1鐨凴AM涓�
// 灏嗘湰璇彞涓�#pragma section all restore璇彞涔嬮棿鐨勫叏灞�鍙橀噺閮芥斁鍦–PU0鐨凴AM涓�

// *************************** 渚嬬▼纭欢杩炴帴璇存槑 ***************************
// 浣跨敤閫愰绉戞妧璋冭瘯涓嬭浇鍣ㄨ繛鎺�
//      鐩存帴灏嗕笅杞藉櫒姝ｇ‘杩炴帴鍦ㄦ牳蹇冩澘鐨勮皟璇曚笅杞芥帴鍙ｅ嵆鍙�
//
// 鎺ュ叆 鎬婚捇椋庢憚鍍忓ご
//      妯″潡绠¤剼            鍗曠墖鏈虹鑴�
//      TXD                 鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_COF_UART_TX        瀹忓畾涔�
//      RXD                 鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_COF_UART_RX        瀹忓畾涔�
//      D0                  鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_D0_PIN             瀹忓畾涔�
//      D1                  鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_D1_PIN             瀹忓畾涔�
//      D2                  鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_D2_PIN             瀹忓畾涔�
//      D3                  鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_D3_PIN             瀹忓畾涔�
//      D4                  鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_D4_PIN             瀹忓畾涔�
//      D5                  鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_D5_PIN             瀹忓畾涔�
//      D6                  鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_D6_PIN             瀹忓畾涔�
//      D7                  鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_D7_PIN             瀹忓畾涔�
//      PCLK                鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_PCLK_PIN           瀹忓畾涔�
//      VSYNC               鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_VSY_PIN            瀹忓畾涔�
//      HSYNC               鏌ョ湅 zf_device_mt9v03x.h 涓� MT9V03X_HERF_PIN           瀹忓畾涔�
//  ------------------------------------

// *************************** 渚嬬▼浣跨敤姝ラ璇存槑 ***************************
// 1.鏍规嵁纭欢杩炴帴璇存槑杩炴帴濂芥ā鍧楋紝浣跨敤鐢垫簮渚涚數(涓嬭浇鍣ㄤ緵鐢典細瀵艰嚧妯″潡鐢靛帇涓嶈冻)
//
// 2.涓嬭浇渚嬬▼鍒板崟鐗囨満涓紝鎵撳紑閫愰涓插彛鍔╂墜銆�
//
// 3.鍦ㄩ�愰涓插彛鍔╂墜涓紝閫夋嫨鍥惧儚浼犺緭銆�
//
// 4.閫夋嫨涓嬭浇鍣ㄥ搴旂殑涓插彛鍙凤紝娉㈢壒鐜�(榛樿115200)锛岀偣鍑昏繛鎺�
//
// 5.绛夊緟鍑犵閽燂紝鍥惧儚灏变細鏄剧ず鍦ㄩ�愰涓插彛鍔╂墜涓��


// *************************** 渚嬬▼娴嬭瘯璇存槑 ***************************
// 1.鏈緥绋嬩細閫氳繃 Debug 涓插彛杈撳嚭娴嬭瘯淇℃伅 璇峰姟蹇呮帴濂借皟璇曚覆鍙ｄ互渚胯幏鍙栨祴璇曚俊鎭�
//
// 2.杩炴帴濂芥ā鍧楀拰鏍稿績鏉垮悗锛堝敖閲忎娇鐢ㄩ厤濂椾富鏉挎祴璇曚互閬垮厤渚涚數涓嶈冻鐨勯棶棰橈級 鐑у綍鏈緥绋� 鎸変笅澶嶄綅鍚庣▼搴忓紑濮嬭繍琛�
//
// 3.濡傛灉妯″潡鏈兘姝ｅ父鍒濆鍖� 浼氶�氳繃 DEBUG 涓插彛杈撳嚭鏈兘鎴愬姛鍒濆鍖栫殑鍘熷洜 闅忓悗绋嬪簭浼氬皾璇曢噸鏂板垵濮嬪寲 涓�鑸儏鍐典笅閲嶈瘯浼氭垚鍔�
//
// 4.濡傛灉涓�鐩村湪 Debug 涓插彛杈撳嚭鎶ラ敊 灏遍渶瑕佹鏌ユ姤閿欏唴瀹� 骞舵煡鐪嬫湰鏂囦欢涓嬫柟鐨勫父瑙侀棶棰樺垪琛ㄨ繘琛屾帓鏌�
//
// 5.浣跨敤115200娉㈢壒鐜囥�傞�愰鍔╂墜鐨勫浘鍍忓ぇ姒備袱涓夌涓�甯э紝杩欐槸鐢变簬涓插彛浼犺緭鎱㈠鑷寸殑锛屽苟闈炴憚鍍忓ご閲囬泦闂銆�
//
// 6.115200娉㈢壒鐜囦竴绉掗挓澶х害浼犺緭11.25KB鏁版嵁锛屼竴鍓浘鍍�188x120鐨勫垎杈ㄧ巼澶х害鏈�22KB鐨勬暟鎹��
//


// **************************** 浠ｇ爜鍖哄煙 ****************************
//0锛氫笉鍖呭惈杈圭晫淇℃伅
//1锛氬寘鍚笁鏉¤竟绾夸俊鎭紝杈圭嚎淇℃伅鍙寘鍚í杞村潗鏍囷紝绾佃酱鍧愭爣鐢卞浘鍍忛珮搴﹀緱鍒帮紝鎰忓懗鐫�姣忎釜杈圭晫鍦ㄤ竴琛屼腑鍙細鏈変竴涓偣
//2锛氬寘鍚笁鏉¤竟绾夸俊鎭紝杈圭晫淇℃伅鍙惈鏈夌旱杞村潗鏍囷紝妯酱鍧愭爣鐢卞浘鍍忓搴﹀緱鍒帮紝鎰忓懗鐫�姣忎釜杈圭晫鍦ㄤ竴鍒椾腑鍙細鏈変竴涓偣锛屼竴鑸潵璇村緢灏戞湁杩欐牱鐨勪娇鐢ㄩ渶姹�
//3锛氬寘鍚笁鏉¤竟绾夸俊鎭紝杈圭晫淇℃伅鍚湁妯旱杞村潗鏍囷紝鎰忓懗鐫�浣犲彲浠ユ寚瀹氭瘡涓偣鐨勬í绾靛潗鏍囷紝杈圭嚎鐨勬暟閲忎篃鍙互澶т簬鎴栬�呭皬浜庡浘鍍忕殑楂樺害锛岄�氬父鏉ヨ杈圭嚎鏁伴噺澶т簬鍥惧儚鐨勯珮搴︼紝涓�鑸槸鎼滅嚎绠楁硶鑳芥壘鍑哄洖寮殑鎯呭喌
//4锛氭病鏈夊浘鍍忎俊鎭紝浠呭寘鍚笁鏉¤竟绾夸俊鎭紝杈圭嚎淇℃伅鍙寘鍚í杞村潗鏍囷紝绾佃酱鍧愭爣鐢卞浘鍍忛珮搴﹀緱鍒帮紝鎰忓懗鐫�姣忎釜杈圭晫鍦ㄤ竴琛屼腑鍙細鏈変竴涓偣锛岃繖鏍风殑鏂瑰紡鍙互鏋佸ぇ鐨勯檷浣庝紶杈撶殑鏁版嵁閲�
#define INCLUDE_BOUNDARY_TYPE   3

// 杈圭晫鐨勭偣鏁伴噺杩滃ぇ浜庡浘鍍忛珮搴︼紝渚夸簬淇濆瓨鍥炲集鐨勬儏鍐�
#define BOUNDARY_NUM            (MT9V03X_H * 3 / 2)

uint8 xy_x1_boundary[BOUNDARY_NUM], xy_x2_boundary[BOUNDARY_NUM], xy_x3_boundary[BOUNDARY_NUM];
uint8 xy_y1_boundary[BOUNDARY_NUM], xy_y2_boundary[BOUNDARY_NUM], xy_y3_boundary[BOUNDARY_NUM];

uint8 x1_boundary[MT9V03X_H], x2_boundary[MT9V03X_H], x3_boundary[MT9V03X_H];
uint8 y1_boundary[MT9V03X_W], y2_boundary[MT9V03X_W], y3_boundary[MT9V03X_W];

// 鍥惧儚澶囦唤鏁扮粍锛屽湪鍙戦�佸墠灏嗗浘鍍忓浠藉啀杩涜鍙戦�侊紝杩欐牱鍙互閬垮厤鍥惧儚鍑虹幇鎾曡鐨勯棶棰�
IFX_ALIGN(4) uint8  image_copy[MT9V03X_H][MT9V03X_W];
//static uint8 center_line[MT9V03X_H];
uint8 OTSU_Threshold=100;
#define LED1                    (P20_9 )
// **************************** 浠ｇ爜鍖哄煙 ****************************

// 鏈緥绋嬫槸寮�婧愬簱绌哄伐绋� 鍙敤浣滅Щ妞嶆垨鑰呮祴璇曞悇绫诲唴澶栬
// 鏈緥绋嬫槸寮�婧愬簱绌哄伐绋� 鍙敤浣滅Щ妞嶆垨鑰呮祴璇曞悇绫诲唴澶栬
// 鏈緥绋嬫槸寮�婧愬簱绌哄伐绋� 鍙敤浣滅Щ妞嶆垨鑰呮祴璇曞悇绫诲唴澶栬

void core1_main(void)
{
    disable_Watchdog();                     // 鍏抽棴鐪嬮棬鐙�
    interrupt_global_enable(0);             // 鎵撳紑鍏ㄥ眬涓柇
    // 姝ゅ缂栧啓鐢ㄦ埛浠ｇ爜 渚嬪澶栬鍒濆鍖栦唬鐮佺瓑
    ips200_init(IPS200_TYPE_PARALLEL8);
    float x=0.721;
    ips200_show_float(0, 0, x, 2, 3);
    clock_init();                   // 鑾峰彇鏃堕挓棰戠巼<鍔″繀淇濈暀>
      debug_init();                   // 鍒濆鍖栭粯璁よ皟璇曚覆鍙�

    // 姝ゅ缂栧啓鐢ㄦ埛浠ｇ爜 渚嬪澶栬鍒濆鍖栦唬鐮佺瓑
    cpu_wait_event_ready();                 // 绛夊緟鎵�鏈夋牳蹇冨垵濮嬪寲瀹屾瘯

      // 姝ゅ缂栧啓鐢ㄦ埛浠ｇ爜 渚嬪澶栬鍒濆鍖栦唬鐮佺瓑

      // 璁剧疆閫愰鍔╂墜浣跨敤DEBUG涓插彛杩涜鏀跺彂
      //seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_DEBUG_UART);

  #if(0 != INCLUDE_BOUNDARY_TYPE)
      int32 i=0;
  #endif

  #if(3 == INCLUDE_BOUNDARY_TYPE)
      int32 j=0;
  #endif

      gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // 鍒濆鍖� LED1 杈撳嚭 榛樿楂樼數骞� 鎺ㄦ尳杈撳嚭妯″紡

      // 姝ゅ缂栧啓鐢ㄦ埛浠ｇ爜 渚嬪澶栬鍒濆鍖栦唬鐮佺瓑
      while(1)
      {
          if(mt9v03x_init())
              gpio_toggle_level(LED1);                                            // 缈昏浆 LED 寮曡剼杈撳嚭鐢靛钩 鎺у埗 LED 浜伃 鍒濆鍖栧嚭閿欒繖涓伅浼氶棯鐨勫緢鎱�
          else
              break;
          system_delay_ms(500);                                                  // 闂伅琛ㄧず寮傚父
      }

  #if(0 == INCLUDE_BOUNDARY_TYPE)
      // 鍙戦�佹�婚捇椋庡浘鍍忎俊鎭�(浠呭寘鍚師濮嬪浘鍍忎俊鎭�)
      seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);

  #elif(1 == INCLUDE_BOUNDARY_TYPE)
      // 鍙戦�佹�婚捇椋庡浘鍍忎俊鎭�(骞朵笖鍖呭惈涓夋潯杈圭晫淇℃伅锛岃竟鐣屼俊鎭彧鍚湁妯酱鍧愭爣锛岀旱杞村潗鏍囩敱鍥惧儚楂樺害寰楀埌锛屾剰鍛崇潃姣忎釜杈圭晫鍦ㄤ竴琛屼腑鍙細鏈変竴涓偣)
      // 瀵硅竟鐣屾暟缁勫啓鍏ユ暟鎹�
      for(i = 0; i < MT9V03X_H; i++)
      {
          x1_boundary[i] = 70 - (70 - 20) * (uint8)i / MT9V03X_H;
          x2_boundary[i] = MT9V03X_W / 2;
          x3_boundary[i] = 118 + (168 - 118) * (uint8)i / MT9V03X_H;
      }
      seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);
      seekfree_assistant_camera_boundary_config(X_BOUNDARY, MT9V03X_H, x1_boundary, x2_boundary, x3_boundary, NULL, NULL ,NULL);


  #elif(2 == INCLUDE_BOUNDARY_TYPE)
      // 鍙戦�佹�婚捇椋庡浘鍍忎俊鎭�(骞朵笖鍖呭惈涓夋潯杈圭晫淇℃伅锛岃竟鐣屼俊鎭彧鍚湁绾佃酱鍧愭爣锛屾í杞村潗鏍囩敱鍥惧儚瀹藉害寰楀埌锛屾剰鍛崇潃姣忎釜杈圭晫鍦ㄤ竴鍒椾腑鍙細鏈変竴涓偣)
      // 閫氬父寰堝皯鏈夎繖鏍风殑浣跨敤闇�姹�
      // 瀵硅竟鐣屾暟缁勫啓鍏ユ暟鎹�
      for(i = 0; i < MT9V03X_W; i++)
      {
          y1_boundary[i] = (uint8)i * MT9V03X_H / MT9V03X_W;
          y2_boundary[i] = MT9V03X_H / 2;
          y3_boundary[i] = (MT9V03X_W - (uint8)i) * MT9V03X_H / MT9V03X_W;
      }
      seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);
      seekfree_assistant_camera_boundary_config(Y_BOUNDARY, MT9V03X_W, NULL, NULL ,NULL, y1_boundary, y2_boundary, y3_boundary);


  #elif(3 == INCLUDE_BOUNDARY_TYPE)
      // 鍙戦�佹�婚捇椋庡浘鍍忎俊鎭�(骞朵笖鍖呭惈涓夋潯杈圭晫淇℃伅锛岃竟鐣屼俊鎭惈鏈夋í绾佃酱鍧愭爣)
      // 杩欐牱鐨勬柟寮忓彲浠ュ疄鐜板浜庢湁鍥炲集鐨勮竟鐣屾樉绀�
      j = 0;
      for(i = MT9V03X_H - 1; i >= MT9V03X_H / 2; i--)
      {
          // 鐩寸嚎閮ㄥ垎
          xy_x1_boundary[j] = 34;
          xy_y1_boundary[j] = (uint8)i;

          xy_x2_boundary[j] = 47;
          xy_y2_boundary[j] = (uint8)i;

          xy_x3_boundary[j] = 60;
          xy_y3_boundary[j] = (uint8)i;
          j++;
      }

      for(i = MT9V03X_H / 2 - 1; i >= 0; i--)
      {
          // 鐩寸嚎杩炴帴寮亾閮ㄥ垎
          xy_x1_boundary[j] = 34 + (MT9V03X_H / 2 - (uint8)i) * (MT9V03X_W / 2 - 34) / (MT9V03X_H / 2);
          xy_y1_boundary[j] = (uint8)i;

          xy_x2_boundary[j] = 47 + (MT9V03X_H / 2 - (uint8)i) * (MT9V03X_W / 2 - 47) / (MT9V03X_H / 2);
          xy_y2_boundary[j] = 15 + (uint8)i * 3 / 4;

          xy_x3_boundary[j] = 60 + (MT9V03X_H / 2 - (uint8)i) * (MT9V03X_W / 2 - 60) / (MT9V03X_H / 2);
          xy_y3_boundary[j] = 30 + (uint8)i / 2;
          j++;
      }

      for(i = 0; i < MT9V03X_H / 2; i++)
      {
          // 鍥炲集閮ㄥ垎
          xy_x1_boundary[j] = MT9V03X_W / 2 + (uint8)i * (138 - MT9V03X_W / 2) / (MT9V03X_H / 2);
          xy_y1_boundary[j] = (uint8)i;

          xy_x2_boundary[j] = MT9V03X_W / 2 + i * (133 - MT9V03X_W / 2) / (MT9V03X_H / 2);
          xy_y2_boundary[j] = 15 + (uint8)i * 3 / 4;

          xy_x3_boundary[j] = MT9V03X_W / 2 + i * (128 - MT9V03X_W / 2) / (MT9V03X_H / 2);
          xy_y3_boundary[j] = 30 + (uint8)i / 2;
          j++;
      }
      seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);
      seekfree_assistant_camera_boundary_config(XY_BOUNDARY, BOUNDARY_NUM, xy_x1_boundary, xy_x2_boundary, xy_x3_boundary, xy_y1_boundary, xy_y2_boundary, xy_y3_boundary);


  #elif(4 == INCLUDE_BOUNDARY_TYPE)
      // 鍙戦�佹�婚捇椋庡浘鍍忎俊鎭�(骞朵笖鍖呭惈涓夋潯杈圭晫淇℃伅锛岃竟鐣屼俊鎭彧鍚湁妯酱鍧愭爣锛岀旱杞村潗鏍囩敱鍥惧儚楂樺害寰楀埌锛屾剰鍛崇潃姣忎釜杈圭晫鍦ㄤ竴琛屼腑鍙細鏈変竴涓偣)
      // 瀵硅竟鐣屾暟缁勫啓鍏ユ暟鎹�
      for(i = 0; i < MT9V03X_H; i++)
      {
          x1_boundary[i] = 70 - (70 - 20) * (uint8)i / MT9V03X_H;
          x2_boundary[i] = MT9V03X_W / 2;
          x3_boundary[i] = 118 + (168 - 118) * (uint8)i / MT9V03X_H;
      }
      seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, NULL, MT9V03X_W, MT9V03X_H);
      seekfree_assistant_camera_boundary_config(X_BOUNDARY, MT9V03X_H, x1_boundary, x2_boundary, x3_boundary, NULL, NULL ,NULL);


  #endif

      // 姝ゅ缂栧啓鐢ㄦ埛浠ｇ爜 渚嬪澶栬鍒濆鍖栦唬鐮佺瓑
      cpu_wait_event_ready();         // 绛夊緟鎵�鏈夋牳蹇冨垵濮嬪寲瀹屾瘯
      //int flag_neighborhood=0;
      //clear_find_point();
      while (TRUE)
      {
          // 姝ゅ缂栧啓闇�瑕佸惊鐜墽琛岀殑浠ｇ爜


          if(mt9v03x_finish_flag)
          {
              mt9v03x_finish_flag = 0;

              // 鍦ㄥ彂閫佸墠灏嗗浘鍍忓浠藉啀杩涜鍙戦�侊紝杩欐牱鍙互閬垮厤鍥惧儚鍑虹幇鎾曡鐨勯棶棰�
              memcpy(image_copy[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
              image_process();
               //鍙戦�佸浘鍍�
              //ips200_show_binary_image(30, 60, image_copy[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H);
//                          OTSU_Threshold = otsuThreshold(image_copy[0]);//锟斤拷锟斤拷锟街�
//                          for(i = 0;i<MT9V03X_H;i++)
//                          {
//                              for(j = 0;j<MT9V03X_W;j++)
//                              {
//                                  if(image_copy[i][j]>OTSU_Threshold)image_copy[i][j] = WHITE;
//                                  else image_copy[i][j] = BLACK;
//                              }
//                          }
//
//                          image_draw_rectan(image_copy);
//                          flag_neighborhood=get_start_point(MT9V03X_H-2);
//                          if(flag_neighborhood)
//                          {
//                              search_neighborhood();
//                              draw_sideline(image_copy, MT9V03X_W);
//                          }
//
//                          ips200_show_gray_image(10, 100, image_copy[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
          }

          // 姝ゅ缂栧啓闇�瑕佸惊鐜墽琛岀殑浠ｇ爜
      }
}


#pragma section all restore
// **************************** 浠ｇ爜鍖哄煙 ****************************
