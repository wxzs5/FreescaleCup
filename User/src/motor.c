/********************************************************************************
*     COPYRIGHT NOTICE
*     Copyright (c) 2015,Ibrahim
*     All rights reserved.
*
*     本程序没有版权欢迎借阅，或给我提出问题及改进意见
*     联系人Ibrahim 联系方式：1711125768@qq.com
*********************************************************************************
* @file       motor.c
* @brief      野火K60 平台主程序
* @author     Ibrahim
* @version    v5.0
* @date       2015-10-18
*********************************************************************************/
#include "include.h"


/************************************************定义全局变量*******************************************************/

volatile float  Speed_L, Speed_R, Speed_L_Last, Speed_R_Last; //左右轮速度 ，最终速度

//编码器测速值
volatile float Speed_Val1_L = 0;
volatile float Speed_Val2_R = 0;

/*******************************************************************************
* Function Name  : Init_ftm_motor()
* Description    : 初始化电机驱动
* Input          : None
* Output         : None
* Return         : None
* Editor         ：Ibrahim
***************************************************************************/
void Init_ftm_motor()
{
  //初始化 PWM 输出
  //FTM 的管脚 可在  fire_port_cfg.h
  //宏定义FTM0_PRECISON   改为  1000u
  //PWM数值反转。
  ftm_pwm_init(FTM0, MOTOR1_PWM, 20000, 0);              //初始化 电机 PWM
  ftm_pwm_init(FTM0, MOTOR2_PWM, 20000, 0);              //初始化 电机 PWM
  ftm_pwm_init(FTM0, MOTOR3_PWM, 20000, 0);              //初始化 电机 PWM
  ftm_pwm_init(FTM0, MOTOR4_PWM, 20000, 0);              //初始化 电机 PWM

  ftm_pwm_init(FTM3, SERVO, 50, SERVOCENTER);                //初始化 电机 PWM

  //IO管脚配置
  //gpio_init(MOTOR1_IO,GPO,LOW);
  //gpio_init(MOTOR2_IO,GPO,LOW);
  //gpio_init(MOTOR3_IO,GPO,LOW);
  //gpio_init(MOTOR4_IO,GPO,LOW);
  /*gpio_init(MOTOR1_IO,GPO,HIGH);
  gpio_init(MOTOR2_IO,GPO,HIGH);
  gpio_init(MOTOR3_IO,GPO,HIGH);
  gpio_init(MOTOR4_IO,GPO,HIGH);*/

}
/*******************************************************************************
* Function Name  : motor_test()
* Description    : 电机驱动测试
* Input          : None
* Output         : None
* Return         : None
* Editor         ：lyf
***************************************************************************/
void SERVO_test()
{

  ftm_pwm_duty(FTM3, SERVO, 1100);  //R
  DELAY_MS(1000);


  ftm_pwm_duty(FTM3, SERVO, 900);
  DELAY_MS(1000);

}
/*******************************************************************************
* Function Name  : motor_test()
* Description    : 电机驱动测试
* Input          : None
* Output         : None
* Return         : None
* Editor         ：lyf
***************************************************************************/
void motor_test(uint32 du)
{

  ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM, 0);
  ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM, du); //L    给占空比正转
  ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM, du); //R    给占空比正转
  ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM, 0);
//      DELAY_MS(1000);


  //ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,0);
  //ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,2000);
  //ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,0);
  //ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM,2000);
  //DELAY_MS(1000);


}
/*******************************************************************************
* Function Name  : Init_quad()
* Description    : 初始化正交解码模块
* Input          : None
* Output         : None
* Return         : None
* Editor         ：Ibrahim
***************************************************************************/
void Init_quad()
{
  //初始化FTM1
  ftm_quad_init(FTM1);
  //初始化FTM2
  ftm_quad_init(FTM2);

}
/*******************************************************************************
* Function Name  : show_speed()
* Description    : 显示所测速度（只是判断正反时使用，其余时刻并没有什么用）
* Input          : None
* Output         : None
* Return         : None
* Editor         ：Ibrahim
********************************************************************************/
void show_speed_read(int16 val1, int16 val2)
{
  if (val1 >= 0)
  {
    printf("\n1正转：%d", val1);
  }
  else
  {
    printf("\n1反转：%d", -val1);
  }
  if (val2 >= 0) //
  {
    printf("\n2正转：%d", val2);
  }
  else
  {
    printf("\n2反转：%d", -val2);
  }
}
/*******************************************************************************
* Function Name  : speed_show_show()
* Description    : 显示所测速度（只是判断正反时使用，其余时刻并没有什么用）
* Input          : None
* Output         : None
* Return         : None
* Editor         ：Ibrahim
********************************************************************************/
void speed_show_show()
{
  int16 val1_show, val2_show;//
  val1_show = ftm_quad_get(FTM1);          //获取FTM1 正交解码 的脉冲数(负数表示反方向)
  ftm_quad_clean(FTM1);
  val2_show = ftm_quad_get(FTM2);          //获取FTM 2正交解码 的脉冲数(负数表示反方向)
  ftm_quad_clean(FTM2);

  if (val1_show >= 0)
  {
    printf("L:%d\n", val1_show);
  }
  else
  {
    printf("L:%d\n", -val1_show);
  }
  if (val2_show >= 0) //
  {
    printf("R:%d\n", val2_show);
  }
  else
  {
    printf("R:%d\n", -val2_show);
  }
}
/*******************************************************************************
* Function Name  : Speed_Read()
* Description    : 读取速度
* Input          : None
* Output         : None
* Return         : None
* Editor         ：Ibrahim
********************************************************************************/
void Speed_Read()
{
  Speed_Val1_L = (float)ftm_quad_get(FTM1);          //获取FTM1 正交解码 的脉冲数(负数表示反方向)
  ftm_quad_clean(FTM1);
  Speed_Val2_R = -(float)ftm_quad_get(FTM2);          //获取FTM 2正交解码 的脉冲数(负数表示反方向)     Warning:The direction is inverse
  ftm_quad_clean(FTM2);
}



/*******************************************************************************
* Function Name  : MotorSpeedOut(float standPWM ,float speedPWM ,float turnPWM)
* Description    : 电机驱动
* Input          : None
* Output         : None
* Return         : None
* Editor         ：yzy
***************************************************************************/
void MotorSpeedOut(float Speed_L, float Speed_R)
{

  /***********************将最大速度限制在985个PWM内******************************/
  if (Speed_L > 10000)  Speed_L = 10000;
  if (Speed_L < -10000) Speed_L = -10000;
  if (Speed_R > 10000)  Speed_R = 10000;
  if (Speed_R < -10000) Speed_R = -10000;

  /*************用所得到的对应角度的速度进行PWM控制********************/
  if (Speed_L >= 0)   //angle大于0，向前，小于0，向后
  {
    ftm_pwm_duty(FTM0, MOTOR1_PWM, 0);
    ftm_pwm_duty(FTM0, MOTOR2_PWM, (uint32)(Speed_L - MOTOR_DEAD_VAL_L));  //加入死区电压
  }
  else
  {
    ftm_pwm_duty(FTM0, MOTOR2_PWM, 0);
    ftm_pwm_duty(FTM0, MOTOR1_PWM, (uint32)(-Speed_L - MOTOR_DEAD_VAL_L));  //加入死区电压
  }

  if (Speed_R >= 0)   //angle大于0，向前，小于0，向后
  {
    ftm_pwm_duty(FTM0, MOTOR4_PWM, 0);
    ftm_pwm_duty(FTM0, MOTOR3_PWM, (uint32)(Speed_R - MOTOR_DEAD_VAL_R));  //加入死区电压
  }
  else
  {
    ftm_pwm_duty(FTM0, MOTOR3_PWM, 0);
    ftm_pwm_duty(FTM0, MOTOR4_PWM, (uint32)(-Speed_R - MOTOR_DEAD_VAL_R)); //加入死区电压
  }
}
