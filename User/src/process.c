#include "include.h"


uint8 stop_flag = 1;  //目前的停车

int32 Calservo = 0;
int32 Calservo_Expect;
int32 Coderval;

int32 Speed_Expect_L;
int32 Speed_Expect_R;
int32 Speed_Average;

float Cal_Speed_L;
float Cal_Speed_R;

uint8 write_sd_flag = 0;

uint8 check_flag = 0;

uint8 reduce_spe_flag = 0;   //PID减速时间标志
float Into_Cur_Speed = 100;

uint8 send_data_cnt = 0;                   //发送数据的计数器

float K_Speed_Diff = 0; //差速   差速的比例
float Angle_Servo = 0; //差速  舵机输出与角度的关系


void Car_stop()      //停车函数      (注意要更换新的停车函数，stop_flag的更换需特别注意)
{
	if (stop_flag)
	{
		ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM, 0);
		ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM, 0); //L    给占空比正转
		ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM, 0); //R    给占空比正转
		ftm_pwm_duty(MOTOR_FTM, MOTOR4_PWM, 0);
#if TESTSD
		if (write_sd_flag)
		{
			write_sd_flag = 0;
			mySDWrite_Para_End();
		}
#endif
	}
}

/*************************舵机处理函数*************************/
void   Steer_Process()
{
	CCD1_ImageCapture(&CCD1_info);       //采集CCD1 AD值函数
	CCD2_ImageCapture(&CCD2_info);       //采集CCD2 AD值函数
	myCCD_DataHandle(&CCD1_info, &CCD2_info, &Speed_info);
	//Center_Board_Value = CCD1_info.CentralLine[0];
	if (CCD1_info.LossLine_Flag != 1)
	{
		Center_Board_Value = CCD1_info.CentralLine[0];
		Bell_Off;
	}
	else if (CCD1_info.AddLine_Flag == 1)
	{
		Center_Board_Value = (CCD1_info.LeftLine[0] + CCD1_info.RightLine[0]) / 2;
	}
	else if ( CCD1_info.Cross_Flag == 1 )
	{
		//Center_Board_Value = 64;
		Car_state.pre = Car_state.now;      //下坡
		Car_state.now = In_Crossing;
		if (CCD2_info.Cross_Flag != 1)
		{
			Center_Board_Value = (CCD2_info.LeftLine[0] + CCD2_info.RightLine[0]) / 2;
			Bell_On;
		}
		else
		{
			Center_Board_Value = (CCD1_info.LeftLine[0] + CCD1_info.RightLine[0]) / 2;
		}

	}
	if (Gyro_info.RampUpDown == 1)
	{
		Center_Board_Value = 64;
	}
	// Calservo = Calservo_Expect;
	Calservo_Expect =  (int32) (Pid_Calculate_Servo(&PidServo, Center_Board_Value, 64));
	Calservo = Calservo * 0.4 + Calservo_Expect * 0.6;

	// if (PidServo.error > 45)
	// {
	// 	Calservo = Calservo_Expect;
	// 	Calservo_Expect = SERVOCENTER - 90;
	// }
	// if (PidServo.error < - 45)
	// {

	// 	Calservo_Expect = SERVOCENTER + 90;
	// }
	if (!stop_flag)
	{
		ftm_pwm_duty(FTM3, SERVO, SERVOCENTER + Calservo);
		if (check_flag < 1300)
		{
			check_flag++;
			if (check_flag == 1300)
			{
				enable_irq(PORTC_IRQn);
				check_flag = 51;  //停止起跑线计数
			}
		}
#if TESTSD
		mySD_Write_CCD(&CCD1_info);
		mySD_Write_CCD(&CCD1_info);
		mySD_Write_Contr_Data(&PidServo, &ServoFuzzy);
#endif
	}

}

/*************************电机处理函数*************************/
void   Motor_Process()
{
	Speed_Read();
	Speed_Average = (int32)((Speed_Val2_R + Speed_Val1_L) / 2 );
	if (!stop_flag)
	{

		// Angle_Servo = PidSpeedLeft.temp * PidServo.out / 57.296; //转换为弧度制
		// if (Angle_Servo > 1.5)
		// 	Angle_Servo = 1.5;
		// if (Angle_Servo < -1.5)
		// 	Angle_Servo = -1.5;
		// K_Speed_Diff = 0.3209 * tan(Angle_Servo);//宽/2*长=0.3209

		K_Speed_Diff = -PidSpeedLeft.temp * PidServo.error;
		if ( K_Speed_Diff > 0.64 )   //转弯半径最大为50cm
			K_Speed_Diff = 0.64;     //50cm计算出来的差速比例为1.3256
		if ( K_Speed_Diff < -0.64 )
			K_Speed_Diff = -0.64;

		//if ( ( K_Speed_Diff < 0.01 ) && ( K_Speed_Diff > -0.01 ) ) //差速很小的时候就不差速了
		//	K_Speed_Diff = 0;
		Speed_Expect_L = ( Speed_Expect + (int32)(ServoFuzzy.outSpeed) ) * ( 1 - K_Speed_Diff );
		Speed_Expect_R = ( Speed_Expect + (int32)(ServoFuzzy.outSpeed) ) * ( 1 + K_Speed_Diff );

		Cal_Speed_L = Pid_Calculate_Speed(&PidSpeedLeft, Speed_Val1_L, Speed_Expect_L);
		Cal_Speed_R = Pid_Calculate_Speed(&PidSpeedRight, Speed_Val2_R, Speed_Expect_R);

		MotorSpeedOut(Cal_Speed_L, Cal_Speed_R);
		Send_Motor_Info();
#if TESTSD
		mySD_Write_Status();
#endif
	}
}

void Car_State_Judge()
{
	static int32 Stop_Counter = 0;
	if ((PidServo.temp < 4) && (PidServo.error < 10))
	{
		Stop_Counter++;
	}
	else
	{
		Stop_Counter = 0;
		Car_state.pre = Car_state.now;
		Car_state.now = In_Curva;
	}
	if (Stop_Counter >= 10)
	{
		Car_state.pre = Car_state.now;
		Car_state.now = In_Straight;
	}
}

void Send_CCD_Imag()      //发送到蓝宙CCD上位机
{
	if (stop_flag)
	{
		if (ccd_switch_flag) SendImageData(CCD1_info.PixelBinary);                                //CCD上传到蓝宙上位机函数
		else SendImageData(&CCD2_info.Pixel[0]);
	}
}

void Send_Steer_Info()    //发送给匿名上位机
{
	if (!stop_flag && Tune_Mode == 1)
	{
		push(0, (int16)Center_Board_Value);
		push(1, 64);
		push(2, (int16)(PidServo.kpi * 1000));
		push(3, (int16)(PidServo.kdi * 1000));
		push(4, (int16)(PidServo.error));
		push(5, (int16)(PidServo.temp));
		push(6, (int16)(ServoFuzzy.outP * 1000));
		push(7, (int16)(ServoFuzzy.outD * 1000));
		push(8, 1);
		Data_Send((uint8 *)SendBuf);
	}
	if (!stop_flag && Tune_Mode == 4)
	{
		// push(0, (int16)ccd1_info.LeftLine.variance); push(1, (int16)ccd1_info.LeftLine.mean); push(2, (int16)(ccd1_info.RightLine.variance)); push(3, (int16)(ccd1_info.RightLine.mean));
		// push(4, (int16)ccd1_info.Ec_Left.mean); push(5, (int16)ccd1_info.Ec_Right.mean); push(6, (int16)ccd1_info.Ec_Left.node[qhead]);
		// push(7, (int16)ccd1_info.Ec_Right.node[qhead]); push(8, 4);
		// Data_Send((uint8 *)SendBuf);
	}
}

void Send_Motor_Info()    //发送电机信息匿名上位机
{
	if (Tune_Mode == 2)  //Send Data to ANO Lab
	{
		push(0, (int16)( Speed_Expect + (int32)(ServoFuzzy.outSpeed) ) );
		push(1, (int16)Speed_Expect_L);
		push(2, (int16)(Speed_Expect_R));
		push(3, (int16)(Calservo));
		push(4, (int16)(Speed_Val1_L));
		push(5, (int16)Speed_Val2_R);
		push(6, (int16)(K_Speed_Diff * 1000));
		push(7, (int16)Speed_Expect);
		push(8, 2);
		Data_Send((uint8 *)SendBuf);
	}
	else if (Tune_Mode == 3)
	{
		push(0, (int16)Gyro_info.Gyro_Sum);
		push(1, (int16)Gyro_info.RampThresholdValue);
		push(2, (int16)(PidServo.out));
		push(3, (int16)(K_Speed_Diff * 100));
		push(4, (int16)(Angle_Servo * 5729.6));
		push(5, (int16)(PidServo.temp * 100));
		push(6, (int16)IIC_Count);
		push(7, (int16)(Gyro_info.RampUpDown * 1000 ));
		push(8, 3);
		Data_Send((uint8 *)SendBuf);
	}
}
