/********************************************************************************
*     COPYRIGHT NOTICE
*     Copyright (c) 2015, Ibrahim
*     All rights reserved.
*
*********************************************************************************
* @file       PIT0.c
* @brief      野火K60 平台主程序
* @author     Ibrahim
* @version    v5.0
* @date       2015 - 10 - 18
*********************************************************************************/
#include "include.h"
int16 Center_Board_Value = 64;

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void myCCD_DataInit(CCD_Info * CCD_info);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void myCCD_DataInit(CCD_Info *CCD_info)
{
  uint8 ii = 0, jj = 0;

  for (ii = 0; ii < 2; ii++)
  {
    for (jj = 0; jj < 20; jj++)
    {
      CCD_info->PixelOri[ii][jj] = 0;
      CCD_info->PixelOri[ii][127 - jj] = 0;
    }

    for (jj = 20; jj < 107; jj++)
    {
      CCD_info->PixelOri[ii][jj] = 255;
    }
  }

  for (ii = 0; ii < 128; ii++)
  {
    CCD_info->Pixel[ii] = 255;
    CCD_info->PixelBinary[ii] = 0;
  }

  CCD_info->CCD_PhotoCenter = 64;
  CCD_info->CCD_ObstacleShift = 22;          //默认偏移两个点
  CCD_info->CCD_CrossShift = 30;
  CCD_info->Cross_Shift_Counter = 4;
  CCD_info->Cross_state = 0;

  for (ii = 0; ii < Line_SIZE; ii++)
  {
    CCD_info->LeftLine[ii] = 0;
    CCD_info->RightLine[ii] = 0;
    CCD_info->CentralLine[ii] = 64;
    CCD_info->LineError[ii] = 0;
    CCD_info->LineError_D[ii] = 0;
  }

  //CCD_info->LeftLossLinePixel = 0;
  //CCD_info->RightLossLinePixel = 0;
  CCD_info->LeftLossLineFlag = 0;
  CCD_info->RightLossLineFlag = 0;

  for (ii = 0; ii < 10; ii++)
  {
    CCD_info->RoadWidth[ii] = 50;
  }

  CCD_info->RoadWidthOfStraight = 70;

  CCD_info->LeftLine[0] = 28;
  CCD_info->RightLine[0] = 100;

  for (ii = 0; ii < 4; ii++)
  {
    CCD_info->AD_MAX[ii] = 255;
    CCD_info->AD_MIN[ii] = 0;
  }

  for (ii = 0; ii < 16; ii++)
  {
    CCD_info->CCD_PhotoValue[ii] = 0;
  }


  CCD_info->CCD_Ready_Num = 0;

  CCD_info->AddLine_Flag = 0;     //补线标记
  CCD_info->LossLine_Flag = 0;    //丢线标记
  CCD_info->Cross_Flag = 0;     //十字道标记
  CCD_info->RoadInvalid_Flag = 0;

  CCD_info->Left_Mean = 0;
  CCD_info->Left_Variance = 0;
  CCD_info->Right_Mean = 0;
  CCD_info->Right_Variance = 0;
}

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void myCCD_DataInit(CCD_Info * CCD_info);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void myCCD_FilterAndBinarization(CCD_Info *CCD1_info, CCD_Info *CCD2_info)
{
  uint8 ii = 0;
  uint8 AD1_MAX = 0, AD2_MAX = 0;
  uint8 AD1_MIN = 255, AD2_MIN = 255;
  uint16 ADD_buf = 0;
  uint8 BinaryEdgeValue1 = 150, BinaryEdgeValue2 = 150;


  //进行CCD数据采集滤波
  for (ii = 0; ii < 128; ii++)//60us
  {
    //CCD1_info->Pixel[ii] = (CCD1_info->PixelOri[0][ii] + CCD1_info->PixelOri[1][ii]) >> 1;
    CCD1_info->Pixel[ii] = CCD1_info->PixelOri[0][ii];
    if (CCD1_info->Pixel[ii] > AD1_MAX) AD1_MAX = CCD1_info->Pixel[ii];
    if (CCD1_info->Pixel[ii] < AD1_MIN) AD1_MIN = CCD1_info->Pixel[ii];
    //CCD2_info->Pixel[ii] = (CCD2_info->PixelOri[0][ii] + CCD2_info->PixelOri[1][ii]) >> 1;
    CCD2_info->Pixel[ii] = CCD2_info->PixelOri[0][ii];
    if (CCD2_info->Pixel[ii] > AD2_MAX) AD2_MAX = CCD2_info->Pixel[ii];
    if (CCD2_info->Pixel[ii] < AD2_MIN) AD2_MIN = CCD2_info->Pixel[ii];

    //移动CCD1原始数据队列
    CCD1_info->PixelOri[1][ii] = CCD1_info->PixelOri[0][ii];

    //移动CCD2原始数据队列
    CCD2_info->PixelOri[1][ii] = CCD2_info->PixelOri[0][ii];

    //去CCD1暗电流
    /*if (CCD1_info->Pixel[ii] > CCD_Dark_Current)
    {
       CCD1_info->Pixel[ii] = CCD1_info->Pixel[ii] - CCD_Dark_Current;
    }
      else
    {
       CCD1_info->Pixel[ii] = 0;
    }*/

    //去CCD2暗电流
    /*if (CCD2_info->Pixel[ii] > CCD_Dark_Current)
    {
       CCD2_info->Pixel[ii] = CCD2_info->Pixel[ii] - CCD_Dark_Current;
    }
      else
    {
       CCD2_info->Pixel[ii] = 0;
    }*/
  }
  CCD1_info->AD_MAX[3] = CCD1_info->AD_MAX[2];
  CCD1_info->AD_MAX[2] = CCD1_info->AD_MAX[1];
  CCD1_info->AD_MAX[1] = CCD1_info->AD_MAX[0];

  CCD1_info->AD_MIN[3] = CCD1_info->AD_MIN[2];
  CCD1_info->AD_MIN[2] = CCD1_info->AD_MIN[1];
  CCD1_info->AD_MIN[1] = CCD1_info->AD_MIN[0];
  //更新AD_MAX,AD_MIN队列
  CCD1_info->AD_MAX[0] = AD1_MAX;
  CCD1_info->AD_MIN[0] = AD1_MIN;

  CCD2_info->AD_MAX[3] = CCD2_info->AD_MAX[2];
  CCD2_info->AD_MAX[2] = CCD2_info->AD_MAX[1];
  CCD2_info->AD_MAX[1] = CCD2_info->AD_MAX[0];

  CCD2_info->AD_MIN[3] = CCD2_info->AD_MIN[2];
  CCD2_info->AD_MIN[2] = CCD2_info->AD_MIN[1];
  CCD2_info->AD_MIN[1] = CCD2_info->AD_MIN[0];
  //更新AD_MAX,AD_MIN队列
  CCD2_info->AD_MAX[0] = AD2_MAX;
  CCD2_info->AD_MIN[0] = AD2_MIN;

  //计算CCD1二值化的分界值
  ADD_buf = (   CCD1_info->AD_MAX[3] + CCD1_info->AD_MAX[2] + CCD1_info->AD_MAX[1] + CCD1_info->AD_MAX[0]
                + CCD1_info->AD_MIN[3] + CCD1_info->AD_MIN[2] + CCD1_info->AD_MIN[1] + CCD1_info->AD_MIN[0]
            ) >> 3;
  if (ADD_buf < 255) BinaryEdgeValue1 = (uint8)ADD_buf;
  else BinaryEdgeValue1 = 255;

  //计算CCD2二值化的分界值
  ADD_buf = (   CCD2_info->AD_MAX[3] + CCD2_info->AD_MAX[2] + CCD2_info->AD_MAX[1] + CCD2_info->AD_MAX[0]
                + CCD2_info->AD_MIN[3] + CCD2_info->AD_MIN[2] + CCD2_info->AD_MIN[1] + CCD2_info->AD_MIN[0]
            ) >> 3;
  if (ADD_buf < 255) BinaryEdgeValue2 = (uint8)ADD_buf;
  else BinaryEdgeValue2 = 255;

  //限制二值化边界值的最大值最小值(阈值在750左右)
  MYRANGE(BinaryEdgeValue1, CCD_Binary_MAX, CCD_Binary_MIN);

  //CCD数据的二值化
  for (ii = 0; ii < 128; ii++)
  {
    CCD1_info->PixelBinary[ii] = (CCD1_info->Pixel[ii] >= BinaryEdgeValue1) ? 1 : 0;//CCD1数据二值化
    CCD2_info->PixelBinary[ii] = (CCD2_info->Pixel[ii] >= BinaryEdgeValue2) ? 1 : 0;//CCD2数据二值化
  }
}
/*******************************************************************************
* Function Name  : void Filter_Pixel_Two(void)
* Description    : conversion the AD value to binary code
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void Filter_binary(CCD_Info *CCD1_info, CCD_Info *CCD2_info)
{
  uint8 ii = 0;
  //CCD二值化数据滤波处理
  for (ii = 0; ii < 127; ii++)
  {
    if (CCD1_info->PixelBinary[ii + 1] == 0
        && CCD1_info->PixelBinary[ii + 1] != CCD1_info->PixelBinary[ii]
        && CCD1_info->PixelBinary[ii + 1] != CCD1_info->PixelBinary[ii + 2])
    {
      CCD1_info->PixelBinary[ii + 1] = 1;
    }
    else if (CCD1_info->PixelBinary[ii + 1] == 1
             && CCD1_info->PixelBinary[ii + 1] != CCD1_info->PixelBinary[ii]
             && CCD1_info->PixelBinary[ii + 1] != CCD1_info->PixelBinary[ii + 2])
    {
      CCD1_info->PixelBinary[ii + 1] = 0;
    }
  }
}

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void myCCD_DataInit(CCD_Info * CCD_info);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void myCCD_FilterAtFirst(CCD_Info *CCD1_info, CCD_Info *CCD2_info)
{
  int16_t ii = 0;

  //初始化移动CCD数据数组
  for (ii = 0; ii < 128; ii++)
  {
    //移动CCD1原始数据队列
    CCD1_info->PixelOri[1][ii] = CCD1_info->PixelOri[0][ii];

    //移动CCD2原始数据队列
    CCD2_info->PixelOri[1][ii] = CCD2_info->PixelOri[0][ii];
  }
}

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void myCCD_DataInit(CCD_Info * CCD_info);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void myCCD_GetBeginLineError( CCD_Info *CCD1_info,
                              CCD_Info *CCD2_info,
                              Speed_Info *Speed_info
                            )
{
  uint8_t ii = 0;

  //CCD数据的头几次滤波处理
  ii = 5;
  do
  {
    myCCD_FilterAtFirst(CCD1_info, CCD2_info);
    ii--;
  } while (ii > 0);

  //起跑时的偏差计算和移动
  ii = Line_SIZE;
  do
  {
    //数据滤波 二值化
    myCCD_FilterAndBinarization(CCD1_info, CCD2_info);
    Filter_binary(CCD1_info, CCD2_info);

    //CCD搜边线和偏差计算
    myCCD_CCD1_GetLineError(CCD1_info, Speed_info);
    myCCD_CCD2_GetLineError(CCD2_info);
    ii--;
  } while (ii > 0);

  CCD1_info->RoadWidthOfStraight = CCD1_info->RightLine[0] - CCD1_info->LeftLine[0];
  CCD2_info->RoadWidthOfStraight = CCD2_info->RightLine[0] - CCD2_info->LeftLine[0];


}
/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void myCCD_DataHandle(  CCD_Info *CCD1_info,
                                      CCD_Info *CCD2_info,
                                      Speed_Info *Speed_info
                                    )
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void myCCD_DataHandle(  CCD_Info *CCD1_info,
                        CCD_Info *CCD2_info,
                        Speed_Info *Speed_info
                     )
{
  //数据滤波 二值化
  myCCD_FilterAndBinarization(CCD1_info, CCD2_info);
  Filter_binary(CCD1_info, CCD2_info);

  //CCD搜边线和偏差计算

  myCCD_CCD1_GetLineError(CCD1_info, Speed_info);
  myCCD_CCD2_GetLineError(CCD2_info);

  Queue_Mean(CCD1_info);
  Queue_Variance(CCD1_info);

  if (CCD1_info->LossLine_Flag != 1)
  {
    if (CCD1_info->Cross_state == 1) CCD1_info->Cross_state = 2;
    else if (CCD1_info->Cross_state == 3)CCD1_info->Cross_state = 0;

    Center_Board_Value = CCD1_info->CentralLine[0];
    Bell_Off;
  }
  else if (CCD1_info->AddLine_Flag == 1)
  {
    Center_Board_Value = (CCD1_info->LeftLine[0] + CCD1_info->RightLine[0]) / 2;
  }
  else if ( CCD1_info->Cross_Flag == 1 )
  {
    //Center_Board_Value = 64;
    Car_state.pre = Car_state.now;      //下坡
    Car_state.now = In_Crossing;

    // Center_Board_Value = (CCD1_info.LeftLine[0] + CCD1_info.RightLine[0]) / 2;
    if (CCD1_info->Cross_state == 0)
    {
      CCD1_info->Cross_state = 1;
      Center_Board_Value = (CCD1_info->LeftLine[0] + CCD1_info->RightLine[0]) / 2;
    }
    else if (CCD1_info->Cross_state == 2)
    {
      // Bell_On;
      CCD1_info->Cross_state = 3;
      if (CCD1_info->CentralLine[6] - 64 < -5) Center_Board_Value = 64 - CCD1_info->CCD_CrossShift;
      else if (CCD1_info->CentralLine[6] - 64 > 5) Center_Board_Value = 64 + CCD1_info->CCD_CrossShift;
      else Center_Board_Value = (CCD1_info->LeftLine[0] + CCD1_info->RightLine[0]) / 2;
    }
  }
  if (Gyro_info.RampUpDown != 1)
  {
    //障碍处理
    switch (myCCD_GetObstacle(CCD1_info, CCD2_info))
    {
    case 1:
    {
      CCD1_info->CentralLine[0] = CCD1_info->CentralLine[0] + CCD1_info->CCD_ObstacleShift;
      Car_state.pre = Car_state.now;
      Car_state.now = Into_Obstacle;
      Bell_On;
      break;
    }
    case 2:
    {
      CCD1_info->CentralLine[0] = CCD1_info->CentralLine[0] - CCD1_info->CCD_ObstacleShift;
      Car_state.pre = Car_state.now;
      Car_state.now = Into_Obstacle;
      Bell_On;
      break;
    }
    case 0:
    {
      break;
    }
    default:            //不需要处理 cancel
      break;
    }
  }
  // switch (myCCD_detect_startline(CCD1_info, CCD2_info))
  // {
  // case 1:
  // {
  //   Speed_Expect = 0;
  // }
  // case 0:
  // {
  //   break;
  // }
  // default:            //不需要处理 cancel
  //   break;
  // }
}
/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void myCCD_DataInit(CCD_Info * CCD_info);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void myCCD_CCD1_GetLineError(CCD_Info *CCD1_info, Speed_Info *Speed_info)
{
  int16 CentralLinePixel_Now = CCD1_info->CentralLine[0];//从上次的中点开始搜线
  int16 LinePixel_Temp = CentralLinePixel_Now;

  int16 Left_temp = 0, Right_temp = 0;
  int16 ii = 0;

  //清零标记
  CCD1_info->LossLine_Flag = 0;
  CCD1_info->Cross_Flag  = 0;
  CCD1_info->AddLine_Flag = 0;
  CCD1_info->LeftLossLineFlag = 1;
  CCD1_info->RightLossLineFlag = 1;

  /*------------------左边线------------------------*/
  for (ii = LinePixel_Temp; ii > 3; ii--)
  {
    if ((CCD1_info->PixelBinary[ii - 2] == 0) && (CCD1_info->PixelBinary[ii - 1] == 0) && (CCD1_info->PixelBinary[ii] == 1))
    {
      Left_temp = ii;
      CCD1_info->LeftLossLineFlag = 0;
      break;
    }
  }
  /*if (Left_temp == 3)
  {
    CCD1_info->LeftLossLineFlag = 1;
  }*/
  if (ii == 3)
  {
    Left_temp = ii;
    CCD1_info->LeftLossLineFlag = 1;
  } 

  /*-------------------右边线------------------------*/
  for (ii = LinePixel_Temp; ii < 125; ii++)
  {
    if ((CCD1_info->PixelBinary[ii] == 1) && (CCD1_info->PixelBinary[ii + 1] == 0) && (CCD1_info->PixelBinary[ii + 2] == 0))
    {
      Right_temp = ii;
      CCD1_info->RightLossLineFlag = 0;
      break;
    }
  }
  /*if (Right_temp == 125)
  {
    CCD1_info->RightLossLineFlag = 1;
  }*/
  if (ii == 125)
  {
    Right_temp = ii;
    CCD1_info->RightLossLineFlag = 1;
  } 

  /*------------------------------移动队列---------------------------------*/
  for (ii = Line_SIZE - 1; ii > 0; ii--)
  {
    CCD1_info->LeftLine[ii]    = CCD1_info->LeftLine[ii - 1];
    CCD1_info->RightLine[ii]   = CCD1_info->RightLine[ii - 1];
    CCD1_info->CentralLine[ii] = CCD1_info->CentralLine[ii - 1];
    CCD1_info->LineError[ii]   = CCD1_info->LineError[ii - 1];
    CCD1_info->LineError_D[ii] = CCD1_info->LineError_D[ii - 1];
  }

  /*------------------------------普通弯道往左补线-------------------------------*/
  if ((CCD1_info->LeftLossLineFlag == 1) && (CCD1_info->RightLossLineFlag == 0))//限制右边界范围
  {
    // Bell_On;

    CCD1_info->AddLine_Flag = 1;

    CCD1_info->LeftLine[0]  = Right_temp -  (CCD1_info->RoadWidth[0]);
    CCD1_info->RightLine[0] = Right_temp;

    if (((CCD1_info->LeftLine[0] + CCD1_info->RightLine[0]) >> 1) > CCD1_info->CCD_PhotoCenter)//防止在弯道入十字的时候补线错误
    {
      CCD1_info->LeftLine[0] = CCD1_info->LeftLine[1];
      CCD1_info->RightLine[0] = CCD1_info->RightLine[1];
    }
  }
  /*------------------------------普通弯道往右补线-------------------------------*/
  if ((CCD1_info->LeftLossLineFlag == 0) && (CCD1_info->RightLossLineFlag == 1))//限制左边界范围
  {

//    Bell_On;
    CCD1_info->AddLine_Flag = 1;

    CCD1_info->RightLine[0] = Left_temp + (CCD1_info->RoadWidth[0]);
    CCD1_info->LeftLine[0]  = Left_temp;

    if (((CCD1_info->LeftLine[0] + CCD1_info->RightLine[0]) >> 1) < CCD1_info->CCD_PhotoCenter)//防止在弯道入十字的时候补线错误
    {
      CCD1_info->LeftLine[0] = CCD1_info->LeftLine[1];
      CCD1_info->RightLine[0] = CCD1_info->RightLine[1];
    }
  }

  /*------------------------------十字道和正常赛道-------------------------------*/
  if (CCD1_info->AddLine_Flag == 0)//没有进行补线
  {
    //正常赛道

    if ((CCD1_info->LeftLossLineFlag == 0) && (CCD1_info->RightLossLineFlag == 0))
    {
//      Bell_Off;
      CCD1_info->LeftLine[0] = Left_temp;
      CCD1_info->RightLine[0] = Right_temp;
      CCD1_info->LossLine_Flag = 0;
      CCD1_info->CCD_Ready_Num++;//CCD1数据有效次数自加

      /*if ((1 == Speed_info->DistanceOf1Cm_Flag) && (CCD1_info->CCD_Ready_Num < CCD1_DataReady_Num))//1cm到了,清零1cm标志放在更新摇头舵机偏差队列之后
      {
        CCD1_info->CCD_Ready_Num++;//CCD1数据有效次数自加
      }*/

      //CCD1_info->LeftLoseLine_Flag = 0;
      //CCD1_info->RightLoseLine_Flag = 0;
    }
    else//可能是十字道,坡道和全黑丢线,停止更新左右边界值
    {
      CCD1_info->LossLine_Flag = 1;
      // Bell_On;
      //判断十字道，十字道不清除CCD1的有效次数
      if (  (1 == CCD1_info->PixelBinary[LinePixel_Temp])          //此处要加坡道！！！！！！！！！
            && (1 == CCD1_info->PixelBinary[LinePixel_Temp - 5])
            && (1 == CCD1_info->PixelBinary[LinePixel_Temp + 5]))//不是坡道则为十字道或者全黑丢线
      {
        CCD1_info->Cross_Flag = 1;
        CCD1_info->LeftLine[0] = Left_temp;
        CCD1_info->RightLine[0] = Right_temp;
        //CCD1_info->LeftLine[0] = CCD1_info->LeftLine[2];
        //CCD1_info->RightLine[0] = CCD1_info->RightLine[2];
      }
      else
      {
        CCD1_info->CCD_Ready_Num = 0;
      }
    }
  }

  /*------------------------------更新队列-----------------------------------------*/
  if ((CCD1_info->LossLine_Flag != 1) && (CCD1_info->RightLine[0] - CCD1_info->LeftLine[0]) >= ROAD_WIDETH_1_MIN)//限制路宽
  {
    CCD1_info->CentralLine[0] = (CCD1_info->LeftLine[0] + CCD1_info->RightLine[0]) / 2;
    CCD1_info->LineError[0] = CCD1_info->CentralLine[0] - CCD1_info->CCD_PhotoCenter;
    CCD1_info->LineError_D[0] = CCD1_info->LineError[0] - CCD1_info->LineError[8];

    /*if ((Ramp_Up == Road_condition) || (Ramp_Down == Road_condition))//坡道使用CCD1，不允许舵机有很大的打角且不允许偏差突变
    {
      if((fabs(CCD1_info->CentralLine[0] - CCD1_info->CentralLine[1]) > 5)
        || (fabs(CCD1_info->LineError[0]) > 15))
      {
        CCD1_info->LeftLine[0] = CCD1_info->LeftLine[1];
        CCD1_info->RightLine[0] = CCD1_info->RightLine[1];

        CCD1_info->CentralLine[0] = (CCD1_info->LeftLine[0] + CCD1_info->RightLine[0]) >> 1;
        CCD1_info->LineError[0] = CCD1_info->CentralLine[0] - Photo_Center;
        CCD1_info->LineError_D[0] = CCD1_info->LineError[0] - CCD1_info->LineError[8];

        CCD1_info->LossLine_Flag = 1;//偏差有突变时认为CCD1丢线
      }
    }*/

    if ((Right_temp - Left_temp) <= ROAD_WIDETH_1_MAX)//路宽符合规定再更新路宽，1cm更新一次
    {
      CCD1_info->RoadWidth[9] = CCD1_info->RoadWidth[8];
      CCD1_info->RoadWidth[8] = CCD1_info->RoadWidth[7];
      CCD1_info->RoadWidth[7] = CCD1_info->RoadWidth[6];
      CCD1_info->RoadWidth[6] = CCD1_info->RoadWidth[5];
      CCD1_info->RoadWidth[5] = CCD1_info->RoadWidth[4];
      CCD1_info->RoadWidth[4] = CCD1_info->RoadWidth[3];
      CCD1_info->RoadWidth[3] = CCD1_info->RoadWidth[2];
      CCD1_info->RoadWidth[2] = CCD1_info->RoadWidth[1];
      CCD1_info->RoadWidth[1] = CCD1_info->RoadWidth[0];
      CCD1_info->RoadWidth[0] = CCD1_info->RightLine[0] - CCD1_info->LeftLine[0];
    }
  }
}




/*************************************************************************
*         我要过六级
*
*  函数名称:myCCD_CCD2_GetLineError
*  功能说明:CCD2搜寻中线,求得偏差
*  参数说明:
*  函数返回:无
*  修改时间:2014-7-8
*  备    注: 从上次的中点往两边搜索低电平
*************************************************************************/
void myCCD_CCD2_GetLineError(CCD_Info * CCD2_info)
{
  int16 CentralLinePixel_Now = CCD2_info->CentralLine[0];//从上次的中点开始搜线
  int16 LinePixel_Temp = CentralLinePixel_Now;
  int16 Left_temp = 0, Right_temp = 0;
  int16 ii = 0;

  //清零标记
  CCD2_info->LossLine_Flag = 0;
  CCD2_info->Cross_Flag  = 0;
  CCD2_info->AddLine_Flag = 0;
  CCD2_info->LeftLossLineFlag = 1;
  CCD2_info->RightLossLineFlag = 1;

  /*------------------左边线------------------------*/
  for (ii = LinePixel_Temp; ii > 3; ii--)
  {
    if ((CCD2_info->PixelBinary[ii - 2] == 0) && (CCD2_info->PixelBinary[ii - 1] == 0) && (CCD2_info->PixelBinary[ii] == 1))
    {
      Left_temp = ii;
      CCD2_info->LeftLossLineFlag = 0;
      break;
    }
  }
  if (Left_temp == 3)
  {
    CCD2_info->LeftLossLineFlag = 1;
  }

  /*-------------------右边线------------------------*/
  for (ii = LinePixel_Temp; ii < 125; ii++)
  {
    if ((CCD2_info->PixelBinary[ii] == 1) && (CCD2_info->PixelBinary[ii + 1] == 0) && (CCD2_info->PixelBinary[ii + 2] == 0))
    {
      Right_temp = ii;
      CCD2_info->RightLossLineFlag = 0;
      break;
    }
  }
  if (Right_temp == 125)
  {
    CCD2_info->RightLossLineFlag = 1;
  }

  /*------------------------------移动队列---------------------------------*/
  for (ii = Line_SIZE - 1; ii > 0; ii--)
  {
    CCD2_info->LeftLine[ii]    = CCD2_info->LeftLine[ii - 1];
    CCD2_info->RightLine[ii]   = CCD2_info->RightLine[ii - 1];
    CCD2_info->CentralLine[ii] = CCD2_info->CentralLine[ii - 1];
    CCD2_info->LineError[ii]   = CCD2_info->LineError[ii - 1];
    CCD2_info->LineError_D[ii] = CCD2_info->LineError_D[ii - 1];
  }

  /*------------------------------普通弯道往左补线-------------------------------*/
  if ((CCD2_info->LeftLossLineFlag == 1) && (CCD2_info->RightLossLineFlag == 0))//限制右边界范围
  {
    // Bell_On;
    CCD2_info->AddLine_Flag = 1;
    CCD2_info->LeftLine[0]  = Right_temp -  (CCD2_info->RoadWidth[0]);
    CCD2_info->RightLine[0] = Right_temp;
    if (((CCD2_info->LeftLine[0] + CCD2_info->RightLine[0]) >> 1) > CCD2_info->CCD_PhotoCenter)//防止在弯道入十字的时候补线错误
    {
      CCD2_info->LeftLine[0] = CCD2_info->LeftLine[1];
      CCD2_info->RightLine[0] = CCD2_info->RightLine[1];
    }
  }
  /*------------------------------普通弯道往右补线-------------------------------*/
  if ((CCD2_info->LeftLossLineFlag == 0) && (CCD2_info->RightLossLineFlag == 1))//限制左边界范围
  {

//    Bell_On;
    CCD2_info->AddLine_Flag = 1;
    CCD2_info->RightLine[0] = Left_temp + (CCD2_info->RoadWidth[0]);
    CCD2_info->LeftLine[0]  = Left_temp;

    if (((CCD2_info->LeftLine[0] + CCD2_info->RightLine[0]) >> 1) < CCD2_info->CCD_PhotoCenter)//防止在弯道入十字的时候补线错误
    {
      CCD2_info->LeftLine[0] = CCD2_info->LeftLine[1];
      CCD2_info->RightLine[0] = CCD2_info->RightLine[1];
    }
  }

  /*------------------------------十字道和正常赛道-------------------------------*/
  if (CCD2_info->AddLine_Flag == 0)//没有进行补线
  {
    //正常赛道
    if ((CCD2_info->LeftLossLineFlag == 0) && (CCD2_info->RightLossLineFlag == 0))
    {
//      Bell_Off;
      CCD2_info->LeftLine[0] = Left_temp;
      CCD2_info->RightLine[0] = Right_temp;
      CCD2_info->LossLine_Flag = 0;
    }
    else//可能是十字道,坡道和全黑丢线,停止更新左右边界值
    {
      CCD2_info->LossLine_Flag = 1;
      // Bell_On;
      //判断十字道，十字道不清除CCD1的有效次数
      if (  (1 == CCD2_info->PixelBinary[LinePixel_Temp])          //此处要加坡道！！！！！！！！！
            && (1 == CCD2_info->PixelBinary[LinePixel_Temp - 3])
            && (1 == CCD2_info->PixelBinary[LinePixel_Temp + 3]))//不是坡道则为十字道或者全黑丢线
      {
        CCD2_info->Cross_Flag = 1;
      }
      //判断CCD全黑有效次数
      else if (   (0 == CCD2_info->PixelBinary[LinePixel_Temp])          //此处要加坡道！！！！！！！！！
                  && (0 == CCD2_info->PixelBinary[LinePixel_Temp - 5])
                  && (0 == CCD2_info->PixelBinary[LinePixel_Temp + 5]))
      {
        CCD2_info->CCD_Ready_Num = 0;
      }
    }
  }

  /*------------------------------更新队列-----------------------------------------*/
  if ((CCD2_info->LossLine_Flag != 1) && (CCD2_info->RightLine[0] - CCD2_info->LeftLine[0]) >= ROAD_WIDETH_1_MIN)//限制路宽
  {
    CCD2_info->CentralLine[0] = (CCD2_info->LeftLine[0] + CCD2_info->RightLine[0]) / 2;
    CCD2_info->LineError[0] = CCD2_info->CentralLine[0] - CCD2_info->CCD_PhotoCenter;
    CCD2_info->LineError_D[0] = CCD2_info->LineError[0] - CCD2_info->LineError[8];

    if ((Right_temp - Left_temp) <= ROAD_WIDETH_2_MAX)//路宽符合规定再更新路宽，1cm更新一次
    {
      CCD2_info->RoadWidth[9] = CCD2_info->RoadWidth[8];
      CCD2_info->RoadWidth[8] = CCD2_info->RoadWidth[7];
      CCD2_info->RoadWidth[7] = CCD2_info->RoadWidth[6];
      CCD2_info->RoadWidth[6] = CCD2_info->RoadWidth[5];
      CCD2_info->RoadWidth[5] = CCD2_info->RoadWidth[4];
      CCD2_info->RoadWidth[4] = CCD2_info->RoadWidth[3];
      CCD2_info->RoadWidth[3] = CCD2_info->RoadWidth[2];
      CCD2_info->RoadWidth[2] = CCD2_info->RoadWidth[1];
      CCD2_info->RoadWidth[1] = CCD2_info->RoadWidth[0];
      CCD2_info->RoadWidth[0] = CCD2_info->RightLine[0] - CCD2_info->LeftLine[0];
    }
  }
}

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      void myCCD_DataInit(CCD_Info * CCD_info);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
uint8 myCCD_GetObstacle(  CCD_Info *CCD1_info,
                          CCD_Info *CCD2_info
                       )
{
  if (  (CCD1_info->LossLine_Flag == 0)
        && (CCD2_info->LossLine_Flag == 0))
    //CCD1,CCD2没有丢边
  {
    if ((CCD1_info->RoadWidth[0] - CCD1_info->RoadWidth[6]) < -12) //CCD2路宽有突变
    {
      if ((CCD1_info->LeftLine[0] - CCD1_info->LeftLine[6] >= 10)
          && (ABS(CCD1_info->RightLine[0] - CCD1_info->RightLine[6]) < 5))//CCD1和CCD2左边界相同，右边界不同
      {
        return 1;//路障在左边
      }
      else if ((CCD1_info->RightLine[6] - CCD1_info->RightLine[0] >= 10)
               && (ABS(CCD1_info->LeftLine[0] - CCD1_info->LeftLine[6]) < 5))//CCD1和CCD2右边界相同，左边界不同
      {
        return 2;//路障在右边
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}

/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       CCD.c
* @brief      uint8 myCCD_detect_startline(CCD_Info *CCD2_info)
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
uint8 myCCD_detect_startline(CCD_Info *CCD1_info, CCD_Info *CCD2_info)
{
  int16 CentralLinePixel_Now = CCD2_info->CentralLine[0];//从上次的中点开始搜线
  int16 LinePixel_Temp = CentralLinePixel_Now;

  int16 Left_temp[3] = {0}, Right_temp[3] = {0};
  int16 ii = 0 , line_counter = 0;
  uint8 Left_startline_flag = 0, Right_startline_flag = 0 ;

  if (       CCD2_info->LossLine_Flag == 0
             && CCD2_info->AddLine_Flag == 0
             && CCD1_info->LossLine_Flag == 0
             && CCD1_info->AddLine_Flag == 0 ) //CCD1,CCD2没有丢边,且摇头很小
  {
    if ((CCD2_info->RoadWidth[0] - CCD2_info->RoadWidth[1]) < -30) //CCD1路宽有突变
    {
      /*------------------左边线------------------------*/
      for (ii = LinePixel_Temp; ii > 3; ii--)
      {
        if ((CCD2_info->PixelBinary[ii - 2] == 0) && (CCD2_info->PixelBinary[ii - 1] == 0) && (CCD2_info->PixelBinary[ii] == 1))
        {
          Left_temp[line_counter] = ii;
          line_counter++;
        }
      }
      if (line_counter == 1)
      {
        Left_startline_flag = 1;
      }
      else
      {
        Left_startline_flag = 0;
      }
      line_counter = 0;
      /*-------------------右边线------------------------*/
      for (ii = LinePixel_Temp; ii < 125; ii++)
      {
        if ((CCD2_info->PixelBinary[ii] == 1) && (CCD2_info->PixelBinary[ii + 1] == 0) && (CCD2_info->PixelBinary[ii + 2] == 0))
        {
          Right_temp[line_counter] = ii;
          line_counter++;
        }
      }
      if (line_counter == 1)
      {
        Right_startline_flag = 1;
      }
      else
      {
        Right_startline_flag = 0;
      }
      line_counter = 0;

      /*-------------------寻线结束------------------------*/
      if (Right_startline_flag == 1 && Left_startline_flag == 1)
      {
        if (ABS((Left_temp[0] + Right_temp[0]) / 2 - (Left_temp[1] + Right_temp[1]) / 2) < 5)
        {
          return 1;
        }
        else
        {
          return 0;
        }
      }
      else
      {
        return 0;
      }
    }
  }
  else
  {
    return 0;
  }
}


/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       Calculate.c
* @brief      int16 Queue_Mean(Info_queue * queue)
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void Queue_Mean(CCD_Info *CCD_info)
{
  int16 result_L = 0;
  int16 result_R = 0;
  uint8 i = 0;
  for (i = 0; i < Line_SIZE; i++)
  {
    result_L += CCD_info->LeftLine[i];
    result_R += CCD_info->RightLine[i];
  }
  CCD_info->Left_Mean = result_L / Line_SIZE;
  CCD_info->Right_Mean = result_R / Line_SIZE;
}


/*********************************************************************************
*                               我要过六级                                       *
**********************************************************************************
* @file       Calculate.c
* @brief      int16 Queue_Variance(Info_queue * queue)
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
void Queue_Variance(CCD_Info *CCD_info)
{
  int16 result_L = 0;
  int16 result_R = 0;
  for (int i = 0; i < Line_SIZE; i++)
  {
    result_L += (CCD_info->LeftLine[i] - CCD_info->Left_Mean) * (CCD_info->LeftLine[i] - CCD_info->Left_Mean);
    result_R += (CCD_info->RightLine[i] - CCD_info->Right_Mean) * (CCD_info->RightLine[i] - CCD_info->Right_Mean);
  }
  CCD_info->Left_Variance = result_L / Line_SIZE;
  CCD_info->Right_Variance = result_R / Line_SIZE;
}




