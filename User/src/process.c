#include "include.h"

int8 qhead = 0;     //队列头


uint32 Calservo;
int32 Coderval;
float Calspeed;
float Caldiffer;
uint8 check_flag = 0;

uint8 reduce_spe_flag = 0;   //PID减速时间标志
float Into_Cur_Speed = 100;


/****************************************************************************
赛道信息变量
******************************************************************************/
uint8 Pixel_1[128];
uint8 binary_road_1[128];
uint8 differ_road_1[128];
uint8 Pixel_2[128];
uint8 binary_road_2[128];
uint8 differ_road_2[128];


uint8 send_data_cnt = 0;                   //发送数据的计数器
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

uint8 stop_flag = 0;

void Remote_stop()
{
	if (stop_flag)
	{
		ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM, 0);
		ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM, 0); //L    给占空比正转
		ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM, 0); //R    给占空比正转
		ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM, 0);
	}
}




/*************************舵机处理函数*************************/
void   Servo_Process()
{
	CCD1_ImageCapture(Pixel_1);       //采集CCD1 AD值函数
	CCD2_ImageCapture(Pixel_2);       //采集CCD2 AD值函数
	CCD_Get_Line_1(&Left_Board_Value1, &Right_Board_Value1, &Center_Board_Value1);
	CCD_Get_Line_2(&Left_Board_Value2, &Right_Board_Value2, &Center_Board_Value2);
	// if (Pixel_Get_Right_Flag1 && Pixel_Get_Left_Flag1 && (!CCD1_flag))
	Center_Board_Value = Center_Board_Value1;
	Calservo = SERVOCENTER + (int32) (Pid_Calculate_Servo(&PidServo, (int16)Center_Board_Value, 64));
	if (!stop_flag) ftm_pwm_duty(FTM3, SERVO, Calservo);

	Road_Data_Update(&ccd1_info, Right_Board_Value1, Left_Board_Value1);
	//Road_Data_Update(&ccd2_info, Right_Board_Value2,Left_Board_Value2);
	Road_Judge(&ccd1_info, &ccd1_state);
	//Road_Judge(&ccd2_info, &ccd2_state);

}


/*************************电机处理函数*************************/
void   Motor_Process()
{
	Speed_Read();
	Coderval = (int32) ((Speed_Val2_R + Speed_Val1_L) / 2);
	if (!stop_flag)
	{
		//Caldiffer = Pid_Calculate_Differ(&PidDSpe, Center_Board_Value, 64);
		//Calspeed = Pid_Calculate_Speed(&PidSpeed, Coderval, Speed_Expect);
		// MotorSpeedOut(Calspeed, Caldiffer);
		MotorSpeedOut(3000, 0);
		if (check_flag < 50) check_flag++;
		if (reduce_spe_flag < REDUCE_COUNT && ccd1_state.now == Into_Curva)reduce_spe_flag++;

		if (Tune_Mode == 2)  //Send Data to ANO Lab
		{
			push(0, (int16)Speed_Expect); push(1, (int16)Coderval); push(2, (int16)(PidSpeed.ex_ki * 1000)); push(3, (int16)(PidSpeed.ex_kp * 1000));
			push(4, (int16)(PidSpeed.outI)); push(5, (int16)PidSpeed.outP); push(6, (int16)PidSpeed.out); push(7, (int16)Calservo); push(8, 2);
			Data_Send((uint8 *)SendBuf);
		}
		else if (Tune_Mode == 3)
		{
			push(0, (int16)Speed_Val1_L); push(1, (int16)Speed_Val2_R); push(2, (int16)(PidDSpe.ex_kp * 1000)); push(3, (int16)(PidDSpe.ex_kd * 1000));
			push(4, (int16)(PidDSpe.outP)); push(5, (int16)PidDSpe.outI); push(6, (int16)PidDSpe.outD); push(7, (int16)PidDSpe.out); push(8, 3);
			Data_Send((uint8 *)SendBuf);
		}
	}
	Speed_Val1_L = Speed_Val2_R = 0;                                         //clear the quadruptrue coder's value
}





void Differ_Process()
{
	Caldiffer = Pid_Calculate_Differ(&PidDSpe, Center_Board_Value, 64);
	MotorSpeedOut(0, Caldiffer);
}




