#include "include.h"

#define  UPDATE   0     //用于处理函数等函数更新

uint8 stop_flag = 1;   //目前的停车

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



void Car_stop()      //停车函数      (注意要更换新的停车函数，stop_flag的更换需特别注意)
{
	if (stop_flag)
	{
		ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM, 0);
		ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM, 0); //L    给占空比正转
		ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM, 0); //R    给占空比正转
		ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM, 0);
	}
}

#if  UPDATE

/*************************************************************************
*				我要过六级
*  函数名称:  新Steer_Process
*  功能说明:  舵机信息处理
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-23
*  备注:注意更新换代，此处只占位置，还未更新
*************************************************************************/
void   Steer_Process()
{
	CCD1_ImageCapture(Pixel_1);       //采集CCD1 AD值函数
	CCD2_ImageCapture(Pixel_2);       //采集CCD2 AD值函数
	CCD_Get_Line_1(&Left_Board_Value1, &Right_Board_Value1, &Center_Board_Value1);
	CCD_Get_Line_2(&Left_Board_Value2, &Right_Board_Value2, &Center_Board_Value2);

	Center_Board_Value = Center_Board_Value1;
	Calservo = SERVOCENTER + (int32) (Pid_Calculate_Servo(&PidServo, (int16)Center_Board_Value, 64));
	if (!stop_flag) ftm_pwm_duty(FTM3, SERVO, Calservo);

	Road_Data_Update(&ccd1_info, Right_Board_Value1, Left_Board_Value1);
	//Road_Data_Update(&ccd2_info, Right_Board_Value2,Left_Board_Value2);
	Road_Judge(&ccd1_info, &ccd1_state);
	//Road_Judge(&ccd2_info, &ccd2_state);
}

/*************************************************************************
*				我要过六级
*  函数名称:  新Motor_Process
*  功能说明:  电机信息处理
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-23
*  备注:注意更新换代，此处只占位置，还未更新
*************************************************************************/
void   Motor_Process()
{
	Speed_Read();
	Coderval = (int32) ((Speed_Val2_R + Speed_Val1_L) / 2);
	if (!stop_flag)
	{
		Caldiffer = Pid_Calculate_Differ(&PidDSpe, Center_Board_Value, 64);
		Calspeed = Pid_Calculate_Speed(&PidSpeed, Coderval, Speed_Expect);
		MotorSpeedOut(Calspeed, Caldiffer);
		MotorSpeedOut(3000, 0);
		if (check_flag < 50) check_flag++;     //用于开始一段不检测起跑线，此处为50，即500ms内不检测起跑线
		if (reduce_spe_flag < REDUCE_COUNT && ccd1_state.now == Into_Curva)reduce_spe_flag++;

		Send_Motor_Info();
	}
	Speed_Val1_L = Speed_Val2_R = 0;                                         //clear the quadruptrue coder's value
}




#else
/*************************舵机处理函数*************************/
void   Steer_Process()
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
		// Caldiffer = Pid_Calculate_Differ(&PidDSpe, Center_Board_Value, 64);
		// Calspeed = Pid_Calculate_Speed(&PidSpeed, Coderval, Speed_Expect);
		// MotorSpeedOut(Calspeed, 0);
		MotorSpeedOut(3000, 0);
		if (check_flag < 50) check_flag++;
		if (reduce_spe_flag < REDUCE_COUNT && ccd1_state.now == Into_Curva)reduce_spe_flag++;

		Send_Motor_Info();
	}
	Speed_Val1_L = Speed_Val2_R = 0;                                         //clear the quadruptrue coder's value
}


/*************************后轮处理函数*************************/
void Differ_Process()
{
	Caldiffer = Pid_Calculate_Differ(&PidDSpe, Center_Board_Value, 64);
	MotorSpeedOut(0, Caldiffer);
}


#endif


void Send_CCD_Imag()      //发送到蓝宙CCD上位机
{
	if (stop_flag)
	{
		if (ccd_switch_flag) SendImageData(Pixel_1);                                //CCD上传到蓝宙上位机函数
		else SendImageData(Pixel_2);
	}
	else
	{
		if (check_flag == 50)    //此处用于起跑线检测，即500ms后再检测起跑线
		{
			enable_irq(PORTC_IRQn);
			check_flag = 51;
		}
	}
}

void Send_Steer_Info()    //发送给匿名上位机
{
	if (!stop_flag && Tune_Mode == 1)
	{
		push(0, (int16)Center_Board_Value); push(1, 64); push(2, (int16)(PidServo.kp * 1000)); push(3, (int16)(PidServo.kd * 1000));
		push(4, (int16)(PidServo.outP * 1000)); push(5, (int16)PidServo.outD * 1000); push(6, (int16)PidServo.out * 1000); push(7, (int16)Calservo); push(8, 1);
		Data_Send((uint8 *)SendBuf);
	}
	if (!stop_flag && Tune_Mode == 4)
	{
		push(0, (int16)ccd1_info.LeftLine.variance); push(1, (int16)ccd1_info.LeftLine.mean); push(2, (int16)(ccd1_info.RightLine.variance)); push(3, (int16)(ccd1_info.RightLine.mean));
		push(4, (int16)ccd1_info.Ec_Left.mean); push(5, (int16)ccd1_info.Ec_Right.mean); push(6, (int16)ccd1_info.Ec_Left.node[qhead]);
		push(7, (int16)ccd1_info.Ec_Right.node[qhead]); push(8, 4);
		Data_Send((uint8 *)SendBuf);
	}
}

void Send_Motor_Info()    //发送电机信息匿名上位机
{
	if (Tune_Mode == 2)  //Send Data to ANO Lab
	{
		push(0, (int16)Speed_Expect); push(1, (int16)Coderval); push(2, (int16)(PidSpeed.ki * 1000)); push(3, (int16)(PidSpeed.kp * 1000));
		push(4, (int16)(PidSpeed.outI)); push(5, (int16)PidSpeed.outP); push(6, (int16)PidSpeed.out); push(7, (int16)Calservo); push(8, 2);
		Data_Send((uint8 *)SendBuf);
	}
	else if (Tune_Mode == 3)
	{
		push(0, (int16)Speed_Val1_L); push(1, (int16)Speed_Val2_R); push(2, (int16)(PidDSpe.kp * 1000)); push(3, (int16)(PidDSpe.kd * 1000));
		push(4, (int16)(PidDSpe.outP)); push(5, (int16)PidDSpe.outI); push(6, (int16)PidDSpe.outD); push(7, (int16)PidDSpe.out); push(8, 3);
		Data_Send((uint8 *)SendBuf);
	}
}
