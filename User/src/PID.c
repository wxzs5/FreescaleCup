#include "include.h"


float para_a = 0.02;
float para_b = 3.0;

Pidsuite PidServo;
Pidsuite PidSpeed;
Pidsuite PidDSpe;

float Speed_Expect = 320;


/*************************************************************************
*       我要过六级
*  函数名称:  PID_Init
*  功能说明:  Pid参数初始化
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-23
*  备注:
*************************************************************************/
void PID_Init(Pidsuite *Pid)
{
  Pid->kp                     = 0;
  Pid->ki                      = 0;
  Pid->kd                     = 0;
  Pid->error                 = 0;
  Pid->error_pre               = 0;
  Pid->error_pre_pre        = 0;
  Pid->out                        = 0;
  Pid->outD                     = 0;
  Pid->outI                       = 0;
  Pid->outP                      = 0;
  Pid->temp                     = 0;
}

void Pid_Init(void)
{
  PidSpeed.kp                     = 12;
  PidSpeed.ki                      = 15;
  PidSpeed.kd                     = 0;
  PidSpeed.error                 = 0;
  PidSpeed.error_pre               = 0;
  PidSpeed.error_pre_pre        = 0;
  PidSpeed.out                        = 0;
  PidSpeed.outD                     = 0;
  PidSpeed.outI                       = 0;
  PidSpeed.outP                      = 0;
  PidSpeed.temp                     = 0;

  PidDSpe.kp                      = 0;
  PidDSpe.ki                       = 6;
  PidDSpe.kd                      = 0;
  PidDSpe.error                  = 0;
  PidDSpe.error_pre                = 0;
  PidDSpe.error_pre_pre         = 0;
  PidDSpe.out                         = 0;
  PidDSpe.outD                       = 0;
  PidDSpe.outI                        = 0;
  PidDSpe.outP                       = 0;
  PidSpeed.temp                     = 0;

  PidServo.kp                     = 4.6;
  PidServo.ki                      = 0;
  PidServo.kd                     = -1.5;
  PidServo.error                 = 0;
  PidServo.error_pre               = 0;
  PidServo.error_pre_pre        = 0;
  PidServo.out                        = 0;
  PidServo.outD                      = 0;
  PidServo.outI                       = 0;
  PidServo.outP                      = 0;
  PidSpeed.temp                     = 0;
}
#if PIDUPDATE


/*************************************************************************
*       我要过六级
*  函数名称:  PidPosi_Calculate
*  功能说明:  位置式PID计算
*  参数说明:  other   是外部微分项,如果使用默认位置式计算则把other置0
*
*  函数返回:
*  修改时间:2016-06-23
*  备注:
*************************************************************************/
float PidPosi_Calculate(Pidsuite *Pid, float Measured, float Expect, float other)
{

  Pid->error = Expect - Measured;

  Pid->outP   = Pid->kp * Pid->error;

  Pid->outI += Pid->ki * Pid->error;
  //MYRANGE(Pid->outI, 40, -40);       //积分限幅

  Pid->outD = Pid->kd * (Pid->error - Pid->error_pre);
  Pid->temp = Pid->kd * other;                         //为变微分项算法保留

  Pid->error_pre = Pid->error;

  if (ohter)
  {
    Pid->out   = Pid->outP
                 + Pid->outI
                 + Pid->temp;
  }
  else
  {
    Pid->out   = Pid->outP
                 + Pid->outI
                 + Pid->outD;
  }

  Pid->out = -Pid->out;

  return   MYRANGE(Pid->out, 95, -95);
}

/*************************************************************************
*       我要过六级
*  函数名称:  PidDelta_Calculate
*  功能说明:  增量式PID计算
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-23
*  备注:
*************************************************************************/
float PidDelta_Calculate(Pidsuite *Pid, float Measured, float Expect)
{
  Pid->error = Expect - Measured;

  Pid->outP   = Pid->kp * (Pid->error - Pid->error_pre);


  Pid->outI   = Pid->ki * Pid->error;
  //MYRANGE(Pid->outI, 5000, -5000);

  Pid->outD   = Pid->kd * (Pid->error + Pid->error_pre_pre - 2 * Pid->error_pre);

  Pid->out   += Pid->outP
                + Pid->outI
                + Pid->outD;

  Pid->error_pre_pre = Pid->error_pre;
  Pid->error_pre = Pid->error;

  return MYRANGE(Pid->out, 10000, -10000);
}


#else
float Pid_Calculate_Servo(Pidsuite *Pid, int16 Measured, int16 Expect)
{
  static int16 Measured_Pre = 0;
  float kp , kd;
  kp = Pid->kp + ServoFuzzy.outP;
  kd = Pid->kd + ServoFuzzy.outD;

  Pid->error = Expect - Measured;
  // Pid->temp = Expect - Center_Board_Value2;
  // if ((Pid->temp > 15 || Pid->temp < -15) && (Pixel_Get_Right_Flag2 || Pixel_Get_Left_Flag2))Pid->error = 0.5 * Pid->error + 0.5 * Pid->temp;
  Pid->error_pre = Measured - Measured_Pre;

  //Fuzzy_Cal(&ServoFuzzy, Pid->error, Pid->error_pre);
  kp = para_a * Pid->error * Pid->error + para_b;
  Pid->outP   = kp * Pid->error;

  Pid->outD = kd * Pid->error_pre;
  // if (Pid->error > 15) Pid->outD =  0;
  // if (Pid->error < -15) Pid->outD = 0;

  Measured_Pre  = Measured;

  Pid->out   = Pid->outP
               + Pid->outI
               + Pid->outD;

  Pid->out = -Pid->out;
  return   MYRANGE(Pid->out, 95, -95);
}




float Pid_Calculate_Speed(Pidsuite *Pid, float Measured, float Expect)
{
  Pid->error = Expect - Measured;

  //Pid->outP   = Pid->temp * Pid->kp * (Pid->error - Pid->error_pre);
  Pid->outP   = Pid->kp * (Pid->error - Pid->error_pre);


  Pid->outI   = Pid->ki * Pid->error;

  //MYRANGE(Pid->outI, 5000, -5000);

  //Pid->outD   = Pid->kd * (Pid->error + Pid->error_pre_pre - 2 * Pid->error_pre);

  Pid->out   += Pid->outP
                + Pid->outI
                + Pid->outD;

  Pid->error_pre_pre = Pid->error_pre;
  Pid->error_pre = Pid->error;

  return MYRANGE(Pid->out, 10000, -10000);

}

float Pid_Calculate_Differ(Pidsuite *Pid, int16 Measured, int16 Expect)
{
  // Pid->error = Expect - Measured;

  // Pid->outP   = Pid->kp * Pid->error ;

  // Pid->outI   += Pid->ki * Pid->error;

  // if (Pid->outI > 200) Pid->outI =  200;
  // if (Pid->outI < -200) Pid->outI = -200;

  // Pid->outD   = Pid->kd * (Pid->error - Pid->error_pre);

  // Pid->error_pre = Pid->error;

  // Pid->out   = Pid->outP
  //              + Pid->outI
  //              + Pid->outD;
  Pid->out = Pid->kd * PidServo.out;

  return    MYRANGE(Pid->out, 500, -500);
}


#endif

