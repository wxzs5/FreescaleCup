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

/****************************************************************************
赛道黑白基本信息变量
******************************************************************************/
uint8 White_Ahead_Flag = 0;
uint8 Black_Ahead_Flag = 0;

uint8 CCD1_flag = 0;
uint8 CCD2_flag = 0;


uint8 Pixel_Lose_ALL_Line_Flag = 1;
uint8 Pixel_Lose_Left_Flag = 1;
uint8 Pixel_Lose_Right_Flag = 1;
uint8 Pixel_Get_Left_Flag1 = 0;
uint8 Pixel_Get_Right_Flag1 = 0;
uint8 Pixel_Get_Left_Flag2 = 0;
uint8 Pixel_Get_Right_Flag2 = 0;
uint8 Pixel_Minimum_differ = 20;


uint8 Car_begin_Stop_Flag = 0;

float L_bc = 40;
float L_ab_sqr = 40;
float arc_ratio_left;
float arc_ratio_right;
float arc_ratio;

uint8 Left_Board_Value1 = 3;
uint8 Right_Board_Value1 = 124;
int8 Center_Board_Value1 = 64;

uint8 Left_Board_Value2 = 3;
uint8 Right_Board_Value2 = 124;
int8 Center_Board_Value2 = 64;

int8 Center_Board_Value = 64;

//unsigned int sum = 0;

//int8 Left_Board_Value_Last = 3;
//int8 Right_Board_Value_Last = 124;
int8 Centre_BlackOld_1 = 64;
int8 Centre_BlackOld_2 = 64;
//int8  Centre_Black = 0;

//volatile float middle_Line;
/*******************************************************************************
* Function Name  : init_ADC()
* Description    : initaization of the ADC0 channel 2(AN2)
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
uint8 Threshold_Value_Low = 153;
uint8 Threshold_Value_High = 153;
uint8 Pixel_Maximum_value = 0;
uint8 Pixel_Minimum_value = 0;
uint8 get_min_max(uint8 *Pixel_BUFFER)
{
  uint8 Pixel_MAX_BUFFER = *Pixel_BUFFER;
  uint8 Pixel_MIN_BUFFER = *Pixel_BUFFER;
  while (*Pixel_BUFFER != 0)
  {
    if (*Pixel_BUFFER > Pixel_MAX_BUFFER)
    {
      Pixel_MAX_BUFFER = *Pixel_BUFFER;
    }
    if (*Pixel_BUFFER < Pixel_MIN_BUFFER)
    {
      Pixel_MIN_BUFFER = *Pixel_BUFFER;
    }
    Pixel_BUFFER++;
  }
  Pixel_Maximum_value = Pixel_MAX_BUFFER;
  Pixel_Minimum_value = Pixel_MIN_BUFFER;
  if (Pixel_Minimum_value > Threshold_Value_Low)
  {
    White_Ahead_Flag = 1;
    Black_Ahead_Flag = 0;
    return 1;
  }
  else
  {
    if (Pixel_Maximum_value < Threshold_Value_High)
    {
      White_Ahead_Flag = 0;
      Black_Ahead_Flag = 1;
      return 2;
    }
    else
    {
      White_Ahead_Flag = 0;
      Black_Ahead_Flag = 0;
      return 0;
    }
  }
}
/*******************************************************************************
* Function Name  : binary_conversion(voi
* Description    : conversion the AD value to binary code
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
uint8 Threshold_Value = 210;
uint8 binary_conversion(uint8 *value_des, uint8 *value_scr)
{
  for (uint8 i = 0; i < 127; i++)
  {
    if (*value_scr > Threshold_Value)
    {
      *value_des = 0xFF;
    }
    else
    {
      *value_des = 0;
    }
    value_scr++;
    value_des++;
  }
  return 1;
}
//    unsigned int Pixel_counter=0;
/*switch (get_min_max(Pixel_1))
{
case 1:
{
  for (uint8 i = 0; i < 127; i++)
  {
    *value_des = 0xFF;
    value_des++;
  }
  return 0;
  break;
}
case 2:
{
  for (uint8 i = 0; i < 127; i++)
  {
    *value_des = 0x00;
    value_des++;
  }
  return 0;
  break;
}
case 0:
{
  for (uint8 i = 0; i < 127; i++)
  {
    if (*value_scr > Threshold_Value)
    {
      *value_des = 0xFF;
    }
    else
    {
      *value_des = 0;
    }
    value_scr++;
    value_des++;
  }
  return 1;
  break;
}
default: break;
}
return 0;*/
/*******************************************************************************
* Function Name  : void Filter_Pixel_Two(void)
* Description    : conversion the AD value to binary code
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void Filter_Pixel(uint8 *Pixel_des)
{
  uint8 *Pixel_des_L1;
  uint8 *Pixel_des_R1;
  Pixel_des_L1 = Pixel_des;
  Pixel_des++;
  Pixel_des_R1 = Pixel_des + 1;
  while (*Pixel_des_R1 != 0)
  {
    if (*Pixel_des == 0 && *Pixel_des != *Pixel_des_R1 && *Pixel_des != *Pixel_des_L1)
    {
      *Pixel_des = 0xFF;
    }
    else if (*Pixel_des == 0xFF && *Pixel_des != *Pixel_des_R1 && *Pixel_des != *Pixel_des_L1)
    {
      *Pixel_des = 0;
    }
    Pixel_des_L1++;
    Pixel_des++;
    Pixel_des_R1++;
  }
}
/*******************************************************************************
* Function Name  : void CCD_Get_Line_1(uint8 *rightblackedge,uint8 *leftblackedge,sint8 *centre_black);
* Description    :
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void CCD_Get_Line_1(uint8 *rightblackedge, uint8 *leftblackedge, int8 *centre_black)
{
  uint8 counter = 0;
  CCD1_flag = get_min_max(Pixel_1);
  binary_conversion(binary_road_1, Pixel_1);
  Filter_Pixel(binary_road_1);
  for (counter = Centre_BlackOld_1; counter > 3; counter--)
  {

    if ((!binary_road_1[counter - 2]) && (!binary_road_1[counter - 1]) && (binary_road_1[counter]) && (binary_road_1[counter + 1]))
    {
      *leftblackedge = counter;
      L_bc = 64 - counter;
      arc_ratio_left = 2 * L_bc / (L_ab_sqr + L_bc * L_bc);
      Pixel_Get_Left_Flag1 = 1;
      Pixel_Lose_Left_Flag = 0;
      //Above_Left_LED_H;
      break;
    }
    else
    {
      *leftblackedge = 3;
      Pixel_Lose_Left_Flag = 1;
      Pixel_Get_Left_Flag1 = 0;
      //Above_Left_LED_L;
    }

  }

  for (counter = Centre_BlackOld_1; counter < 125; counter++)
  {
    if (((binary_road_1[counter - 1]) && (binary_road_1[counter]) && (!binary_road_1[counter + 1]) && (!binary_road_1[counter + 2])))
    {
      *rightblackedge = counter;
      L_bc = counter - 64;
      arc_ratio_right = 2 * L_bc / (L_ab_sqr + L_bc * L_bc);
      Pixel_Get_Right_Flag1 = 1;
      Pixel_Lose_Right_Flag = 0;
      //Above_Right_LED_H;
      break;
    }
    else
    {
      *rightblackedge = 124;
      Pixel_Lose_Right_Flag = 1;
      Pixel_Get_Right_Flag1 = 0;
      //Above_Right_LED_L;
    }

  }
  if (Pixel_Lose_Right_Flag && Pixel_Lose_Left_Flag) *centre_black = Centre_BlackOld_1;
  else *centre_black = (int8)((*leftblackedge + *rightblackedge) / 2);
  Centre_BlackOld_1 = *centre_black;
  //Centre_Black = (int8)(*centre_black - 64);

  // if (*centre_black < 20)*centre_black = 20;
  // if (*centre_black > 107)*centre_black = 107;
}
/*******************************************************************************
* Function Name  : void CCD_Get_Line(uint8 *rightblackedge,uint8 *leftblackedge,sint8 *centre_black);
* Description    :
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void CCD_Get_Line_2(uint8 *rightblackedge, uint8 *leftblackedge, int8 *centre_black)
{
  uint8 counter = 0;
  CCD2_flag = get_min_max(Pixel_2);
  binary_conversion(binary_road_2, Pixel_2);
  Filter_Pixel(binary_road_2);
  for (counter = Centre_BlackOld_2; counter > 3; counter--)
  {

    if ((!binary_road_2[counter - 2]) && (!binary_road_2[counter - 1]) && (binary_road_2[counter]) && (binary_road_2[counter + 1]))
    {
      *leftblackedge = counter;
      Pixel_Get_Left_Flag2 = 1;
      Pixel_Lose_Left_Flag = 0;
      //Above_Left_LED_H;
      break;
    }
    else
    {
      *leftblackedge = 3;
      Pixel_Lose_Left_Flag = 1;
      Pixel_Get_Left_Flag2 = 0;
      //Above_Left_LED_L;
    }

  }

  for (counter = Centre_BlackOld_2; counter < 125; counter++)
  {
    if (((binary_road_2[counter - 1]) && (binary_road_2[counter]) && (!binary_road_2[counter + 1]) && (!binary_road_2[counter + 2])))
    {
      *rightblackedge = counter - 1;
      Pixel_Get_Right_Flag2 = 1;
      Pixel_Lose_Right_Flag = 0;
      //Above_Right_LED_H;
      break;
    }
    else
    {
      *rightblackedge = 124;
      Pixel_Lose_Right_Flag = 1;
      Pixel_Get_Right_Flag2 = 0;
      //Above_Right_LED_L;
    }

  }
  // if (Pixel_Lose_Right_Flag) ;
  // else if (Pixel_Lose_Left_Flag) ;
  // else
  if (Pixel_Lose_Right_Flag && Pixel_Lose_Left_Flag) *centre_black = Centre_BlackOld_2;
  *centre_black = (int8)((*leftblackedge + *rightblackedge) / 2);
  Centre_BlackOld_2 = *centre_black;
  // Centre_Black = (int8)(*centre_black - 64);

  // if (*centre_black < 20)*centre_black = 20;
  // if (*centre_black > 107)*centre_black = 107;
}

/*******************************************************************************
* Function Name  : void give_image(uint8 *ImageData1,uint8 *ImageData2)
* Description    : get image
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void give_image(uint8 *ImageData1, uint8 *ImageData2)
{
  //while(*ImageData2 !=0)
  uint8 image_counter = 0;
  for (image_counter = 0; image_counter < 128; image_counter++)
  {
    *ImageData1 = *ImageData2;
    ImageData1++;
    ImageData2++;
  }
}


