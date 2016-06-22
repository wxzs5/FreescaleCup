#ifndef __Serial_oscilloscope_H__
#define __Serial_oscilloscope_H__


extern uint8 data_to_send[50];         //发送缓存
extern uint8 Tune_Mode;



void Data_Send(uint8 *data);
void ANO_Send_Data(uint8 *Buff, uint8 len);
void ANO_DT_Data_Receive_Anl(uint8 *data_buf, uint8 num);
void ANO_DT_Data_Receive_Prepare(uint8 data);
static void ANO_DT_Send_Check(uint8 head, uint8 check_sum);



#define    UartDataNum  34

/////////////////////////////////////////////////////////////////////////////////////
//数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)    ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )



extern uint8   SendBuf[UartDataNum ];

void push(uint8 chanel, uint16 data);



#endif
