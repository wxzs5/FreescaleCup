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

// extern uint8 Left_Board_Value;
// extern uint8 Right_Board_Value;
// extern int8 Left_Board_Value_Last;
// extern int8 Right_Board_Value_Last;
// extern int8 Center_Board_Value;
// extern int8 Centre_BlackOld;
// extern int8  Centre_Black;
extern uint8 send_data_cnt ;                   //发送数据的计数器
/*uint8  Atem8B0;                            //临时变量
uint8  ALeftLineAryy[50];                  //左边黑线位置
uint8  ARightLineAryy[50] ;                //右边黑线位置
uint8  ALastLeftLinAryy[50]  ;             //上场左边黑线位置
uint8  ALastRightLinAryy[50]  ;            //上场右边黑线位置
uint8 Pixel[138];                          //CCD采集原始点

uint8 *pixel_pt;                           //CCD采样指针
int8 CCDStation ;                         //CCD的黑线位置
uint8 CCDMIDSTATION = 63 ;                 //CCD传感器表示的黑线的中间位置
uint16 CCDTurnPWM ;                        //转向的PWM值
uint16 count = 0 ;                              //脉冲计数器
uint8 Rightblackedge;
uint8 Leftblackedge;
*/

extern uint8 stop_flag ;
/****Remote Control*******/

void Remote_stop();
void Servo_Process();
void Motor_Process();
void Differ_Process();


#endif
