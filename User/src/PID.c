#include "include.h"

#define MYRANGE(x,max,min)      ((x) =((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))

Pidsuite PidServo;
Pidsuite PidSpeed;
Pidsuite PidDSpe;
float para_a = 0.02;
float para_b = 3.0;


float Speed_Expect = 320;


// servo
//para_a 0.013
//para_b 0.8  可供参考
//差速0.4
void Pid_Init(void)
{
  PidSpeed.ex_kp                     = 12;
  PidSpeed.ex_ki                      = 15;
  PidSpeed.ex_kd                     = 0;
  PidSpeed.ex_error                 = 0;
  PidSpeed.error_pre               = 0;
  PidSpeed.error_pre_pre        = 0;
  PidSpeed.out                        = 0;
  PidSpeed.outD                     = 0;
  PidSpeed.outI                       = 0;
  PidSpeed.outP                      = 0;

  PidDSpe.ex_kp                      = 0;
  PidDSpe.ex_ki                       = 6;
  PidDSpe.ex_kd                      = 0;
  PidDSpe.ex_error                  = 0;
  PidDSpe.error_pre                = 0;
  PidDSpe.error_pre_pre         = 0;
  PidDSpe.out                         = 0;
  PidDSpe.outD                       = 0;
  PidDSpe.outI                        = 0;
  PidDSpe.outP                       = 0;

  PidServo.ex_kp                     = 4.6;
  PidServo.ex_ki                      = 0;
  PidServo.ex_kd                     = -1.5;
  PidServo.ex_error                 = 0;
  PidServo.error_pre               = 0;
  PidServo.error_pre_pre        = 0;
  PidServo.out                        = 0;
  PidServo.outD                      = 0;
  PidServo.outI                       = 0;
  PidServo.outP                      = 0;

}

uint16 sqrt_16(uint32 M)
{
  uint16 N, i;
  uint32 tmp, ttp;   // 结果、循环计数
  if (M == 0)               // 被开方数，开方结果也为0
    return 0;
  N = 0;
  tmp = (M >> 30);          // 获取最高位：B[m-1]
  M <<= 2;
  if (tmp > 1)              // 最高位为1
  {
    N ++;                 // 结果当前位为1，否则为默认的0
    tmp -= N;
  }
  for (i = 15; i > 0; i--)  // 求剩余的15位
  {
    N <<= 1;              // 左移一位
    tmp <<= 2;
    tmp += (M >> 30);     // 假设
    ttp = N;
    ttp = (ttp << 1) + 1;
    M <<= 2;
    if (tmp >= ttp)       // 假设成立
    {
      tmp -= ttp;
      N ++;
    }
  }
  return N;
}

float Pid_Calculate_Servo(Pidsuite *Pid, int16 Measured, int16 Expect)
{
  static int16 Measured_Pre = 0;
  float kp , kd;
  kp = Pid->ex_kp + ServoFuzzy.outP;
  kd = Pid->ex_kd + ServoFuzzy.outD;

  Pid->ex_error = Expect - Measured;
  // Pid->temp = Expect - Center_Board_Value2;
  // if ((Pid->temp > 15 || Pid->temp < -15) && (Pixel_Get_Right_Flag2 || Pixel_Get_Left_Flag2))Pid->ex_error = 0.5 * Pid->ex_error + 0.5 * Pid->temp;
  Pid->error_pre = Measured - Measured_Pre;

  //Fuzzy_Cal(&ServoFuzzy, Pid->ex_error, Pid->error_pre);
  kp = para_a * Pid->ex_error * Pid->ex_error + para_b;
  Pid->outP   = kp * Pid->ex_error;

  //Pid->outD = kd * Pid->error_pre;
  // if (Pid->ex_error > 15) Pid->outD =  0;
  // if (Pid->ex_error < -15) Pid->outD = 0;

  Measured_Pre  = Measured;

  Pid->out   = Pid->outP
               + Pid->outI
               + Pid->outD;

  Pid->out = -Pid->out;
  return   MYRANGE(Pid->out, 95, -95);
}




float Pid_Calculate_Speed(Pidsuite *Pid, float Measured, float Expect)
{
  Pid->ex_error = Expect - Measured;

  //Pid->outP   = Pid->temp * Pid->ex_kp * (Pid->ex_error - Pid->error_pre);
  Pid->outP   = Pid->ex_kp * (Pid->ex_error - Pid->error_pre);


  Pid->outI   = Pid->ex_ki * Pid->ex_error;

  //MYRANGE(Pid->outI, 5000, -5000);

  //Pid->outD   = Pid->ex_kd * (Pid->ex_error + Pid->error_pre_pre - 2 * Pid->error_pre);

  Pid->out   += Pid->outP
                + Pid->outI
                + Pid->outD;

  Pid->error_pre_pre = Pid->error_pre;
  Pid->error_pre = Pid->ex_error;

  return MYRANGE(Pid->out, 10000, -10000);

}

float Pid_Calculate_Differ(Pidsuite *Pid, int16 Measured, int16 Expect)
{
  // Pid->ex_error = Expect - Measured;

  // Pid->outP   = Pid->ex_kp * Pid->ex_error ;

  // Pid->outI   += Pid->ex_ki * Pid->ex_error;

  // if (Pid->outI > 200) Pid->outI =  200;
  // if (Pid->outI < -200) Pid->outI = -200;

  // Pid->outD   = Pid->ex_kd * (Pid->ex_error - Pid->error_pre);

  // Pid->error_pre = Pid->ex_error;

  // Pid->out   = Pid->outP
  //              + Pid->outI
  //              + Pid->outD;
  Pid->out = Pid->ex_kd * PidServo.out;

  return    MYRANGE(Pid->out, 500, -500);
}




