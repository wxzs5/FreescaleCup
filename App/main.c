/*************************************************************************
*                                           我要过六级                                                   *
*************************************************************************
* @file       main.c
* @brief      整车调试
* @version    v5.3
* @date       2016-6-22
*********************************************************************************/
#include "include.h"

/*!
 *  @brief      main函数
 *  @since      v5.0
 *  @note        整车
 */
void main()
{
  Init_all();
  while (lcd_menu_display_init(&Menu))
  {
    if (1 == Parameter_info.OLED_NoAction_Flag) //当按键没有反应的时候计时退出
    {
      if (Parameter_info.OLED_NoAction_Counter > 0)
      {
        Parameter_info.OLED_NoAction_Counter--;
      }
      else if (Parameter_info.OLED_NoAction_Counter <= 0)
      {
        break;//直接跳出OLED等待
      }
    }
  }
  wdog_init_ms(150);
  for (;;)
  {
    Car_stop();
    if (TIME0flag_5ms == 1)
    {
      TIME0flag_5ms = 0 ;
    }

    if (TIME0flag_10ms == 1)
    {
      TIME0flag_10ms = 0 ;
      Steer_Process();
    }

    if (TIME0flag_15ms == 1)
    {
      TIME0flag_15ms = 0 ;
      Send_Steer_Info();
    }

    if (TIME0flag_20ms == 1)
    {
      TIME0flag_20ms = 0 ;
    }

    if (TIME0flag_25ms == 1)
    {
      TIME0flag_25ms = 0 ;
      Motor_Process();
    }

    if (TIME0flag_100ms == 1)
    {
      TIME0flag_100ms = 0 ;
      // printf("%d\n", Menu.Tun_Res );
      //Send_CCD_Imag();
      wdog_feed();
    }

  } //for(;;)
}//main()


