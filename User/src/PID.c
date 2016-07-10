#include "include.h"


Pidsuite PidServo = {0};
Pidsuite PidSpeedLeft = {0};
Pidsuite PidSpeedRight = {0};

float Speed_Expect = 295;


void Pid_Init(void)
{
  PidSpeedLeft.kp                  = 21;
  PidSpeedLeft.ki                  = 12;
  PidSpeedLeft.kd                  = 0;
  PidSpeedLeft.error               = 0;
  PidSpeedLeft.error_pre           = 0;
  PidSpeedLeft.error_pre_pre       = 0;
  PidSpeedLeft.out                 = 0;
  PidSpeedLeft.outD                = 0;
  PidSpeedLeft.outI                = 0;
  PidSpeedLeft.outP                = 0;
  PidSpeedLeft.temp                = 0.01; //差速的参数

  PidSpeedRight.kp                 = 21;
  PidSpeedRight.ki                 = 12;
  PidSpeedRight.kd                 = 0;
  PidSpeedRight.error              = 0;
  PidSpeedRight.error_pre          = 0;
  PidSpeedRight.error_pre_pre      = 0;
  PidSpeedRight.out                = 0;
  PidSpeedRight.outD               = 0;
  PidSpeedRight.outI               = 0;
  PidSpeedRight.outP               = 0;
  PidSpeedRight.temp               = 0.01;//差速的参数

  PidServo.kp                      = 3.75;
  PidServo.ki                      = 0;
  PidServo.kd                      = 6.5;
  PidServo.error                   = 0;
  PidServo.error_pre               = 0;
  PidServo.error_pre_pre           = 0;
  PidServo.out                     = 0;
  PidServo.outD                    = 0;
  PidServo.outI                    = 0;
  PidServo.outP                    = 0;
  PidServo.temp                    = 0;
}


float Pid_Calculate_Servo(Pidsuite *Pid, int16 Measured, int16 Expect)
{
  Pid->error_pre_pre = Pid->error_pre;
  Pid->error_pre = Pid->error;
  Pid->error = Expect - Measured;

  Pid->temp = Pid->error - Pid->error_pre_pre;
  MYRANGE(Pid->temp, 12, -12);
  if (Car_state.now != Ramp_Up && Car_state.now != Ramp_Down) Fuzzy_Cal(&ServoFuzzy, Pid->error, Pid->temp);
  Pid->kpi = Pid->kp + ServoFuzzy.outP;
  Pid->kdi = Pid->kd + ServoFuzzy.outD;

  Pid->outP   = Pid->kpi * Pid->error;

  //Pid->outD = Pid->kd * Gyro_data.z;
  Pid->outD = Pid->kdi * (Pid->error - Pid->error_pre);
  // if (Pid->error > 15) Pid->outD =  0;
  // if (Pid->error < -15) Pid->outD = 0;

  Pid->out   = Pid->outP
               + Pid->outI
               + Pid->outD;

  Pid->out = -Pid->out;
  return   MYRANGE(Pid->out, 100, -100);
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
  Pid->error = Expect - Measured;

  Pid->outP   = Pid->kp * Pid->error ;

  Pid->outI   += Pid->ki * Pid->error;

  if (Pid->outI > 200) Pid->outI =  200;
  if (Pid->outI < -200) Pid->outI = -200;

  Pid->outD   = Pid->kd * (Pid->error - Pid->error_pre);

  Pid->error_pre = Pid->error;

  Pid->out   = Pid->outP
               + Pid->outI
               + Pid->outD;
  Pid->out = -Pid->kd * PidServo.outP;

  return    MYRANGE(Pid->out, 3000, -3000);
}


