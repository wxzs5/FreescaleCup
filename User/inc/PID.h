#ifndef __PID_H
#define __PID_H


#define Piddeadband 0     //1~2
#define SERVOCENTER 945

extern float Speed_Expect;
extern float Ramp_Kp;


void Pid_Init(void);
float Pid_Calculate_Speed(Pidsuite *Pid, float Measured, float Expect);
float Pid_Calculate_Servo(Pidsuite *Pid, int16 Measured, int16 Expect);
float Pid_Calculate_Differ(Pidsuite *Pid, int16 Measured, int16 Expect);



#endif
