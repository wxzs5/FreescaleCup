#include "include.h"
int8 qhead = 0;     //队列头

uint16 StopType = 0;   //停车类型

Parameter_Info  Parameter_info                 = {0};
Car_State  Car_state                                     = {In_Straight};
Car_State     Car_state_Pre                           = {In_Straight};
Car_Mode Car_mode                                   = {SelfDef};//初始化为安全速度
Road_Type    Road_type                                = {All};//默认赛道种类为全有(即：坡道,人字和路障)

menu Menu = {0};

Speed_Info Speed_info = {0};

Gyro_Info Gyro_info = {0};

// DMA_Required_Variable DMA_Variable_1= {0};
// Flash_Info Flash_info= {0};
#ifdef  RemRoad_Control_Enable
RemSpeedUpDown_Info RemSpeedUpDown_info = {0};
#endif

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

}
