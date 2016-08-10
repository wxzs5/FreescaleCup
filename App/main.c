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
  for (;;)
  {
    Car_stop();
    if (TIME0flag_5ms == 1)
    {
      TIME0flag_5ms = 0 ;
#if IIC_ENABLE
      Imu_calculate();
#endif
      if (IIC_Count >= 20000)
      {
        Init_TLY();
        IIC_Count = 0;
      }
    }

    if (TIME0flag_10ms == 1)
    {
      TIME0flag_10ms = 0 ;
      Steer_Process();
      Car_State_Judge();
    }

    if (TIME0flag_15ms == 1)
    {
      TIME0flag_15ms = 0 ;
      // Send_Steer_Info();
    }

    if (TIME0flag_20ms == 1)
    {
      TIME0flag_20ms = 0 ;
    }

    if (TIME0flag_25ms == 1)
    {
      TIME0flag_25ms = 0 ;
    }

    if (TIME0flag_100ms == 1)
    {
      TIME0flag_100ms = 0 ;
      Send_CCD_Imag();
    }

  } //for(;;)
}//main()


