/********************************************************************************
*     COPYRIGHT NOTICE
*     Copyright (c) 2015,Ibrahim
*     All rights reserved.
*
*     本程序没有版权欢迎借阅，或给我提出问题及改进意见
*     联系人Ibrahim 联系方式：1711125768@qq.com
*********************************************************************************
* @file       Init.c
* @brief      野火K60 平台主程序
* @author     Ibrahim
* @version    v5.0
* @date       2015-10-18
*********************************************************************************/
#include "include.h"

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       Init.c
* @brief      void Init_all();
* @version    v5.3
* @date       2016-8-10
*********************************************************************************/
void Init_all()
{
#if   MK60F15
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif

  DisableInterrupts;                           //禁止总中断

  Pid_Init();                                    //Pid Calculate parameters initialize
  gpio_init(PTC3, GPO, 0);
  myCCD_DataInit(&CCD1_info);
  CCD1_info.ID = 1;
  myCCD_DataInit(&CCD2_info);
  CCD2_info.ID = 2;
  Fuzzy_Init();

  myData_Init();

  Init_uart4();

  CCD1_init();

  CCD2_init();

  myCCD_GetBeginLineError(&CCD1_info, &CCD2_info, &Speed_info);

  Init_ftm_motor();                            //初始化电机

  Init_quad();                                 //初始化正交解码器

  gpio_init(PTA16, GPO, 0);

  Init_PORT();

  Init_PORT_C();

  myOLED_Init();

#if TESTSD
  mySD_Init_Parameter();
#endif

  EnableInterrupts;//中断允许

#if IIC_ENABLE
  Init_TLY();
#endif


  /***********  //lcd菜单初始化选择，注意*******/
  // while (lcd_menu_display_init(&Menu))
  // {
  //   if (1 == Parameter_info.OLED_NoAction_Flag) //当按键没有反应的时候计时退出
  //   {
  //     if (Parameter_info.OLED_NoAction_Counter > 0)
  //     {
  //       Parameter_info.OLED_NoAction_Counter--;
  //     }
  //     else if (Parameter_info.OLED_NoAction_Counter <= 0)
  //     {
  //       break;//直接跳出OLED等待
  //     }
  //   }
  // }
#if TESTSD
  mySDWrite_Para();
  mySD_RunData_Init();
#endif

  DELAY_MS(1000);
  Init_PIT0();
  Init_PIT1();   //初始化电机控制定时
}

void Init_uart4(void)
{
  /*不用DMA串口的初始化代码*/
  // uart_init (UART4, 460800);
  // set_vector_handler(UART4_RX_TX_VECTORn, uart4_test_handler);
  // uart_rx_irq_en(UART4);

  /*使用DMA串口的初始化代码*/
  uart_init (UART4, 115200);
  UART_ITDMAConfig(UART4, kUART_DMA_Tx, 1);
  set_vector_handler(UART4_RX_TX_VECTORn, uart4_test_handler);
  uart_rx_irq_en(UART4);
  UART_DMASendConfig(UART4, HW_DMA_CH2);
}


/*!
 *  @brief      main函数
 *  @since      v5.2
 *  @note       测试查询接收多个字符串函数
 */
void uart4_test_handler(void)
{
  char ch;
  if (uart_query    (UART4) == 1)  //接受数据寄存器满
  {
    uart_getchar(UART4, &ch);
    ANO_DT_Data_Receive_Prepare(ch);
  }
}


/*!
 *  @brief      main函数
 *  @since      v5.2
 *  @note       测试查询接收多个字符串函数
 */
void Init_PORT_C(void)
{
  gpio_init(PTC0, GPI, 0);
  gpio_init(PTC1, GPI, 0);
  gpio_init(PTC2, GPI, 0);

  port_init(PTC0, ALT1 | IRQ_FALLING | PF);
  port_init(PTC1, ALT1 | IRQ_FALLING | PF);
  port_init(PTC2, ALT1 | IRQ_FALLING | PF);

  set_vector_handler(PORTC_VECTORn , PORTC_IRQHandler);
  // enable_irq(PORTC_IRQn);
  disable_irq(PORTC_IRQn);

}
/*!
 *  @brief      main函数
 *  @since      v5.2
 *  @note       测试查询接收多个字符串函数
 */
void PORTC_IRQHandler(void)
{
  PORT_FUNC(C, 0, stop_IRQProcess);
  PORT_FUNC(C, 1, stop_IRQProcess);
  PORT_FUNC(C, 2, stop_IRQProcess);

}
/*!
 *  @brief      main函数
 *  @since      v5.2
 *  @note       测试查询接收多个字符串函数
 */
void stop_IRQProcess(void)
{
  if ((PTC0_IN == 0 && PTC1_IN == 1 && PTC2_IN == 0)
      || (PTC0_IN == 1 && PTC1_IN == 1 && PTC2_IN == 0)
      || (PTC0_IN == 0 && PTC1_IN == 1 && PTC2_IN == 1))
  {
    if ( Car_state.now == In_Straight )
    {
      Speed_Expect = 0;
      PidSpeedLeft.temp = 0;
      PidSpeedRight.temp = 0;
      // disable_irq(PORTC_IRQn);
      // check_flag = 0;
    }
  }
}
