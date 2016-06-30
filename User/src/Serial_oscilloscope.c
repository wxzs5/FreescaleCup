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

uint8 Tune_Mode = 7;
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
		// temp = ((uint16) (* (data_buf + 4) << 8) | *(data_buf + 5));
		// if (temp != 65535)
		// {
		// 	PidServo.kp   = 0.001 * (  temp - 30000);
		// 	if (PidServo.kp < 0)PidServo.kp = -(30 + PidServo.kp);
		// }
		// temp = ((uint16)(*(data_buf + 6) << 8) | *(data_buf + 7));
		// if (temp != 65535)
		// {
		// 	PidServo.ki    = 0.001 * (  temp - 30000);
		// 	if (PidServo.ki < 0) PidServo.ki = -(30 + PidServo.ki);
		// }
		temp = ((uint16) (* (data_buf + 4) << 8) | *(data_buf + 5));
		if (temp != 65535)
		{
			para_a   = 0.001 * (  temp - 30000);
			if (para_a < 0)para_a = -(30 + para_a);
		}
		temp = ((uint16)(*(data_buf + 6) << 8) | *(data_buf + 7));
		if (temp != 65535)
		{
			para_b    = 0.001 * (  temp - 30000);
			if (para_b < 0) para_b = -(30 + para_b);
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
			PidSpeed.kp  = 0.001 * (  temp - 30000);
			if (PidSpeed.kp < 0) PidSpeed.kp = -(30 + PidSpeed.kp);
		}
		temp = ( (uint16)(*(data_buf + 12) << 8) | *(data_buf + 13) );
		if (temp != 65535)
		{
			PidSpeed.ki    = 0.001 * (  temp - 30000);
			if (PidSpeed.ki < 0) PidSpeed.ki = -(30 + PidSpeed.ki);
		}
		temp = ( (uint16)(*(data_buf + 14) << 8) | *(data_buf + 15) );
		if (temp != 65535)
		{
			PidSpeed.kd  = 0.001 * (  temp - 30000);
			if (PidSpeed.kd < 0) PidSpeed.kd = -(30 + PidSpeed.kd);
		}

		//DSpe
		temp = ( (uint16)(*(data_buf + 16) << 8) | *(data_buf + 17) );
		if (temp != 65535)
		{
			PidDSpe.kp 	   = 0.001 * (  temp - 30000);
			if (PidDSpe.kp < 0) PidDSpe.kp = -(30 + PidDSpe.kp);
		}
		temp = ( (uint16)(*(data_buf + 18) << 8) | *(data_buf + 19) );
		if (temp != 65535)
		{
			PidDSpe.ki 	   = 0.001 * (  temp - 30000);
			if (PidDSpe.ki < 0) PidDSpe.ki = -(30 + PidDSpe.ki);
		}
		temp = ( (uint16)(*(data_buf + 20) << 8) | *(data_buf + 21) );
		if (temp != 65535)
		{
			PidDSpe.kd 	   = 0.001 * ( temp - 30000);
			if (PidDSpe.ki < 0) PidDSpe.ki = -(30 + PidDSpe.ki);
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
		if (temp != 65535) Tune_Mode = 0;

		temp =  (uint16)(*(data_buf + 8) << 8) | *(data_buf + 9);
		if (temp != 65535) Tune_Mode = 4;

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
