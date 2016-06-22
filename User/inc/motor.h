#ifndef _MOTOR_H
#define _MOTOR_H

//【山外电机驱动】打破权威的限制，还原电路的本色。
//注意：山外电机驱动 是 加入 MOS 管 隔离反相的，IO 输出 低电平，经过 MOS 管后会反相，变成 高电平，反正既然。


//常规模式: PWM 接入 IN 管脚 ,IO控制 INH 来使能 。
// INH 输入为 高电平 ，使能 BTN7971
// IN  输入为 高电平 , 加速 ； IN 输入为 低电平，刹车（注意，是刹车，不是降速那么简单）
//常规模式 是 不停加速（IN为高），然后减速（IN为低），是飞思卡尔智能车比赛最常用的方案
//效果如何？ 一边踩 油门 ，一边踩 刹车  ，你觉得呢？

//自由滚动模式: PWM 接入 INH 管脚 控制 是否使能 ，IO 控制 IN 管脚
// IN 输入为 高电平  ， 加速
// INH 输入为 高电平 , 使能芯片，进入全速状态 ； INH 输入为 低电平 ，禁用芯片，进入 无驱动状态
//自由滚动模式 是 一时加油，一时松开油门依靠重力加速度往前滚动。
//效果如何？ 经过 BTN7971 ，实际上 表现为 改变 电压值 ，从而 达到 控制 油门量 的目的 ，芯片发热量大大减少，滑动流畅


//点杀模式：PWM 接入 INH 管脚 控制 是否使能 ，IO 控制 IN 管脚
// IN 输入为 低电平  ， 刹车
// INH 输入为 高电平 , 使能芯片，进入刹车状态 ； INH 输入为 低电平 ，禁用芯片，进入 无驱动状态
//如果一直进入 刹车状态，会抱死电机，从而使得 小车 打滑，尤其过弯容易 漂移。
//如果一直进入 无驱动状态 ，电机 依靠小车的惯性一直滚动，虽然车轮与地之间是静摩擦，但达不到最大静摩擦力的效果，因而需要PWM调整占空比来点杀


#define MOTOR1_IO   PTD15
#define MOTOR2_IO   PTA19
#define MOTOR3_IO   PTA5
#define MOTOR4_IO   PTA24

#define MOTOR_FTM   FTM0
#define MOTOR1_PWM  FTM_CH3
#define MOTOR2_PWM  FTM_CH4
#define MOTOR3_PWM  FTM_CH5
#define MOTOR4_PWM  FTM_CH6

#define MOTOR1_PWM_IO  FTM0_CH3
#define MOTOR2_PWM_IO  FTM0_CH4
#define MOTOR3_PWM_IO  FTM0_CH5
#define MOTOR4_PWM_IO  FTM0_CH6

#define MOTOR_DEAD_VAL_L  0    //  死区电压
#define MOTOR_DEAD_VAL_R  0    //15


#define SERVO FTM_CH5


extern volatile float Speed_Val1_L;
extern volatile float Speed_Val2_R;


void motor_test(uint32 du);
void Init_ftm_motor();
void MotorSpeedOut(float speedPWM , float turnPWM);
int16_t SpeedPWMOut(int16_t NewspeedPWM , int16_t LastspeedPWM, uint8_t PeriodCount);
int16_t TURNPWMOut(int16_t NewAangPWM , int16_t LastAangPWM, uint8_t PeriodCount);
int16_t AAangPWMOut(int16_t NewAangPWM , int16_t LastAangPWM, uint8_t PeriodCount);


void Init_quad();
void show_speed_read(int16 val1, int16 val2);
void speed_show_show();
void Speed_Read();
void SERVO_test();







#endif
