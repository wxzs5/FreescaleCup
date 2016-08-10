/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      CCD调试
           CCD1
              SI->PTE28
              CLK->PTE26
              ADC->ADC0_DM1
           CCD2
              SI->PTE24
              CLK->PTE25
              ADC->ADC0_DM0
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
#include "include.h"

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void CCD1_init(void);
              SI->PTE28
              CLK->PTE26
              ADC->ADC0_DM1

* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void CCD1_init(void)
{
  gpio_init(PTE28, GPO, 1);        //SI
  gpio_init(PTE26, GPO, 1);        //CLK
  adc_init(ADC0_DM1);

}

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void CCD2_init(void);
              SI->PTE24
              CLK->PTE25
              ADC->ADC0_DM0

* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void CCD2_init(void)
{
  gpio_init(PTE24, GPO, 1);        //SI
  gpio_init(PTE25, GPO, 1);        //CLK
  adc_init(ADC0_DM0);

}

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void CCD1_StartIntegration(void);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
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

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void CCD2_StartIntegration(void);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
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

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void CCD1_ImageCapture(CCD_Info *CCD_info);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void CCD1_ImageCapture(CCD_Info *CCD_info)
{
  uint8 i = 0;
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
  CCD_info->PixelOri[0][0] = adc_once(ADC0_DM1, ADC_8bit);
  CCD1_CLK_ClrVal();           /* CLK = 0 */

  //Sampling Pixel 1~128
  for (i = 1; i < 128; i++) {
    SamplingDelay();
    SamplingDelay();
    CCD1_CLK_SetVal();         /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();

    CCD_info->PixelOri[0][i] = adc_once(ADC0_DM1, ADC_8bit);

    CCD1_CLK_ClrVal();         /* CLK = 0 */
  }
  SamplingDelay();
  SamplingDelay();
  CCD1_CLK_SetVal();           /* CLK = 1 */
  SamplingDelay();
  SamplingDelay();
  CCD1_CLK_ClrVal();           /* CLK = 0 */
}

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void CCD2_ImageCapture(CCD_Info *CCD_info);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void CCD2_ImageCapture(CCD_Info *CCD_info)
{
  uint8 i = 0;
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
  CCD_info->PixelOri[0][0] = adc_once(ADC0_DM0, ADC_8bit);
  CCD1_CLK_ClrVal();           /* CLK = 0 */

  //Sampling Pixel 1~128
  for (i = 1; i < 128; i++) {
    SamplingDelay();
    SamplingDelay();
    CCD2_CLK_SetVal();         /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();

    CCD_info->PixelOri[0][i] = adc_once(ADC0_DM0, ADC_8bit);
    CCD2_CLK_ClrVal();         /* CLK = 0 */
  }
  SamplingDelay();
  SamplingDelay();
  CCD2_CLK_SetVal();           /* CLK = 1 */
  SamplingDelay();
  SamplingDelay();
  CCD2_CLK_ClrVal();           /* CLK = 0 */
}

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void SendHex(uint8 hex);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
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

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void SendImageData(uint8 * ImageData);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void SendImageData(uint8 * ImageData, uint8 id)
{

  uint8 sub1 = 'y', sub2 = 'z';
  uint8 head = '*';

  /* Send Data */
  // uart_putchar(UART4, '*');
  // uart_putchar(UART4, 'L');
  // uart_putchar(UART4, 'D');

  // SendHex(0);
  // SendHex(0);
  // SendHex(0);
  // SendHex(0);

  // for (i = 0; i < 128; i++) {
  //   SendHex(*ImageData++);
  // }
  if (id == 1)
  {
    UART_SendWithDMA(HW_DMA_CH2, &head, 1);
    while (DMA_IsMajorLoopComplete(HW_DMA_CH2));
    UART_SendWithDMA(HW_DMA_CH2, &sub2, 1);
    while (DMA_IsMajorLoopComplete(HW_DMA_CH2));
  }
  else
  {
    UART_SendWithDMA(HW_DMA_CH2, &head, 1);
    while (DMA_IsMajorLoopComplete(HW_DMA_CH2));
    UART_SendWithDMA(HW_DMA_CH2, &sub1, 1);
    while (DMA_IsMajorLoopComplete(HW_DMA_CH2));
  }
  UART_SendWithDMA(HW_DMA_CH2, (const uint8_t*)ImageData, 128);
  while (DMA_IsMajorLoopComplete(HW_DMA_CH2));

  // SendHex(crc);
  // uart_putchar(UART4, '#');
}
/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void SamplingDelay(void);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void SamplingDelay(void)
{
  asm("nop");
  asm("nop");
}
/*!
 *  @brief      山外多功能调试助手上位机，线性CCD显示函数
 *  @param      ccdaddr    CCD图像起始地址
 *  @param      ccdsize    CCD图像占用空间的大小
 *  @since      v5.0
*  Sample usage:
             具体用法参考这帖子:
            【山外线性CCD】上位机显示例程和超广角采集效果 - 智能车资料区
             http://vcan123.com/forum.php?mod=viewthread&tid=6340&ctid=27
 */
void vcan_sendccd2(void *ccdaddr1, void *ccdaddr2, uint32_t ccdsize)
{
#define CMD_CCD     2
  uint8_t cmdf[2] = {CMD_CCD, ~CMD_CCD};    //开头命令
  uint8_t cmdr[2] = {~CMD_CCD, CMD_CCD};    //结尾命令

  uart_putbuff(VCAN_PORT, cmdf, sizeof(cmdf));    //先发送命令

  uart_putbuff(VCAN_PORT, (uint8_t *)ccdaddr1, ccdsize); //再发送图像

  uart_putbuff(VCAN_PORT, (uint8_t *)ccdaddr2, ccdsize); //再发送图像

  uart_putbuff(VCAN_PORT, cmdr, sizeof(cmdr));    //再发送命令
}
