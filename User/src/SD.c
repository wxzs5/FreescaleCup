
#include"include.h"

#define Parameter_Size   100

FATFS   Carfs;     //文件系统
FIL     Car_Parmeter_file;   //参数文件
FIL     Car_RunData_file;   //数据文件

uint32 size, sizetmp ;
int res;
uint8 Parameters[Parameter_Size];




/*************************************************************************
*                             我要过六级
*  函数名称:mySD_Init_Parameter
*  功能说明:
*  参数说明:
*
*  函数返回:
*  修改时间:
*  备     注:此处初始化SD卡，注意SD卡不能频繁打开
*************************************************************************/
void mySD_Init_Parameter(void)
{

  f_mount(0, &Carfs);                                                               //挂载文件系统

  //初始化 SD卡 在 f_open 上执行,目前代码只支持打开一个文件(由 _FS_SHARE 配置)，频繁打开文件会消耗CPU资源
  res = f_open(&Car_Parmeter_file, "0:/Param.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);  //打开文件，如果没有就创建，带读写打开

  if ( res == FR_DISK_ERR)
  {
    myOLED_Clear();
    myOLED_String(4, 10, "No SD Card!");
    return;
  }
  else if ( res == FR_OK )
  {
    myOLED_Clear();
    myOLED_String(4, 10, "SD Open successful!");
  }
  else
  {
    myOLED_Clear();
    myOLED_String(4, 10, "SD return Invalid value!");
    return;
  }

  size = f_size(&Car_Parmeter_file);                   //获取文件的大小

  if (size > Parameter_Size)size = Parameter_Size;  //防止溢出

  f_lseek(&Car_Parmeter_file, 0);                      //把指针指向文件顶部
  f_read (&Car_Parmeter_file, Parameters, Parameter_Size, &sizetmp);   //读取
  mySD_Get_Parameter();

}


/*************************************************************************
*                             我要过六级
*  函数名称:mySDWrite_Para
*  功能说明:
*  参数说明:
*
*  函数返回:
*  修改时间:
*  备     注:
*************************************************************************/
void mySDWrite_Para(void)
{
  memset(Parameters, 0, Parameter_Size);
  mySD_Load_Parameter();

  f_lseek(&Car_Parmeter_file, 0);                      //把指针指向文件顶部
  f_puts(Parameters, &Car_Parmeter_file);                     //往文件里写入字符串

  f_sync(&Car_Parmeter_file);                          //刚才写入了数据，实际上数据并没真正完成写入，需要调用此函数同步或者关闭文件，才会真正写入

  f_close(&Car_Parmeter_file);                         //关闭参数文件，一定要和参数打开配对
  myOLED_Clear();
}


/*************************************************************************
*                             我要过六级
*  函数名称:mySD_Load_Parameter
*  功能说明:把修改的参数放入SD卡中
*  参数说明:
*
*  函数返回:
*  修改时间:
*  备     注:
*************************************************************************/
void mySD_Load_Parameter(void)
{
  Parameters[0] = (int16)(PidServo.kp * 1000) / 256;
  Parameters[1] = (int16)(PidServo.kp * 1000) % 256;
  Parameters[2] = (int16)(PidServo.ki * 1000) / 256;
  Parameters[3] = (int16)(PidServo.ki * 1000) % 256;
  Parameters[4] = (int16)(PidServo.kd * 1000) / 256;
  Parameters[5] = (int16)(PidServo.kd * 1000) % 256;

  Parameters[6] = (int16)(PidServo.kp * 1000) / 256;
  Parameters[7] = (int16)(PidServo.kp * 1000) % 256;
  Parameters[8] = (int16)(PidServo.ki * 1000) / 256;
  Parameters[9] = (int16)(PidServo.ki * 1000) % 256;
  Parameters[10] = (int16)(PidServo.kd * 1000) / 256;
  Parameters[11] = (int16)(PidServo.kd * 1000) % 256;

  Parameters[12] = (uint16)(Speed_Expect) / 256;
  Parameters[13] = (uint16)(Speed_Expect) % 256;
  Parameters[14] = Parameter_info.SD_Data_name_Change;

  Parameters[15] = 0;
  Parameters[16] = 0;
  Parameters[17] = 0;
  Parameters[18] = 0;
  Parameters[19] = 0;
  Parameters[20] = 0;
  Parameters[21] = 0;
  Parameters[22] = 0;
  Parameters[23] = 0;
  Parameters[24] = 0;
  Parameters[25] = 0;
  Parameters[26] = 0;
}


/*************************************************************************
*                             我要过六级
*  函数名称:mySD_Load_Parameter
*  功能说明:把修改的参数放入SD卡中
*  参数说明:
*
*  函数返回:
*  修改时间:
*  备     注:
*************************************************************************/
void mySD_Get_Parameter(void)
{
  PidServo.kp = (float)(0.001 * (int16)(Parameters[0] << 8 | Parameters[1]));
  PidServo.ki = (float)(0.001 * (int16)(Parameters[2] << 8 | Parameters[3]));
  PidServo.kd = (float)(0.001 * (int16)(Parameters[4] << 8 | Parameters[5]));
  PidSpeedLeft.kp = (float)(0.001 * (int16)(Parameters[6] << 8 | Parameters[7]));
  PidSpeedLeft.ki = (float)(0.001 * (int16)(Parameters[8] << 8 | Parameters[9]));
  PidSpeedLeft.kd = (float)(0.001 * (int16)(Parameters[10] << 8 | Parameters[11]));

  PidSpeedRight.kp = PidSpeedLeft.kp;
  PidSpeedRight.ki = PidSpeedLeft.ki;
  PidSpeedRight.kd = PidSpeedLeft.kd;
  
  Speed_Expect = (float)(Parameters[12] << 8 | Parameters[13]);
  Parameter_info.SD_Data_name_Change = Parameters[14] ;
}
