#ifndef __PID_H
#define __PID_H


#define PIDUPDATE 0  //用于PID函数计算的更新换代


#define Piddeadband 0     //1~2
#define SERVOCENTER 980

extern float Speed_Expect;



void Pid_Init(void);
float Pid_Calculate_Speed(Pidsuite *Pid, float Measured, float Expect);
float Pid_Calculate_Servo(Pidsuite *Pid, int16 Measured, int16 Expect);
float Pid_Calculate_Differ(Pidsuite *Pid, int16 Measured, int16 Expect);
#if PIDUPDATE
float PidPosi_Calculate(Pidsuite *Pid, float Measured, float Expect, float other);
float PidDelta_Calculate(Pidsuite *Pid, float Measured, float Expect);

#endif


#endif
