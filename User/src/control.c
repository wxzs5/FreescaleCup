#include"include.h"





void print_road(Car_State *state)
{
  if (Tune_Mode == 0)
  {
    if (state->now == In_Straight) printf("In_Straight->");
    else if (state->now == Into_Curva) printf("Into_Curva->");
    else if (state->now == In_Curva) printf("In_Curva->");
    else if (state->now == Into_Obstacle) printf("Into_Obstacle->");
    else printf("In_Crossing->");
  }
}




/*********************************************************************************
*                               我要过六级                                       *
*******************************赛道状态判断***************************************
* @file       control.c
* @brief      void Road_Judge(CCD_Info *CCD_info, 
                              Speed_Info *Speed_info, 
                              Car_State *state);
* @version    v5.3
* @date       2016-6-24
*********************************************************************************/
// void Road_Judge(CCD_Info *CCD_info, Speed_Info *Speed_info, Car_State *state)
// {
//   /**************1.在直道中****************/
//   if (state->now == In_Straight)
//   {

//     Speed_Temp = Speed_Expect;
//     Servo_Temp = Servo_Expect;
//     straight_count++;

//     if ((ccd->Left.variance >= CURVA_THRES || ccd->Right.variance >= CURVA_THRES ) &&
//         (ccd->Left.variance < CURVA_THRES_UP || ccd->Right.variance < CURVA_THRES_UP ) &&
//         ccd->Ec_Right.mean * ccd->Ec_Left.mean > 0)     //进弯
//     {
//       state->pre = state->now;
//       state->now = Into_Curva;
//       //方向判断
//       state->direc_pre = state->direc_now;
//       if (ccd->Right.variance > ccd->Left.variance) state->direc_now = 1;    //
//       else state->direc_now = -1;
//       print_road(state);
//     }


//     else if (ccd->Left.lost_line && ccd->Right.lost_line) //进十字
//     {
//       state->pre = state->now;
//       state->now = In_Crossing;
//       state->direc_pre = state->direc_now;
//       state->direc_now = 0;
//       print_road(state);
//     }


//     if (have_obstacle)
//     {
//       /*****************************单独讨论进障碍***************************/

// //情况1   障碍在右边
//       if (ccd->Left.variance < LITTLE_THRES &&
//           ccd->Right.variance > OBSTA_THRES &&
//           ccd->Right.variance < OBSTA_THRES_UP &&
//           ccd->Ec_Right.mean < 0) //进障碍
//       {
//         state->pre = state->now;
//         state->now = Into_Obstacle;
//         state->direc_pre = state->direc_now;
//         //方向判断
//         state->direc_now = 1;
//         print_road(state);
//       }

//       //情况2
//       else if (ccd->Right.variance < LITTLE_THRES &&
//                ccd->Left.variance > OBSTA_THRES &&
//                ccd->Left.variance < OBSTA_THRES_UP &&
//                ccd->Ec_Left.mean > 0) //进障碍
//       {

//         state->pre = state->now;
//         state->now = Into_Obstacle;
//         state->direc_pre = state->direc_now;
//         //方向判断
//         state->direc_now = -1;
//         print_road(state);
//       }
//     }
//   }//In_Straight


//   /**************2.进弯中****************/
//   else if (state ->now == Into_Curva)
//   {
//     if (Coderval > 450)Speed_Temp = Speed_Into_Curva;
//     else if (Coderval > 400)Speed_Temp = 260;
//     else if (Coderval > 350)Speed_Temp = 290;
//     else Speed_Temp = 340;
//     Servo_Temp = Servo_Expect;

//     if (reduce_spe_flag == REDUCE_COUNT)
//     {
//       reduce_spe_flag = 0;
//       state->pre = state->now;
//       state->now = In_Curva;
//       state->direc_pre = state->direc_now;
//       if (ccd->Ec_Left.mean > 0)state->direc_now = 1;
//       else state->direc_now = -1;
//       print_road(state);
//     }

//   }
//   /**************3.在弯道里****************/
//   else if (state ->now == In_Curva)
//   {
//     Speed_Temp = Speed_Curva;
//     Servo_Temp = Servo_Expect;

//     if (ccd->Left.variance < LITTLE_THRES && ccd->Right.variance < LITTLE_THRES)  //进直道
//     {
//       state->pre = state->now;
//       state->now = In_Straight;
//       state->direc_pre = state->direc_now;
//       state->direc_now = 0;
//       print_road(state);
//     }

//   }

//   /**************4.在十字中****************/
//   else if (state ->now == In_Crossing)
//   {
//     Speed_Temp = Speed_Expect;
//     Servo_Temp = Servo_Expect;

//     if (!ccd->Left.lost_line && !ccd->Right.lost_line) //进直道
//     {
//       state->pre = state->now;
//       state->now = In_Straight;
//       state->direc_pre = state->direc_now;
//       state->direc_now = 0;
//       print_road(state);
//     }
//   }

//   /**************5.前方障碍****************/
//   else if (state ->now == Into_Obstacle)
//   {
//     if (Coderval > 450)Speed_Temp = 350;
//     Speed_Temp = Speed_Expect;
//     if (state->direc_now == 1)Servo_Temp = Servo_Obs_Right;
//     else Servo_Temp = Servo_Obs_Left;


//     if ((ccd->Left.variance > OBSTA_THRES && ccd->Left.variance < OBSTA_THRES_UP) ||
//         (ccd->Right.variance > OBSTA_THRES && ccd->Right.variance < OBSTA_THRES_UP))
//     {
//       state->pre = state->now;
//       state->now = Out_Obstacle;
//       state->direc_pre = state->direc_now;
//       state->direc_now = 0;
//       print_road(state);
//     }
//   }

//   /**************6.出障碍****************/
//   else
//   {
//     Speed_Temp = Speed_Expect;
//     Servo_Temp = Servo_Expect;

//     if (ccd->Left.variance < LITTLE_THRES && ccd->Right.variance < LITTLE_THRES)  //进直道
//     {
//       state->pre = state->now;
//       state->now = In_Straight;
//       state->direc_pre = state->direc_now;
//       state->direc_now = 0;
//       print_road(state);
//     }
//   }


// }// Road_Judge(CCD_Info *ccd)
