#ifndef _SD_H_
#define _SD_H_

#define TESTSD 0

extern FIL     Car_RunData_file;   //数据文件
extern FIL     Car_Parmeter_file;   //参数文件

void mySD_Init_Parameter(void);
void mySDWrite_Para(void);
void mySD_Get_Parameter(void);
void mySD_Load_Parameter(void);
void mySDWrite_Para_End(void);
void mySD_Write_Contr_Data(Pidsuite *Pid, Fuzzysuite *fuzzy);
void mySD_Write_CCD(CCD_Info *ccd);
void mySD_Write_Status(void);
void mySD_RunData_Init();

#endif
