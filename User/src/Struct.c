#include "include.h"
int8 qhead = 0;     //队列头

uint16 StopType = 0;   //停车类型

Parameter_Info  Parameter_info                 = {0};
Car_State  Car_state                                     = {In_Straight};
Car_Mode Car_mode                                   = {SelfDef};//初始化为安全速度

menu Menu = {0};

Speed_Info Speed_info = {0};

Gyro_Info Gyro_info = {0};

// Flash_Info Flash_info= {0};


CCD_Info CCD1_info = {0};
CCD_Info CCD2_info = {0};



/*************************************************************************
*                   我要过六级
*
*  函数名称：myData_Init
*  功能说明：总参数初始化
*  参数说明：
*  函数返回：无
*  修改时间：2016-06-23
*  备    注：
*************************************************************************/
void myData_Init()
{
    Speed_info.Obstacle_Speed = 60;
    Speed_info.RampUp_Speed = 80;
    Speed_info.RampDown_Speed = 70;
    Speed_info.Straight_Speed = 108;
    Speed_info.Cur_Speed = 108;
    Speed_info.Snake_Speed = 112;
    Speed_info.Into_Cur_Speed = 90;

    Parameter_info.DebugTime = 1700;
    Parameter_info.Time = 1900;
    Parameter_info.Snake_dead = 0.05;

    CCD1_info.Little_Thres = 5;
    CCD1_info.Obstacle_Thres = 45;
    CCD1_info.Obstacle_Thres_Up = 100;
    CCD1_info.Curva_Thres = 10;
    CCD1_info.Curva_Thres_Up = 120;
    CCD1_info.Into_Curva_Time = 20;

    Car_state.now = In_Straight;
    Car_state.pre = In_Straight;

}
