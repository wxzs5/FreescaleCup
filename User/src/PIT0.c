/********************************************************************************
*     COPYRIGHT NOTICE
*     Copyright (c) 2015,Ibrahim
*     All rights reserved.
*
*     本程序没有版权欢迎借阅，或给我提出问题及改进意见
*     联系人Ibrahim 联系方式：1711125768@qq.com
*********************************************************************************
* @file       PIT0.c
* @brief      野火K60 平台主程序
* @author     Ibrahim
* @version    v5.0
* @date       2015-10-18
*********************************************************************************/
#include "include.h"

/*************************
设置系统时间变量
*************************/
uint8 TIME0flag_2ms  = 0 ;
uint8 TIME0flag_5ms  = 0 ;
uint8 TIME0flag_10ms = 0 ;
uint8 TIME0flag_15ms = 0 ;
uint8 TIME0flag_20ms = 0 ;
uint8 TIME0flag_25ms = 0 ;
uint8 TIME0flag_100ms = 0 ;
uint8  TimeCount = 0 ;

/*******************************************************************************
* Function Name  : Init_PIT()
* Description    : 中断初始化函数
* Input          : None
* Output         : None
* Return         : None
* Editor         ：Ibrahim
***************************************************************************/
void Init_PIT0()
{
  pit_init_ms(PIT0, 5);                                //初始化PIT0，定时时间为： 5ms
  set_vector_handler(PIT0_VECTORn , PIT0_IRQHandler);     //设置PIT0的中断服务函数为 PIT0_IRQHandler
  enable_irq (PIT0_IRQn);                                 //使能PIT0中断
}
/*******************************************************************************
* Function Name  : PIT0_IRQHandler(void)
* Description    : 中断函数
* Input          : None
* Output         : None
* Return         : None
* Editor         ：Ibrahim
***************************************************************************/
void PIT0_IRQHandler(void)
{
  PIT_Flag_Clear(PIT0);       //清中断标志位
  TimeCount ++ ;

  if (TimeCount % 1 == 0 )
  {
    TIME0flag_5ms = 1;
  }
  if (TimeCount % 2 == 0 )
  {
    TIME0flag_10ms = 1;
  }
  if (TimeCount % 3 == 0 )
  {
    TIME0flag_15ms = 1;
  }
  if (TimeCount % 4 == 0 )
  {
    TIME0flag_20ms = 1;
  }
  if (TimeCount % 5 == 0 )
  {
    TIME0flag_25ms = 1;
  }
  if (TimeCount % 20 == 0 )
  {
    TIME0flag_100ms = 1;
    TimeCount = 0 ;
  }
}



void Init_PIT1()
{
  pit_init_ms(PIT1, 5);                                //初始化PIT0，定时时间为： 5ms
  set_vector_handler(PIT1_VECTORn , PIT1_IRQHandler);     //设置PIT0的中断服务函数为 PIT0_IRQHandler
  enable_irq (PIT1_IRQn);                                 //使能PIT0中断
}

/*******************************************************************************
* Function Name  : void PIT1_IRQHandler(void)
* Description    : 中断初始化函数
* Input          : None
* Output         : None
* Return         : None
* Editor         ：Ibrahim
***************************************************************************/
void PIT1_IRQHandler(void)
{
  PIT_Flag_Clear(PIT1);       //清中断标志位
  gpio_turn(PTA16);
  Motor_Process();
  gpio_turn(PTA16);

}

