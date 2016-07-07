#ifndef _OLED_H_
#define _OLED_H_

#define   OLED_DA     PTC11
#define   OLED_CK   PTC10
#define   OLED_DC PTA24
#define   OLED_RST  PTA19


#define   zhi  Speed_info.Straight_Speed
#define   wan  Speed_info.Cur_Speed
#define   x_s  Speed_info.Snake_Speed
#define   Up   Speed_info.RampUp_Speed
#define   Dn   Speed_info.RampDown_Speed
#define   LuZ  Speed_info.Obstacle_Speed

#define  SExp  Speed_Expect;
#define   Add3 Speed_info.SpeedAdd_3
#define   E_K  Speed_info.Error_K
#define   Chfile Parameter_info.SD_Data_name_Change

#define   S_P   Steer_info.Pid.kp
#define   S_I   Steer_info.Pid.ki
#define   S_D   Steer_info.Pid.kd
#define   S_PI   Steer_info.Pid.kpi
#define   S_II   Steer_info.Pid.kii
#define   S_DI   Steer_info.Pid.kdi

#define   VP  Motor_info.Pid.kp
#define   VI   Motor_info.Pid.ki
#define   VD   Motor_info.Pid.kd
#define   VPI  Motor_info.Pid.kpi
#define   VII   Motor_info.Pid.kii
#define   VDI   Motor_info.Pid.kdi

#define   D_T  Parameter_info.DebugTime
#define   Po_T Parameter_info.GetRampTime
#define   LuZ_T  Parameter_info.GetObstacleTime
#define   S_T Parameter_info.GetStartEndLineTime

#define   jl_3  Speed_info.DistanceOfSpeedMode3_Max
#define   Po_S1 Speed_info.DistanceOfRampUp[0]
#define   Po_S2 Speed_info.DistanceOfRampUp[1]
#define   Po_X  Speed_info.DistanceOfRampDown

#define   R_tp  Road_type
#define   Ramp  Gyro_info.RampThresholdValue
#define   Wu_x  Parameter_info.RoadInvalid_Enable
#define   S_L Parameter_info.GetStartEndLine_Flag
#define   CCDL  Parameter_info.CCD1GetSL_Enable

#ifdef RemRoad_Control_Enable

#define   S_Z1  RemSpeedUpDown_info.Cross_Num[0]
#define   S_Z2  RemSpeedUpDown_info.Cross_Num[1]
#define   SQ1   RemSpeedUpDown_info.CrossRemDistance[0]
#define   SG1   RemSpeedUpDown_info.CrossRemDistance[1]
#define   SQ2   RemSpeedUpDown_info.CrossRemDistance[2]
#define   SG2   RemSpeedUpDown_info.CrossRemDistance[3]

#define   P_D1  RemSpeedUpDown_info.Ramp_Num[0]
#define   P_D2  RemSpeedUpDown_info.Ramp_Num[1]
#define   PQ1   RemSpeedUpDown_info.RampRemDistance[0]
#define   PG1   RemSpeedUpDown_info.RampRemDistance[1]
#define   PQ2   RemSpeedUpDown_info.RampRemDistance[2]
#define   PG2   RemSpeedUpDown_info.RampRemDistance[3]

#define   Jiyi  RemSpeedUpDown_info.RemRoad_Enable
#define   C_J Parameter_info.WheelOutOfWay_Enable
#define   P_Y   CCD2_info.CCD_ObstacleShift
#define   RNum  Parameter_info.TurnRound_Num_MAX

#endif

#define   B_T Parameter_info.CCD1_AD_TargetValue
#define   b_m Parameter_info.CCD1_Binary_MIN
#define   B_M Parameter_info.CCD1_Binary_MAX
#define   Sght  Parameter_info.Mode_HighSpeedDistance



void myOLED_GPIO_Init(void);
void myOLED_Init(void);
void myOLED_Write_REG(uint8 COM);
void myOLED_Write_DAT(uint8 DAT);
void myOLED_REST(void);
void myOLED_Clear(void);
void myOLED_RefreshGRAM(void);

void myOLED_String(uint8 x, uint8 y, const char *P);
void myOLED_Char(uint8 ch);
void myOLED_Set_XY(uint8 x, uint8 y);
void myOLED_Dec(uint8 x, uint8 y, uint16 DEC);
void myOLED_Dec4(uint8 x, uint8 y, int16 DEC);
void myOLED_ADC_value(uint16 * value);
void myOLED_XY_point(uint8 x, uint8 y, uint8 ch);

void myOLED_Decimals(uint8 x, uint8 y, float als);

void myOLED_CCDwave(CCD_Info * CCD1_info, CCD_Info * CCD2_info);

uint8 lcd_menu_display_init(menu * Menu);

#endif
