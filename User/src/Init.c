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

//extern float a[3], w[3], h[3], Angle[3];
extern uint8  nrf_tx_buff[];

int rx_buff_num = 0;
int tx_buff_num = 0;
char rx_buff[MAX_NUM] = {0};
char tx_buff[MAX_NUM] = {0};


void Init_all()
{
#if   MK60F15
  SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif

  DisableInterrupts;                           //禁止总中断

  Pid_Init();                                    //Pid Calculate parameters initialize

  Fuzzy_Init();

  Init_uart1();

  Init_uart4();

  CCD1_init();

  CCD2_init();

  Init_ftm_motor();                            //初始化电机

  Init_quad();                                 //初始化正交解码器

  Init_PIT0();

  Init_PORT();

  Init_PORT_C();

  //Init_PIT1();
  led_init(LED0);

  Info_Init();

  State_Init();

  myOLED_Init();
  //gpio_init (PTC0, GPO,0);

  EnableInterrupts;//中断允许

  //Init_my_NRF();

  DELAY_MS(1000);
}

void Init_uart4(void)
{
  uart_init (UART4, 115200);
  set_vector_handler(UART4_RX_TX_VECTORn, uart4_test_handler);
  uart_rx_irq_en(UART4);
}

void Init_uart1(void)
{
  uart_init (UART1, 115200);
  set_vector_handler(UART1_RX_TX_VECTORn, uart1_handler);  // 设置中断服务函数到中断向量表里
  uart_rx_irq_en (UART1);                                //开串口接收中断
}


/*!
 *  @brief      main函数
 *  @since      v5.2
 *  @note       测试查询接收多个字符串函数
 */
extern uint8 mode_correct;

void uart1_handler(void)
{
  char ch;

  if (uart_query    (UART1) == 1)  //接收数据寄存器满
  {
    //用户需要处理接收数据
    if (mode_correct == 1)
    {
      uart_getchar   (UART1, &ch);                    //无限等待接受1个字节
      uart_putchar   (UART4 , ch);                    //发送字符串
    }
  }
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
  port_init(PTC6, ALT1 | IRQ_RISING);
  port_init(PTC7, ALT1 | IRQ_RISING);
  set_vector_handler(PORTC_VECTORn , PORTC_IRQHandler);
  gpio_init(PTC5, GPI, 0);
}
/*!
 *  @brief      main函数
 *  @since      v5.2
 *  @note       测试查询接收多个字符串函数
 */
void PORTC_IRQHandler(void)
{
  PORT_FUNC(C, 6, stop_IRQProcess);
  PORT_FUNC(C, 7, stop_IRQProcess);

}
/*!
 *  @brief      main函数
 *  @since      v5.2
 *  @note       测试查询接收多个字符串函数
 */
void stop_IRQProcess(void)
{
  if (PTC6_IN == 1 && PTC7_IN == 1 && PTC5_IN == 0)
  {
    Speed_Expect = 0;
    // disable_irq(PORTC_IRQn);
    // check_flag = 0;
    led_turn(LED0);
  }
  else
  {
    return;
  }
}

void Init_my_NRF(void)
{
  uint8 i;
  /************************ 无线模块 NRF 初始化  ***********************/
  while (!nrf_init());
  //配置中断服务函数
  set_vector_handler(PORTE_VECTORn , PORTE_IRQHandler);               //设置 PORTE 的中断服务函数为 PORTE_VECTORn
  enable_irq(PORTE_IRQn);
  nrf_msg_init();                                                     //无线模块消息初始化

  //线性CCD模块，需要 发送 空命令给 调试板模块，这样可以清掉 接收图像失败而产生多余数据
  i = 20;
  while (i--)
  {
    nrf_msg_tx(COM_RETRAN, nrf_tx_buff);                             //发送多个 空 命令过去，用于清空 接收端的缓存数据
  }
}

/*!
 *  @brief      PORTE中断服务函数
 *  @since      v5.0
 */
void PORTE_IRQHandler(void)
{
  uint8  n;    //引脚号
  uint32 flag;

  flag = PORTE_ISFR;
  PORTE_ISFR  = ~0;                                   //清中断标志位

  n = 27;
  if (flag & (1 << n))                                //PTE27触发中断
  {
    nrf_handler();
  }
}




//队列节点初始化
void Queue_Init(Info_queue *queue)
{
  queue->mean = 0;
  queue->variance = 0;
}

void State_Init()
{
  ccd1_state.now = In_Straight;
  ccd1_state.pre = In_Straight;
  ccd1_state.direc_now = 0;
  ccd1_state.direc_pre = 0;
  ccd2_state.now = In_Straight;
  ccd2_state.pre = In_Straight;
  ccd2_state.direc_now = 0;
  ccd2_state.direc_pre = 0;
}


void Info_Init()
{
  Queue_Init(&ccd1_info.LeftLine);
  Queue_Init(&ccd1_info.RightLine);
  Queue_Init(&ccd1_info.Ec_Left);
  Queue_Init(&ccd1_info.Ec_Right);
  Queue_Init(&ccd2_info.LeftLine);
  Queue_Init(&ccd2_info.RightLine);
  Queue_Init(&ccd2_info.Ec_Left);
  Queue_Init(&ccd2_info.Ec_Right);
}
