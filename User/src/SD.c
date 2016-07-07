
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

  // size = f_size(&Car_Parmeter_file);                   //获取文件的大小
  // if (size > Parameter_Size)size = Parameter_Size;  //防止溢出

  f_lseek(&Car_Parmeter_file, 0);                      //把指针指向文件顶部
  f_read (&Car_Parmeter_file, Parameters, Parameter_Size, &sizetmp);   //读取
  mySD_Get_Parameter();
  DELAY_MS(200);  //用于显示SD卡信息初始化情况
  myOLED_Clear();
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

  Parameters[6] = (int16)(PidSpeedLeft.kp * 1000) / 256;
  Parameters[7] = (int16)(PidSpeedLeft.kp * 1000) % 256;
  Parameters[8] = (int16)(PidSpeedLeft.ki * 1000) / 256;
  Parameters[9] = (int16)(PidSpeedLeft.ki * 1000) % 256;
  Parameters[10] = (int16)(PidSpeedLeft.kd * 1000) / 256;
  Parameters[11] = (int16)(PidSpeedLeft.kd * 1000) % 256;
  //期望速度
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
*  修改时间:2016-7-3
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

/*************************************************************************
*                             我要过六级
*  函数名称:mySD_Load_Parameter
*  功能说明:初始化小车运行数据文件
*  参数说明:
*
*  函数返回:
*  修改时间:2016-7-4
*  备     注:
*************************************************************************/
void mySD_RunData_Init()
{
  Parameter_info.SD_Data_name_Change = (Parameter_info.SD_Data_name_Change + 1) % 10;
  switch (Parameter_info.SD_Data_name_Change)
  {
  case 0:
    f_unlink("0:/RunData1.txt");
    res = f_open(&Car_RunData_file, "0:/RunData1.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    break;
  case 1:
    f_unlink("0:/RunData2.txt");
    res = f_open(&Car_RunData_file, "0:/RunData2.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    break;
  case 2:
    f_unlink("0:/RunData3.txt");
    res = f_open(&Car_RunData_file, "0:/RunData3.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    break;
  case 3:
    f_unlink("0:/RunData4.txt");
    res = f_open(&Car_RunData_file, "0:/RunData4.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    break;
  case 4:
    f_unlink("0:/RunData5.txt");
    res = f_open(&Car_RunData_file, "0:/RunData5.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    break;
  case 5:
    f_unlink("0:/RunData6.txt");
    res = f_open(&Car_RunData_file, "0:/RunData6.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    break;
  case 6:
    f_unlink("0:/RunData7.txt");
    res = f_open(&Car_RunData_file, "0:/RunData7.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    break;
  case 7:
    f_unlink("0:/RunData8.txt");
    res = f_open(&Car_RunData_file, "0:/RunData8.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    break;
  case 8:
    f_unlink("0:/RunData9.txt");
    res = f_open(&Car_RunData_file, "0:/RunData9.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    break;
  case 9:
    f_unlink("0:/RunData0.txt");
    res = f_open(&Car_RunData_file, "0:/RunData0.txt", FA_OPEN_ALWAYS | FA_WRITE | FA_READ);
    break;
  default:
    res = 25;
    break;
  }
  if ( res == FR_DISK_ERR)
  {
    myOLED_Clear();
    myOLED_String(4, 10, "No SD Card!");
    return;
  }
  else if ( res == FR_OK )
  {
    myOLED_Clear();
    myOLED_String(4, 10, "Rundata successful!");
    f_lseek(&Car_RunData_file, 0);                      //把指针指向文件顶部
  }
  else if (res == 25)
  {
    myOLED_Clear();
    myOLED_String(4, 10, "not choice Rundata!");
  }
  else
  {
    myOLED_Clear();
    myOLED_String(4, 10, "SD return Invalid value!");
    return;
  }
  DELAY_MS(200);
}

/*************************************************************************
*                             我要过六级
*  函数名称:mySD_Write_CCD
*  功能说明:初始化小车运行数据文件
*  参数说明:
*
*  函数返回:
*  修改时间:2016-7-4
*  备     注:
*************************************************************************/
void mySD_Write_CCD(CCD_Info *ccd)
{
  uint8 ii = 0;
  f_puts("\n CCD Info\n", &Car_RunData_file);
  f_putc(ccd->ID, &Car_RunData_file);
  f_putc(((uint8)ccd->CentralLine[0]), &Car_RunData_file);
  f_putc(ccd->AddLine_Flag, &Car_RunData_file);
  f_putc(ccd->LossLine_Flag, &Car_RunData_file);
  f_putc(ccd->LeftLossLineFlag, &Car_RunData_file);
  f_putc(ccd->RightLossLineFlag, &Car_RunData_file);
  f_putc(ccd->Cross_Flag, &Car_RunData_file);
  f_putc(ccd->CCD_Ready_Num, &Car_RunData_file);

  for (ii = 0; ii < 16; ii++)
  {
    ccd->CCD_PhotoValue[ii] =   (ccd->PixelBinary[7 + 8 * ii] << 7)
                                | (ccd->PixelBinary[6 + 8 * ii] << 6)
                                | (ccd->PixelBinary[5 + 8 * ii] << 5)
                                | (ccd->PixelBinary[4 + 8 * ii] << 4)
                                | (ccd->PixelBinary[3 + 8 * ii] << 3)
                                | (ccd->PixelBinary[2 + 8 * ii] << 2)
                                | (ccd->PixelBinary[1 + 8 * ii] << 1)
                                | (ccd->PixelBinary[0 + 8 * ii])
                                ;
  }

  f_puts(ccd->CCD_PhotoValue, &Car_RunData_file);
  f_sync(&Car_RunData_file);
}

/*************************************************************************
*                             我要过六级
*  函数名称:mySD_Write_Contr_Data
*  功能说明:初始化小车运行数据文件
*  参数说明:
*
*  函数返回:
*  修改时间:2016-7-4
*  备     注:
*************************************************************************/
void mySD_Write_Contr_Data(Pidsuite *Pid)
{
  int16 temp = 0;
  f_puts("\n Pid output info\n", &Car_RunData_file);
  f_putc(Pid->ID, &Car_RunData_file);
  temp = (int16)(Pid->kp * 1000);
  f_putc((uint8)(temp >> 8), &Car_RunData_file); f_putc((uint8)(temp & 0x00ff), &Car_RunData_file);
  temp = (int16)(Pid->ki * 1000);
  f_putc((uint8)(temp >> 8), &Car_RunData_file); f_putc((uint8)(temp & 0x00ff), &Car_RunData_file);
  temp = (int16)(Pid->kd * 1000);
  f_putc((uint8)(temp >> 8), &Car_RunData_file); f_putc((uint8)(temp & 0x00ff), &Car_RunData_file);
  temp = (int16)(Pid->error);
  f_putc((uint8)(temp >> 8), &Car_RunData_file); f_putc((uint8)(temp & 0x00ff), &Car_RunData_file);
  temp = (int16)(Pid->outP);
  f_putc((uint8)(temp >> 8), &Car_RunData_file); f_putc((uint8)(temp & 0x00ff), &Car_RunData_file);
  temp = (int16)(Pid->outI);
  f_putc((uint8)(temp >> 8), &Car_RunData_file); f_putc((uint8)(temp & 0x00ff), &Car_RunData_file);
  temp = (int16)(Pid->outD);
  f_putc((uint8)(temp >> 8), &Car_RunData_file); f_putc((uint8)(temp & 0x00ff), &Car_RunData_file);
  temp = (int16)(Pid->out);
  f_putc((uint8)(temp >> 8), &Car_RunData_file); f_putc((uint8)(temp & 0x00ff), &Car_RunData_file);
  f_sync(&Car_RunData_file);
}


