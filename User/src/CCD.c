/********************************************************************************
*     COPYRIGHT NOTICE
*     Copyright (c) 2015,Ibrahim
*     All rights reserved.
*
*     本程序没有版权欢迎借阅，或给我提出问题及改进意见
*     联系人Ibrahim 联系方式：1711125768@qq.com
*********************************************************************************
* @file       control.c
* @brief      野火K60 平台主程序
* @author     Ibrahim
* @version    v5.0
* @date       2015-10-18
*********************************************************************************/
#include "include.h"


/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：CCD1_init
*  功能说明：CCD1初始化
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void CCD1_init(void)
{
  gpio_init(PTE28, GPO, 1);
  gpio_init(PTE26, GPO, 1);
  adc_init(ADC0_DM1);

}


void CCD2_init(void)
{
  gpio_init(PTE24, GPO, 1);
  gpio_init(PTE25, GPO, 1);
  adc_init(ADC0_DM0);       //PTB0

}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：CCD1_StartIntegration
*  功能说明：CCD启动程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void CCD1_StartIntegration(void)
{
  uint8 i;

  CCD1_SI_SetVal();            /* SI  = 1 */
  SamplingDelay();
  CCD1_CLK_SetVal();           /* CLK = 1 */
  SamplingDelay();
  CCD1_SI_ClrVal();            /* SI  = 0 */
  SamplingDelay();
  CCD1_CLK_ClrVal();           /* CLK = 0 */

  for (i = 0; i < 127; i++) {
    SamplingDelay();
    SamplingDelay();
    CCD1_CLK_SetVal();       /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CCD1_CLK_ClrVal();       /* CLK = 0 */
  }
  SamplingDelay();
  SamplingDelay();
  CCD1_CLK_SetVal();           /* CLK = 1 */
  SamplingDelay();
  SamplingDelay();
  CCD1_CLK_ClrVal();           /* CLK = 0 */
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：CCD2_StartIntegration
*  功能说明：CCD启动程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void CCD2_StartIntegration(void)
{
  uint8 i;

  CCD2_SI_SetVal();            /* SI  = 1 */
  SamplingDelay();
  CCD2_CLK_SetVal();           /* CLK = 1 */
  SamplingDelay();
  CCD2_SI_ClrVal();            /* SI  = 0 */
  SamplingDelay();
  CCD2_CLK_ClrVal();           /* CLK = 0 */

  for (i = 0; i < 127; i++) {
    SamplingDelay();
    SamplingDelay();
    CCD2_CLK_SetVal();       /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CCD2_CLK_ClrVal();       /* CLK = 0 */
  }
  SamplingDelay();
  SamplingDelay();
  CCD2_CLK_SetVal();           /* CLK = 1 */
  SamplingDelay();
  SamplingDelay();
  CCD2_CLK_ClrVal();           /* CLK = 0 */
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：CCD1_ImageCapture
*  功能说明：CCD采样程序
*  参数说明：* ImageData   采样数组
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*ImageData =  ad_once(ADC1, AD6a, ADC_8bit);
*************************************************************************/
void CCD1_ImageCapture(uint8 * ImageData)
{
  uint8 i;
  //extern uint8 AtemP ;

  CCD1_SI_SetVal();            /* SI  = 1 */
  SamplingDelay();
  CCD1_CLK_SetVal();           /* CLK = 1 */
  SamplingDelay();
  CCD1_SI_ClrVal();            /* SI  = 0 */
  SamplingDelay();

  //Delay 10us for sample the first pixel
  /**/
  for (i = 0; i < 250; i++) {                   //更改250，让CCD的图像看上去比较平滑，
    SamplingDelay() ;  //200ns                  //把该值改大或者改小达到自己满意的结果。
  }

  //Sampling Pixel 1

  *ImageData =  adc_once(ADC0_DM1, ADC_8bit);
  ImageData ++ ;
  CCD1_CLK_ClrVal();           /* CLK = 0 */

  for (i = 0; i < 127; i++) {
    SamplingDelay();
    SamplingDelay();
    CCD1_CLK_SetVal();       /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    //Sampling Pixel 2~128

    *ImageData =  adc_once(ADC0_DM1, ADC_8bit);
    ImageData ++ ;
    CCD1_CLK_ClrVal();       /* CLK = 0 */
  }
  SamplingDelay();
  SamplingDelay();
  CCD1_CLK_SetVal();           /* CLK = 1 */
  SamplingDelay();
  SamplingDelay();
  CCD1_CLK_ClrVal();           /* CLK = 0 */
}

/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：CCD2_ImageCapture
*  功能说明：CCD采样程序
*  参数说明：* ImageData   采样数组
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*ImageData =  ad_once(ADC1, AD6a, ADC_8bit);
*************************************************************************/
void CCD2_ImageCapture(uint8 * ImageData)
{
  uint8 i;
  //extern uint8 AtemP ;

  CCD2_SI_SetVal();            /* SI  = 1 */
  SamplingDelay();
  CCD2_CLK_SetVal();           /* CLK = 1 */
  SamplingDelay();
  CCD2_SI_ClrVal();            /* SI  = 0 */
  SamplingDelay();

  //Delay 10us for sample the first pixel
  /**/
  for (i = 0; i < 250; i++) {                   //更改250，让CCD的图像看上去比较平滑，
    SamplingDelay() ;  //200ns                  //把该值改大或者改小达到自己满意的结果。
  }

  //Sampling Pixel 1

  *ImageData =  adc_once(ADC0_DM0, ADC_8bit);
  ImageData ++ ;
  CCD2_CLK_ClrVal();           /* CLK = 0 */

  for (i = 0; i < 127; i++) {
    SamplingDelay();
    SamplingDelay();
    CCD2_CLK_SetVal();       /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    //Sampling Pixel 2~128

    *ImageData =  adc_once(ADC0_DM0, ADC_8bit);
    ImageData ++ ;
    CCD2_CLK_ClrVal();       /* CLK = 0 */
  }
  SamplingDelay();
  SamplingDelay();
  CCD2_CLK_SetVal();           /* CLK = 1 */
  SamplingDelay();
  SamplingDelay();
  CCD2_CLK_ClrVal();           /* CLK = 0 */
}


/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SendHex
*  功能说明：采集发数程序
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendHex(uint8 hex)
{
  uint8 temp;
  temp = hex >> 4;
  if (temp < 10) {
    uart_putchar(UART4, temp + '0');
  } else {
    uart_putchar(UART4, temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if (temp < 10) {
    uart_putchar(UART4, temp + '0');
  } else {
    uart_putchar(UART4, temp - 10 + 'A');
  }
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SendImageData
*  功能说明：
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SendImageData(uint8 * ImageData)
{

  uint8 i;
  uint8 crc = 0;

  /* Send Data */
  uart_putchar(UART4, '*');
  uart_putchar(UART4, 'L');
  uart_putchar(UART4, 'D');

  SendHex(0);
  SendHex(0);
  SendHex(0);
  SendHex(0);

  for (i = 0; i < 128; i++) {
    SendHex(*ImageData++);
  }

  SendHex(crc);
  uart_putchar(UART4, '#');
}
/*************************************************************************
*                           蓝宙电子工作室
*
*  函数名称：SamplingDelay
*  功能说明：CCD延时程序 200ns
*  参数说明：
*  函数返回：无
*  修改时间：2012-10-20
*  备    注：
*************************************************************************/
void SamplingDelay(void)
{
  volatile uint8 i ;
  for (i = 0; i < 1; i++) {
    asm("nop");
    asm("nop");
    // asm("nop");
  }

}
