#include"include.h"



//CCD 信息
CCD_Info ccd1_info;
CCD_Info ccd2_info;
Car_State ccd1_state;
Car_State ccd2_state;





void print_road(Car_State *state)
{
  if (Tune_Mode == 0)
  {
    if (state->now == In_Straight) printf("In_Straight->");
    else if (state->now == Into_Curva) printf("Into_Curva->");
    else if (state->now == In_Curva) printf("In_Curva->");
    else if (state->now == Into_Obstacle) printf("Into_Obstacle->");
    else if (state->now == In_Obstacle) printf("In_Obstacle->");
    else if (state->now == Out_Obstacle) printf("Out_Obstacle->");
    else if (state->now == Pre_Into_Obstacle) printf("Pre_Into_Obstacle->");
    else if (state->now == In_Crossing)printf("In_Crossing->");
  }
}


/*************************赛道状态判断*************************/
void Road_Judge(CCD_Info *ccd, Car_State *state)
{
  /**************1.在直道中****************/
  if (state->now == In_Straight)
  {
    if ((ccd->LeftLine.variance >= CURVA_THRES || ccd->RightLine.variance >= CURVA_THRES ) &&
        (ccd->LeftLine.variance < CURVA_THRES_UP || ccd->RightLine.variance < CURVA_THRES_UP ) &&
        ccd->Ec_Right.mean * ccd->Ec_Left.mean > 0)     //进弯
    {
      state->pre = state->now;
      state->now = Into_Curva;
      //方向判断
      state->direc_pre = state->direc_now;
      if (ccd->RightLine.variance > ccd->LeftLine.variance) state->direc_now = 1;    //
      else state->direc_now = -1;
      print_road(state);
    }
    else if ((ccd->LeftLine.variance < LITTLE_THRES && ccd->RightLine.variance > OBSTA_THRES && ccd->RightLine.variance < OBSTA_THRES_UP) ||
             (ccd->RightLine.variance < LITTLE_THRES && ccd->LeftLine.variance > OBSTA_THRES && ccd->LeftLine.variance < OBSTA_THRES_UP)) //进障碍
    {
      state->pre = state->now;
      state->now = Pre_Into_Obstacle;
      state->direc_pre = state->direc_now;
      //方向判断
      if (ccd->RightLine.variance < LITTLE_THRES ) state->direc_now = -1;   //障碍可能在左边
      else state->direc_now = 1;
      print_road(state);
    }
    else if (ccd->LeftLossLineFlag && ccd->RightLossLineFlag) //进十字
    {
      state->pre = state->now;
      state->now = In_Crossing;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }
  }


  /**************2.进弯中****************/
  else if (state ->now == Into_Curva)
  {
    if (reduce_spe_flag == REDUCE_COUNT)
    {
      reduce_spe_flag = 0;
      state->pre = state->now;
      state->now = In_Curva;
      state->direc_pre = state->direc_now;
      if (ccd->Ec_Left.mean > 0)state->direc_now = 1;
      else state->direc_now = -1;
      print_road(state);
    }

  }
  /**************3.在弯道里****************/
  else if (state ->now == In_Curva)
  {
    if (ccd->LeftLine.variance < LITTLE_THRES && ccd->RightLine.variance < LITTLE_THRES)  //进直道
    {
      state->pre = state->now;
      state->now = In_Straight;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }

  }

  /**************4.进十字****************/
  else if (state ->now == Pre_Into_Obstacle)
  {
    if (ccd->LeftLossLineFlag && ccd->RightLossLineFlag)
    {
      state->pre = state->now;
      state->now = Into_Obstacle;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }
  }

  /**************5.在十字中****************/
  else if (state ->now == In_Crossing)
  {
    if (!ccd->LeftLossLineFlag && !ccd->RightLossLineFlag) //进直道
    {
      state->pre = state->now;
      state->now = In_Straight;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }
  }

  /**************6.前方障碍****************/
  else if (state ->now == Into_Obstacle)
  {
    if (state->direc_now == 1) //偏右边
    {
      if (ccd->LeftLine.variance < LITTLE_THRES)
      {
        state->pre = state->now;
        state->now = In_Obstacle;
        print_road(state);
      }
    }
    if (state->direc_now == -1) //偏左边
    {
      if (ccd->RightLine.variance < LITTLE_THRES)
      {
        state->pre = state->now;
        state->now = In_Obstacle;
        print_road(state);
      }
    }
  }

  /**************7.正在过障碍****************/
  else if (state ->now == In_Obstacle)
  {
    if (state->direc_now == 1) //偏右边
    {
      if (ccd->LeftLine.variance > OBSTA_THRES)
      {
        state->pre = state->now;
        state->now = Out_Obstacle;
        state->direc_pre = state->direc_now;
        state->direc_now = -1;
        print_road(state);
      }
    }
    if (state->direc_now == -1) //偏左边
    {
      if (ccd->RightLine.variance > OBSTA_THRES && ccd->RightLine.variance < OBSTA_THRES_UP)
      {
        state->pre = state->now;
        state->now = Out_Obstacle;
        state->direc_pre = state->direc_now;
        state->direc_now = 1;
        print_road(state);
      }
    }
  }


  /**************8.出障碍****************/
  else
  {
    if (ccd->LeftLine.variance < LITTLE_THRES && ccd->RightLine.variance < LITTLE_THRES)  //进直道
    {
      state->pre = state->now;
      state->now = In_Straight;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }
  }


}// Road_Judge(CCD_Info *ccd)


/*************************赛道信息数据处理*************************/
void Road_Data_Update(CCD_Info * ccd, uint8 LeftValue, uint8 RightValue)
{
  Info_queue *left_temp, *left_temp_ec;
  Info_queue *right_temp, *right_temp_ec;
  left_temp = &ccd->LeftLine;
  left_temp_ec = &ccd->Ec_Left;

  qhead = QRANGE(qhead + 1); //先把队头移到队尾
  left_temp->node[qhead] = LeftValue;  //队头赋值
  left_temp_ec->node[qhead] = left_temp->node[qhead] - left_temp->node[QRANGE(qhead - 1)]; //这次值减去上次即是变化量

  left_temp->mean = Queue_Mean(left_temp);  //左边均值
  left_temp->variance = Queue_Variance(left_temp);//左边方差
  left_temp_ec->mean = Queue_Mean(left_temp_ec);

//Right
  right_temp = &ccd->RightLine;
  right_temp_ec = &ccd->Ec_Right;

  right_temp->node[qhead] = RightValue;  //队头赋值
  right_temp_ec->node[qhead] = right_temp->node[qhead] - right_temp->node[QRANGE(qhead - 1)]; //这次值减去上次即是变化量

  right_temp->mean = Queue_Mean(right_temp);  //左边均值
  right_temp->variance = Queue_Variance(right_temp);//左边方差
  right_temp_ec->mean = Queue_Mean(right_temp_ec);


}



int16 Queue_Mean(Info_queue * queue)
{
  int16 result = 0;
  for (int i = 0; i < Line_SIZE; i++)
  {
    result += queue->node[i];
  }
  result = result / Line_SIZE;
  return result;
}


int16 Queue_Variance(Info_queue * queue)
{
  int16 result = 0;
  for (int i = 0; i < Line_SIZE; i++)
  {
    result += (queue->node[i] - queue->mean) * (queue->node[i] - queue->mean);
  }
  result = result / Line_SIZE;
  return result;
}
