#include"include.h"





void print_road(Car_State *state)
{
  if (Tune_Mode == 0)
  {
    // if (state->now == In_Straight) printf("In_Straight->");
    // else if (state->now == Into_Curva) printf("Into_Curva->");
    // else if (state->now == In_Curva) printf("In_Curva->");
    // else if (state->now == Into_Obstacle) printf("Into_Obstacle->");
    // else printf("In_Crossing->");
  }
}


/*************************赛道状态判断*************************/
void Road_Judge(CCD_Info *ccd, Car_State *state)
{
  /**************1.在直道中****************/
  if (state->now == In_Straight)
  {

    Speed_Expect = Speed_info.Straight_Speed;

    if ((ccd->Left_Variance >= ccd->Curva_Thres || ccd->Right_Variance >= ccd->Curva_Thres  ) &&
        (ccd->Left_Variance < ccd->Curva_Thres_Up || ccd->Right_Variance < ccd->Curva_Thres_Up ) )//&&
      //ccd->Ec_Right_Mean * ccd->Ec_Left_Mean > 0)     //进弯
    {

      Speed_Expect = Speed_info.Into_Cur_Speed;

      state->pre = state->now;
      state->now = Into_Curva;
      //方向判断
      state->direc_pre = state->direc_now;
      if (ccd->Right_Variance > ccd->Left_Variance) state->direc_now = 1;    //
      else state->direc_now = -1;
      print_road(state);
    }


    else if (ccd->Cross_Flag == 1) //进十字
    {
      state->pre = state->now;
      state->now = In_Crossing;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }


    /*****************************单独讨论进障碍***************************/

//情况1   障碍在右边
    else if (ccd->Left_Variance < ccd->Little_Thres &&
             ccd->Right_Variance > ccd->Obstacle_Thres &&
             ccd->Right_Variance < ccd->Obstacle_Thres_Up &&
             ccd->Ec_Right_Mean < 0) //进障碍
    {

      Speed_Expect = Speed_info.Obstacle_Speed;

      state->pre = state->now;
      state->now = Into_Obstacle;
      state->direc_pre = state->direc_now;
      //方向判断
      state->direc_now = 1;
      print_road(state);
    }

    //情况2
    else if (ccd->Right_Variance < ccd->Little_Thres &&
             ccd->Left_Variance > ccd->Obstacle_Thres &&
             ccd->Left_Variance < ccd->Obstacle_Thres_Up &&
             ccd->Ec_Left_Mean > 0) //进障碍
    {

      Speed_Expect = Speed_info.Obstacle_Speed;

      state->pre = state->now;
      state->now = Into_Obstacle;
      state->direc_pre = state->direc_now;
      //方向判断
      state->direc_now = -1;
      print_road(state);
    }

  }//In_Straight

  /**************2.进弯中****************/
  else if (state ->now == Into_Curva)
  {
    reduce_spe_flag++;
    if (reduce_spe_flag == ccd->Into_Curva_Time)
    {

      Speed_Expect = Speed_info.Cur_Speed;

      reduce_spe_flag = 0;
      state->pre = state->now;
      state->now = In_Curva;
      state->direc_pre = state->direc_now;
      if (ccd->Ec_Left_Mean > 0)state->direc_now = 1;
      else state->direc_now = -1;
      print_road(state);
    }

  }
  /**************3.在弯道里****************/
  else if (state ->now == In_Curva)
  {
    if (ccd->Left_Variance < ccd->Little_Thres && ccd->Right_Variance < ccd->Little_Thres)  //进直道
    {

      Speed_Expect = Speed_info.Straight_Speed;

      state->pre = state->now;
      state->now = In_Straight;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }

  }

  /**************4.在十字中****************/
  else if (state ->now == In_Crossing)
  {
    if (!ccd->LossLine_Flag) //进直道
    {
      state->pre = state->now;
      state->now = In_Straight;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }
  }

  /**************5.前方障碍****************/
  else if (state ->now == Into_Obstacle)
  {
    if ((ccd->Left_Variance > ccd->Obstacle_Thres && ccd->Left_Variance < ccd->Obstacle_Thres_Up) ||
        (ccd->Right_Variance > ccd->Obstacle_Thres && ccd->Right_Variance < ccd->Obstacle_Thres_Up))
    {

      Speed_Expect = Speed_info.Straight_Speed;

      state->pre = state->now;
      state->now = Out_Obstacle;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }
  }
  /**************6.在十字中****************/
  else if (state ->now == Ramp_Down)
  {
    if (ccd->Left_Variance < ccd->Little_Thres && ccd->Right_Variance < ccd->Little_Thres)  //进直道
    {

      Speed_Expect = Speed_info.Straight_Speed;

      state->pre = state->now;
      state->now = In_Straight;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }
  }
  /**************7.出障碍****************/
  else
  {
    if (ccd->Left_Variance < ccd->Little_Thres && ccd->Right_Variance < ccd->Little_Thres)  //进直道
    {

      Speed_Expect = Speed_info.Straight_Speed;

      state->pre = state->now;
      state->now = In_Straight;
      state->direc_pre = state->direc_now;
      state->direc_now = 0;
      print_road(state);
    }
  }




}// Road_Judge(CCD_Info *ccd)



