/********************************************************************************
*     COPYRIGHT NOTICE
*     Copyright (c) 2015,Ibrahim
*     All rights reserved.
*
*     本程序没有版权欢迎借阅，或给我提出问题及改进意见
*     联系人Ibrahim 联系方式：1711125768@qq.com
*********************************************************************************
* @file       main.c
* @brief      野火K60 平台主程序
* @author     Ibrahim
* @version    v5.0
* @date       2015-10-18
*********************************************************************************/
#include "include.h"

void Send_CCD_Imag();
/*!
 *  @brief      main函数
 *  @since      v5.0
 *  @note        整车
 */
void main()
{
  Init_all();
  wdog_init_ms(150);
  for (;;)
  {
    Remote_stop();
    if (TIME0flag_5ms == 1)
    {
      TIME0flag_5ms = 0 ;
    }

    if (TIME0flag_10ms == 1)
    {
      TIME0flag_10ms = 0 ;
      Servo_Process();
    }

    if (TIME0flag_15ms == 1)
    {
      TIME0flag_15ms = 0 ;
      if (!stop_flag && Tune_Mode == 1)
      {
        push(0, (int16)Center_Board_Value); push(1, 64); push(2, (int16)(PidServo.ex_kp * 1000)); push(3, (int16)(PidServo.ex_kd * 1000));
        push(4, (int16)(PidServo.outP * 1000)); push(5, (int16)PidServo.outD * 1000); push(6, (int16)PidServo.out * 1000); push(7, (int16)Calservo); push(8, 1);
        Data_Send((uint8 *)SendBuf);
      }
      if (!stop_flag && Tune_Mode == 4)
      {
        push(0, (int16)ccd1_info.LeftLine.variance); push(1, (int16)ccd1_info.LeftLine.mean); push(2, (int16)(ccd1_info.RightLine.variance)); push(3, (int16)(ccd1_info.RightLine.mean));
        push(4, (int16)ccd1_info.Ec_Left.mean); push(5, (int16)ccd1_info.Ec_Right.mean); push(6, (int16)ccd1_info.Ec_Left.node[qhead]);
        push(7, (int16)ccd1_info.Ec_Right.node[qhead]); push(8, 4);
        Data_Send((uint8 *)SendBuf);
      }
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
      Send_CCD_Imag();
      wdog_feed();
    }

  } //for(;;)
}//main()


void Send_CCD_Imag()
{

  if (stop_flag)
  {
    if (ccd_switch_flag) SendImageData(Pixel_1);                                //CCD上传到蓝宙上位机函数
    else SendImageData(Pixel_2);
  }
  else
  {
    if (check_flag == 50)
    {
      enable_irq(PORTC_IRQn);
      check_flag = 51;
    }
  }
}
