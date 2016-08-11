#ifndef  __PROCESS_H
#define  __PROCESS_H



extern int32 Calservo;

extern int32 Speed_Expect_L;
extern int32 Speed_Expect_R;
extern int32 Speed_Average;

extern float Cal_Speed_L;
extern float Cal_Speed_R;

extern uint32 check_flag;
extern uint16 Time_Counter;

extern uint8 reduce_spe_flag;


extern uint8 send_data_cnt ;                   //发送数据的计数器

extern uint8 stop_flag ;

/****Remote Control*******/

void Car_stop();    //停车函数
void Steer_Process();   //舵机处理
void Motor_Process();   //电机处理
// void Car_State_Judge();
void Send_CCD_Imag();   //发送CCD信息到蓝宙上位机
void Send_Steer_Info();   //发送舵机信息匿名上位机
void Send_Motor_Info();   //发送电机信息匿名上位机
#endif
