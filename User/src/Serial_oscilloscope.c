/******************** LQ_K60_函数库 v1.0 ********************
 * 文件名           ：UART.c
 * 功能             ：设置UART口工作模式
 * 备注             ：官方例程上修改
 * 日期             ：2015-10-16
 * 实验平台         ：龙丘 k60DN512Z核心板
 * 作者             ：龙丘技术 006
 * 淘宝店           ：https://longqiu.taobao.com
 * 龙丘智能车讨论群 ：202949437
*************************************************************/

#include "include.h"

uint8 Tune_Mode = 2;
uint8 data_to_send[50] = {0};       //发送缓存

uint8   SendBuf[UartDataNum ] = {0};



void push(uint8 chanel, uint16 data)
{
	SendBuf[chanel * 2] = data / 256;
	SendBuf[chanel * 2 + 1] = data % 256;
}


//unsigned char data_to_send[16];
void Data_Send(uint8 *pst)
{
	uint8 _cnt = 0;	uint8 sum = 0;
	data_to_send[_cnt++] = 0xAA;
	data_to_send[_cnt++] = 0xAA;
	data_to_send[_cnt++] = 0x02;
	data_to_send[_cnt++] = 0;
	data_to_send[_cnt++] = *pst++; //低8位
	data_to_send[_cnt++] = *pst++; //高8位
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;
	data_to_send[_cnt++] = *pst++;


	data_to_send[3] = _cnt - 4;

	sum = 0;

	for (uint8 i = 0; i < _cnt; i++)
		sum += data_to_send[i];

	data_to_send[_cnt++] = sum;
	ANO_Send_Data((uint8 *)data_to_send, _cnt);
}

void ANO_Send_Data(uint8 *Buff, uint8 len)
{
	for (uint8 i = 0; i < len; i++)
		uart_putchar(UART4, data_to_send[i]);
}


void ANO_DT_Data_Receive_Prepare(uint8 data)
{
	static uint8 RxBuffer[50];
	static uint8 _data_len = 0, _data_cnt = 0;
	static uint8 state = 0;

	if (state == 0 && data == 0xAA)
	{
		state = 1;
		RxBuffer[0] = data;
	}
	else if (state == 1 && data == 0xAF)
	{
		state = 2;
		RxBuffer[1] = data;
	}
	else if (state == 2 && data < 0XF1)
	{
		state = 3;
		RxBuffer[2] = data;
	}
	else if (state == 3 && data < 50)
	{
		state = 4;
		RxBuffer[3] = data;
		_data_len = data;
		_data_cnt = 0;
	}
	else if (state == 4 && _data_len > 0)
	{
		_data_len--;
		RxBuffer[4 + _data_cnt++] = data;
		if (_data_len == 0)
			state = 5;
	}
	else if (state == 5)
	{
		state = 0;
		RxBuffer[4 + _data_cnt] = data;
		ANO_DT_Data_Receive_Anl(RxBuffer, _data_cnt + 5);
	}
	else
		state = 0;
}


/////////////////////////////////////////////////////////////////////////////////////
//Data_Receive_Anl函数是协议数据解析函数，函数参数是符合协议格式的一个数据帧，该函数会首先对协议数据进行校验
//校验通过后对数据进行解析，实现相应功能
//此函数可以不用用户自行调用，由函数Data_Receive_Prepare自动调用
void ANO_DT_Data_Receive_Anl(uint8 *data_buf, uint8 num)
{
	uint8 sum = 0;
	uint16 temp = 0;
	for (uint8 i = 0; i < (num - 1); i++)
		sum += *(data_buf + i);
	if (!(sum == *(data_buf + num - 1)))		return;		//判断sum
	if (!(*(data_buf) == 0xAA && *(data_buf + 1) == 0xAF))		return;		//判断帧头

	if (*(data_buf + 2) == 0X01)
	{
		if (*(data_buf + 4) == 0X02) stop_flag = !stop_flag;
		if (*(data_buf + 4) == 0X01) Tune_Mode = 1;
		if (*(data_buf + 4) == 0X04) Tune_Mode = 2;
		if (*(data_buf + 4) == 0X05) Tune_Mode = 3;
	}

	if (*(data_buf + 2) == 0X10)								//PID1
	{
		temp = ((uint16) (* (data_buf + 4) << 8) | *(data_buf + 5));
		if (temp != 65535)
		{
			PidServo.kp   = 0.001 * (  temp - 30000);
			if (PidServo.kp < 0)PidServo.kp = -(30 + PidServo.kp);
		}
		temp = ((uint16)(*(data_buf + 6) << 8) | *(data_buf + 7));
		if (temp != 65535)
		{
			PidServo.ki    = 0.001 * (  temp - 30000);
			if (PidServo.ki < 0) PidServo.ki = -(30 + PidServo.ki);
		}
		temp = ((uint16)(*(data_buf + 8) << 8) | *(data_buf + 9));
		if (temp != 65535)
		{
			PidServo.kd   = 0.001 * (   temp - 30000);
			if (PidServo.kd < 0) PidServo.kd = -(30 + PidServo.kd);
		}

		//Speed
		temp = ( (uint16)(*(data_buf + 10) << 8) | *(data_buf + 11) );
		if (temp != 65535)
		{
			PidSpeedLeft.kp  = 0.001 * (  temp - 30000);
			if (PidSpeedLeft.kp < 0) PidSpeedLeft.kp = -(30 + PidSpeedLeft.kp);

			PidSpeedRight.kp = PidSpeedLeft.kp;
		}
		temp = ( (uint16)(*(data_buf + 12) << 8) | *(data_buf + 13) );
		if (temp != 65535)
		{
			PidSpeedLeft.ki    = 0.001 * (  temp - 30000);
			if (PidSpeedLeft.ki < 0) PidSpeedLeft.ki = -(30 + PidSpeedLeft.ki);

			PidSpeedRight.ki = PidSpeedLeft.ki;
		}
		temp = ( (uint16)(*(data_buf + 14) << 8) | *(data_buf + 15) );
		if (temp != 65535)
		{
			PidSpeedLeft.kd  = 0.001 * (  temp - 30000);
			if (PidSpeedLeft.kd < 0) PidSpeedLeft.kd = -(30 + PidSpeedLeft.kd);

			PidSpeedRight.kd = PidSpeedLeft.kd;
		}

		//PID3
		temp = ( (uint16)(*(data_buf + 18) << 8) | *(data_buf + 19) );
		if (temp != 65535)
		{
			Gyro_info.RampThresholdValue = temp;

		}

		temp = ( (uint16)(*(data_buf + 20) << 8) | *(data_buf + 21) );
		if (temp != 65535)
		{
			PidSpeedLeft.temp = 0.0001 * ( temp - 30000);
			if (PidSpeedLeft.temp < 0) PidSpeedLeft.temp = -(3 + PidSpeedLeft.temp);
		}

		ANO_DT_Send_Check(*(data_buf + 2), sum);
	}
	if (*(data_buf + 2) == 0X11)
	{
		temp =  (uint16)(*(data_buf + 4) << 8) | *(data_buf + 5);
		if (temp < 2000)
		{
			if (temp < 1000) Speed_Expect = -temp;
			else Speed_Expect = temp - 1000;
		}
		temp =  (uint16)(*(data_buf + 6) << 8) | *(data_buf + 7);
		if (temp < 200)
		{
			if (temp < 100) CCD1_info.CCD_CrossShift = -temp;
			else CCD1_info.CCD_CrossShift = temp - 100;
		}
		temp =  (uint16)(*(data_buf + 8) << 8) | *(data_buf + 9);
		if (temp != 65535) Tune_Mode = 4;

		//ServoFuzzy
		temp = ( (uint16)(*(data_buf + 10) << 8) | *(data_buf + 11) );
		if (temp != 65535)
		{
			ServoFuzzy.kp = 0.001 * ( temp - 30000);
			if (ServoFuzzy.kp < 0) ServoFuzzy.kp = -(30 + ServoFuzzy.kp);
		}
		temp = ( (uint16)(*(data_buf + 10) << 8) | *(data_buf + 11) );
		if (temp != 65535)
		{
			ServoFuzzy.ks = 0.001 * ( temp - 30000);
			if (ServoFuzzy.ks < 0) ServoFuzzy.ks = -(30 + ServoFuzzy.ks);
		}
		temp = ( (uint16)(*(data_buf + 14) << 8) | *(data_buf + 15) );
		if (temp != 65535)
		{
			ServoFuzzy.kd = 0.001 * ( temp - 30000);
			if (ServoFuzzy.kd < 0) ServoFuzzy.kd = -(30 + ServoFuzzy.kd);
		}
		ANO_DT_Send_Check(*(data_buf + 2), sum);
	}
	//***********************模糊表*****************************/
	if (*(data_buf + 2) == 0X12)								//
	{
		//h0
		temp = ((uint16) (* (data_buf + 4) << 8) | *(data_buf + 5));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[0][0] =     temp - 10;
				if ( FRP[0][0] < 0) FRP[0][0] = -(10 + FRP[0][0] );
			}
			else
			{
				FRD[0][0] =     temp - 10;
				if ( FRD[0][0] < 0) FRD[0][0] = -(10 + FRD[0][0] );
			}
		}
		temp = ((uint16)(*(data_buf + 6) << 8) | *(data_buf + 7));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[0][1] =     temp - 10;
				if ( FRP[0][1] < 0) FRP[0][1] = -(10 + FRP[0][1] );
			}
			else
			{
				FRD[0][1] =     temp - 10;
				if ( FRD[0][1] < 0) FRD[0][1] = -(10 + FRD[0][1] );
			}
		}
		temp = ((uint16)(*(data_buf + 8) << 8) | *(data_buf + 9));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[0][2] =     temp - 10;
				if ( FRP[0][2] < 0) FRP[0][2] = -(10 + FRP[0][2] );
			}
			else
			{
				FRD[0][2] =     temp - 10;
				if ( FRD[0][2] < 0) FRD[0][2] = -(10 + FRD[0][2] );
			}
		}

		//h1
		temp = ((uint16) (* (data_buf + 10) << 8) | *(data_buf + 11));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[1][0] =     temp - 10;
				if ( FRP[1][0] < 0) FRP[1][0] = -(10 + FRP[1][0] );
			}
			else
			{
				FRD[1][0] =     temp - 10;
				if ( FRD[1][0] < 0) FRD[1][0] = -(10 + FRD[1][0] );
			}
		}
		temp = ((uint16)(*(data_buf + 12) << 8) | *(data_buf + 13));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[1][1] =     temp - 10;
				if ( FRP[1][1] < 0) FRP[1][1] = -(10 + FRP[1][1] );
			}
			else
			{
				FRD[1][1] =     temp - 10;
				if ( FRD[1][1] < 0) FRD[1][1] = -(10 + FRD[1][1] );
			}
		}
		temp = ((uint16)(*(data_buf + 14) << 8) | *(data_buf + 15));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[1][2] =     temp - 10;
				if ( FRP[1][2] < 0) FRP[1][2] = -(10 + FRP[1][2] );
			}
			else
			{
				FRD[1][2] =     temp - 10;
				if ( FRD[1][2] < 0) FRD[1][2] = -(10 + FRD[1][2] );
			}
		}

		//h2
		temp = ((uint16) (* (data_buf + 16) << 8) | *(data_buf + 17));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[2][0] =     temp - 10;
				if ( FRP[2][0] < 0) FRP[2][0] = -(10 + FRP[2][0] );
			}
			else
			{
				FRD[2][0] =     temp - 10;
				if ( FRD[2][0] < 0) FRD[2][0] = -(10 + FRD[2][0] );
			}
		}
		temp = ((uint16)(*(data_buf + 18) << 8) | *(data_buf + 19));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[2][1] =     temp - 10;
				if ( FRP[2][1] < 0) FRP[2][1] = -(10 + FRP[2][1] );
			}
			else
			{
				FRD[2][1] =     temp - 10;
				if ( FRD[2][1] < 0) FRD[2][1] = -(10 + FRD[2][1] );
			}
		}
		temp = ((uint16)(*(data_buf + 20) << 8) | *(data_buf + 21));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[2][2] =     temp - 10;
				if ( FRP[2][2] < 0) FRP[2][2] = -(10 + FRP[2][2] );
			}
			else
			{
				FRD[2][2] =     temp - 10;
				if ( FRD[2][2] < 0) FRD[2][2] = -(10 + FRD[2][2] );
			}
		}

		ANO_DT_Send_Check(*(data_buf + 2), sum);
	}

	//***********************模糊表*****************************/
	if (*(data_buf + 2) == 0X13)								//
	{
		//h0
		temp = ((uint16) (* (data_buf + 4) << 8) | *(data_buf + 5));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[4][0] =     temp - 10;
				if ( FRP[4][0] < 0) FRP[4][0] = -(10 + FRP[4][0] );
			}
			else
			{
				FRD[4][0] =     temp - 10;
				if ( FRD[4][0] < 0) FRD[4][0] = -(10 + FRD[4][0] );
			}
		}
		temp = ((uint16)(*(data_buf + 6) << 8) | *(data_buf + 7));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[4][1] =     temp - 10;
				if ( FRP[4][1] < 0) FRP[4][1] = -(10 + FRP[4][1] );
			}
			else
			{
				FRD[4][1] =     temp - 10;
				if ( FRD[4][1] < 0) FRD[4][1] = -(10 + FRD[4][1] );
			}
		}
		temp = ((uint16)(*(data_buf + 8) << 8) | *(data_buf + 9));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[4][2] =     temp - 10;
				if ( FRP[4][2] < 0) FRP[4][2] = -(10 + FRP[4][2] );
			}
			else
			{
				FRD[4][2] =     temp - 10;
				if ( FRD[4][2] < 0) FRD[4][2] = -(10 + FRD[4][2] );
			}
		}

		//h1
		temp = ((uint16) (* (data_buf + 10) << 8) | *(data_buf + 11));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[5][0] =     temp - 10;
				if ( FRP[5][0] < 0) FRP[5][0] = -(10 + FRP[5][0] );
			}
			else
			{
				FRD[5][0] =     temp - 10;
				if ( FRD[5][0] < 0) FRD[5][0] = -(10 + FRD[5][0] );
			}
		}
		temp = ((uint16)(*(data_buf + 12) << 8) | *(data_buf + 13));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[5][1] =     temp - 10;
				if ( FRP[5][1] < 0) FRP[5][1] = -(10 + FRP[5][1] );
			}
			else
			{
				FRD[5][1] =     temp - 10;
				if ( FRD[5][1] < 0) FRD[5][1] = -(10 + FRD[5][1] );
			}
		}
		temp = ((uint16)(*(data_buf + 14) << 8) | *(data_buf + 15));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[5][2] =     temp - 10;
				if ( FRP[5][2] < 0) FRP[5][2] = -(10 + FRP[5][2] );
			}
			else
			{
				FRD[5][2] =     temp - 10;
				if ( FRD[5][2] < 0) FRD[5][2] = -(10 + FRD[5][2] );
			}
		}

		//h2
		temp = ((uint16) (* (data_buf + 16) << 8) | *(data_buf + 17));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[6][0] =     temp - 10;
				if ( FRP[6][0] < 0) FRP[6][0] = -(10 + FRP[6][0] );
			}
			else
			{
				FRD[6][0] =     temp - 10;
				if ( FRD[6][0] < 0) FRD[6][0] = -(10 + FRD[6][0] );
			}
		}
		temp = ((uint16)(*(data_buf + 18) << 8) | *(data_buf + 19));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[6][1] =     temp - 10;
				if ( FRP[6][1] < 0) FRP[6][1] = -(10 + FRP[6][1] );
			}
			else
			{
				FRD[6][1] =     temp - 10;
				if ( FRD[6][1] < 0) FRD[6][1] = -(10 + FRD[6][1] );
			}
		}
		temp = ((uint16)(*(data_buf + 20) << 8) | *(data_buf + 21));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[6][2] =     temp - 10;
				if ( FRP[6][2] < 0) FRP[6][2] = -(10 + FRP[6][2] );
			}
			else
			{
				FRD[6][2] =     temp - 10;
				if ( FRD[6][2] < 0) FRD[6][2] = -(10 + FRD[6][2] );
			}
		}

		ANO_DT_Send_Check(*(data_buf + 2), sum);
	}

//***********************模糊表*****************************/
	if (*(data_buf + 2) == 0X14)								//
	{
		//h0
		temp = ((uint16) (* (data_buf + 4) << 8) | *(data_buf + 5));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[0][4] =     temp - 10;
				if ( FRP[0][4] < 0) FRP[0][4] = -(10 + FRP[0][4] );
			}
			else
			{
				FRD[0][4] =     temp - 10;
				if ( FRD[0][4] < 0) FRD[0][4] = -(10 + FRD[0][4] );
			}
		}
		temp = ((uint16)(*(data_buf + 6) << 8) | *(data_buf + 7));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[0][5] =     temp - 10;
				if ( FRP[0][5] < 0) FRP[0][5] = -(10 + FRP[0][5] );
			}
			else
			{
				FRD[0][5] =     temp - 10;
				if ( FRD[0][5] < 0) FRD[0][5] = -(10 + FRD[0][5] );
			}
		}
		temp = ((uint16)(*(data_buf + 8) << 8) | *(data_buf + 9));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[0][6] =     temp - 10;
				if ( FRP[0][6] < 0) FRP[0][6] = -(10 + FRP[0][6] );
			}
			else
			{
				FRD[0][6] =     temp - 10;
				if ( FRD[0][6] < 0) FRD[0][6] = -(10 + FRD[0][6] );
			}
		}

		//h1
		temp = ((uint16) (* (data_buf + 10) << 8) | *(data_buf + 11));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[1][4] =     temp - 10;
				if ( FRP[1][4] < 0) FRP[1][4] = -(10 + FRP[1][4] );
			}
			else
			{
				FRD[1][4] =     temp - 10;
				if ( FRD[1][4] < 0) FRD[1][4] = -(10 + FRD[1][4] );
			}
		}
		temp = ((uint16)(*(data_buf + 12) << 8) | *(data_buf + 13));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[1][5] =     temp - 10;
				if ( FRP[1][5] < 0) FRP[1][5] = -(10 + FRP[1][5] );
			}
			else
			{
				FRD[1][5] =     temp - 10;
				if ( FRD[1][5] < 0) FRD[1][5] = -(10 + FRD[1][5] );
			}
		}
		temp = ((uint16)(*(data_buf + 14) << 8) | *(data_buf + 15));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[1][6] =     temp - 10;
				if ( FRP[1][6] < 0) FRP[1][6] = -(10 + FRP[1][6] );
			}
			else
			{
				FRD[1][6] =     temp - 10;
				if ( FRD[1][6] < 0) FRD[1][6] = -(10 + FRD[1][6] );
			}
		}

		//h2
		temp = ((uint16) (* (data_buf + 16) << 8) | *(data_buf + 17));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[2][4] =     temp - 10;
				if ( FRP[2][4] < 0) FRP[2][4] = -(10 + FRP[2][4] );
			}
			else
			{
				FRD[2][4] =     temp - 10;
				if ( FRD[2][4] < 0) FRD[2][4] = -(10 + FRD[2][4] );
			}
		}
		temp = ((uint16)(*(data_buf + 18) << 8) | *(data_buf + 19));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[2][5] =     temp - 10;
				if ( FRP[2][5] < 0) FRP[2][5] = -(10 + FRP[2][5] );
			}
			else
			{
				FRD[2][5] =     temp - 10;
				if ( FRD[2][5] < 0) FRD[2][5] = -(10 + FRD[2][5] );
			}
		}
		temp = ((uint16)(*(data_buf + 20) << 8) | *(data_buf + 21));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[2][6] =     temp - 10;
				if ( FRP[2][6] < 0) FRP[2][6] = -(10 + FRP[2][6] );
			}
			else
			{
				FRD[2][6] =     temp - 10;
				if ( FRD[2][6] < 0) FRD[2][6] = -(10 + FRD[2][6] );
			}
		}

		ANO_DT_Send_Check(*(data_buf + 2), sum);
	}

//***********************模糊表*****************************/
	if (*(data_buf + 2) == 0X15)								//
	{
		//h0
		temp = ((uint16) (* (data_buf + 4) << 8) | *(data_buf + 5));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[4][4] =     temp - 10;
				if ( FRP[4][4] < 0) FRP[4][4] = -(10 + FRP[4][4] );
			}
			else
			{
				FRD[4][4] =     temp - 10;
				if ( FRD[4][4] < 0) FRD[4][4] = -(10 + FRD[4][4] );
			}
		}
		temp = ((uint16)(*(data_buf + 6) << 8) | *(data_buf + 7));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[4][5] =     temp - 10;
				if ( FRP[4][5] < 0) FRP[4][5] = -(10 + FRP[4][5] );
			}
			else
			{
				FRD[4][5] =     temp - 10;
				if ( FRD[4][5] < 0) FRD[4][5] = -(10 + FRD[4][5] );
			}
		}
		temp = ((uint16)(*(data_buf + 8) << 8) | *(data_buf + 9));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[4][6] =     temp - 10;
				if ( FRP[4][6] < 0) FRP[4][6] = -(10 + FRP[4][6] );
			}
			else
			{
				FRD[4][6] =     temp - 10;
				if ( FRD[4][6] < 0) FRD[4][6] = -(10 + FRD[4][6] );
			}
		}

		//h1
		temp = ((uint16) (* (data_buf + 10) << 8) | *(data_buf + 11));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[5][4] =     temp - 10;
				if ( FRP[5][4] < 0) FRP[5][4] = -(10 + FRP[5][4] );
			}
			else
			{
				FRD[5][4] =     temp - 10;
				if ( FRD[5][4] < 0) FRD[5][4] = -(10 + FRD[5][4] );
			}
		}
		temp = ((uint16)(*(data_buf + 12) << 8) | *(data_buf + 13));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[5][5] =     temp - 10;
				if ( FRP[5][5] < 0) FRP[5][5] = -(10 + FRP[5][5] );
			}
			else
			{
				FRD[5][5] =     temp - 10;
				if ( FRD[5][5] < 0) FRD[5][5] = -(10 + FRD[5][5] );
			}
		}
		temp = ((uint16)(*(data_buf + 14) << 8) | *(data_buf + 15));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[5][6] =     temp - 10;
				if ( FRP[5][6] < 0) FRP[5][6] = -(10 + FRP[5][6] );
			}
			else
			{
				FRD[5][6] =     temp - 10;
				if ( FRD[5][6] < 0) FRD[5][6] = -(10 + FRD[5][6] );
			}
		}

		//h2
		temp = ((uint16) (* (data_buf + 16) << 8) | *(data_buf + 17));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[6][4] =     temp - 10;
				if ( FRP[6][4] < 0) FRP[6][4] = -(10 + FRP[6][4] );
			}
			else
			{
				FRD[6][4] =     temp - 10;
				if ( FRD[6][4] < 0) FRD[6][4] = -(10 + FRD[6][4] );
			}
		}
		temp = ((uint16)(*(data_buf + 18) << 8) | *(data_buf + 19));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[6][5] =     temp - 10;
				if ( FRP[6][5] < 0) FRP[6][5] = -(10 + FRP[6][5] );
			}
			else
			{
				FRD[6][5] =     temp - 10;
				if ( FRD[6][5] < 0) FRD[6][5] = -(10 + FRD[6][5] );
			}
		}
		temp = ((uint16)(*(data_buf + 20) << 8) | *(data_buf + 21));
		if (temp <= 20)
		{
			if (ServoFuzzy.id == 0)
			{
				FRP[6][6] =     temp - 10;
				if ( FRP[6][6] < 0) FRP[6][6] = -(10 + FRP[6][6] );
			}
			else
			{
				FRD[6][6] =     temp - 10;
				if ( FRD[6][6] < 0) FRD[6][6] = -(10 + FRD[6][6] );
			}
		}

		ANO_DT_Send_Check(*(data_buf + 2), sum);
	}

}

static void ANO_DT_Send_Check(uint8 head, uint8 check_sum)
{
	data_to_send[0] = 0xAA;
	data_to_send[1] = 0xAA;
	data_to_send[2] = 0xEF;
	data_to_send[3] = 2;
	data_to_send[4] = head;
	data_to_send[5] = check_sum;


	uint8 sum = 0;
	for (uint8 i = 0; i < 6; i++)
		sum += data_to_send[i];
	data_to_send[6] = sum;

	ANO_Send_Data(data_to_send, 7);
}
