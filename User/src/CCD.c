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
  //Sampling Pixel 1~128
  for (i = 0; i < 128; i++) {
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

  //Sampling Pixel 1~128
  for (i = 0; i < 128; i++) {
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
void SendImageData(uint8 * ImageData)
{

  uint8 i, temp;
  uint8 crc = 0;

  /* Send Data */
  uart_putchar(UART4, '*');
  uart_putchar(UART4, 'L');
  uart_putchar(UART4, 'D');

  SendHex(0);
  SendHex(0);
  SendHex(0);
  SendHex(0);

  // for (i = 0; i < 128; i++) {
  //   SendHex(*ImageData++);
  // }

  for (i = 0; i < 128; i++) {
    SendHex(*ImageData * 255);
    *ImageData++;
  }

  SendHex(crc);
  uart_putchar(UART4, '#');
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
