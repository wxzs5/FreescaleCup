#ifndef  __PROCESS_H
#define  __PROCESS_H



extern uint32 Calservo;
extern int32 Coderval;
extern float Calspeed;
extern float Caldiffer;
extern uint8 check_flag;

extern uint8 reduce_spe_flag;

/****************************************************************************
赛道信息变量
******************************************************************************/
extern uint8 Pixel_1[128];
extern uint8 binary_road_1[128];
extern uint8 differ_road_1[128];
extern uint8 Pixel_2[128];
extern uint8 binary_road_2[128];
extern uint8 differ_road_2[128];

extern uint8 send_data_cnt ;                   //发送数据的计数器

extern uint8 stop_flag ;
/****Remote Control*******/

void Car_stop();    //停车函数
void Steer_Process();   //舵机处理
void Motor_Process();   //电机处理
void Differ_Process();     //差速处理
void Send_CCD_Imag();   //发送CCD信息到蓝宙上位机
void Send_Steer_Info();   //发送舵机信息匿名上位机
void Send_Motor_Info();   //发送电机信息匿名上位机
#endif
