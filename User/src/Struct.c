#include "include.h"
int8 qhead = 0;     //队列头

uint16 StopType = 0;   //停车类型

Parameter_Info  Parameter_info                 = {0};
Car_State  Car_state                                     = {In_Straight};
Car_State     Car_state_Pre                           = {In_Straight};
Car_Mode Car_mode                                   = {SelfDef};//初始化为安全速度
Road_Type 	 Road_type                                = {All};//默认赛道种类为全有(即：坡道,人字和路障)

menu Menu = {0};

Steer_Info Steer_info = {0};   //舵机初始化
Motor_Info Motor_info = {0};
Speed_Info Speed_info = {0};

Gyro_Info Gyro_info = {0};

// DMA_Required_Variable DMA_Variable_1= {0};
// Flash_Info Flash_info= {0};
RemSpeedUpDown_Info RemSpeedUpDown_info = {0};

CCD_Info CCD1_info = {0};
CCD_Info CCD2_info = {0};

/*************************************************************************
*					我要过六级
*
*  函数名称：mySteer_DataInit
*  功能说明：转向舵机参数初始化
*  参数说明：
*  函数返回：无
*  修改时间：2016-07-1
*  备    注：
*************************************************************************/
void mySteer_DataInit(Steer_Info *Steer_info)
{
	uint8_t ii = 0;

	Steer_info->Pid.kp = 0;
	Steer_info->Pid.ki  = 0;
	Steer_info->Pid.kd = 0;
	Steer_info->Pid.kpi = 0;
	Steer_info->Pid.kii  = 0;
	Steer_info->Pid.kdi = 0;

	Steer_info->KP_Mult = 0;            //PID放大倍数
	Steer_info->KD_Mult = 0;
	Steer_info->KI_Mult = 0;


	Steer_info->Steer_Center = 1000;    //舵机中心为1000

	for (ii = 0; ii < 10; ii++)
	{
		Steer_info->SteerPWM_Error[ii] = 0;
	}

	Steer_info->RampUp_SteerBackToCenter_Flag = 0;

}



/*************************************************************************
*					我要过六级
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
	mySteer_DataInit(&Steer_info);
}
