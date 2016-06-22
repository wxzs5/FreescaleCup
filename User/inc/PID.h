

#ifndef __PID_H
#define __PID_H

#include "include.h"

#define Piddeadband 0     //1~2
#define SERVOCENTER 1000

extern float Speed_Expect;
extern float para_a;
extern float para_b;

typedef struct
{
  float ex_error;     //< 被调量期望值
  float error_pre;    //< 前一次偏差
  float error_pre_pre; //前前次偏差
  float temp;        //< 外环输出
  float ex_kp;           //< 外环比例系数
  float ex_ki;           //< 外环积分系数
  float ex_kd;           //< 外环比例系数
  float outP;         //< pid比例部分，调试用
  float outI;         //< pid积分部分，调试用
  float outD;         //< pid微分部分，调试用
  float out;
} Pidsuite;

extern Pidsuite PidServo;
extern Pidsuite PidSpeed;
extern Pidsuite PidDSpe;


void Pid_Init(void);
float Pid_Calculate_Speed(Pidsuite *Pid, float Measured, float Expect);
float Pid_Calculate_Servo(Pidsuite *Pid, int16 Measured, int16 Expect);
float Pid_Calculate_Differ(Pidsuite *Pid, int16 Measured, int16 Expect);
uint16 sqrt_16(uint32 M);


#endif
