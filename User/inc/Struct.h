
#ifndef __STRUCT_H__
#define __STRUCT_H__


/*-----------------------选择使用各个功能辅助模块-------------------*/
//#define   RemRoad_Control_Enable	(4)	//记忆算法使能,注意，此算法不能关闭，否则可能导致坡道问题
//#define   PROTECT_CAR_ENABLE		(5)				//出界保护
//#define   GetRoadCondition_Enable	(6)				//获取赛道类型



#define 	SPEED_FIFO_LENGTH		(20)
#define     Line_SIZE   			(45)		//存储左右边界线，中线等的队列长度
#define 	GYRO_LENGTH			(50)		//存储陀螺仪的AD电压值

#define QRANGE(x)       ((x)<(0) ? ((Line_SIZE)-(1)) : ( (x)>((Line_SIZE)-(1)) ? (0):(x) ))   //用于限定队列循环指针的值
#define MYRANGE(x,max,min)      ((x) =((x)<(min) ? (min) : ( (x)>(max) ? (max):(x) )))  //限定范围


/*--------------------我要过六级-------------------------
                                 PID结构体
--------------------------------------------------------*/
typedef struct
{
	float error;     //< 被调量期望值
	float error_pre;    //< 前一次偏差
	float error_pre_pre; //前前次偏差
	float kp;           //< 比例系数
	float ki;           //< 积分系数
	float kd;           //< 比例系数
	float kpi;           //< 比例系数
	float kii;           //< 积分系数
	float kdi;           //< 比例系数
	float outP;         //< pid比例部分，调试用
	float outI;         //< pid积分部分，调试用
	float outD;         //< pid微分部分，调试用
	float out;
	float temp;  //留一个临时变量为PID调节过程中打印参数
} Pidsuite;

typedef enum
{
	// NeedJudge,			//需再判断
	In_Straight,             //在直道
	Into_Curva,             //进弯道
	In_Curva,                 //弯道
	In_Crossing,             //十字
	Into_Obstacle,             //在直道
	Ramp_Up,			//上坡
	Ramp_Down,			//下坡
	Stop			//停车
} Car_State_e;

typedef struct
{
	Car_State_e now;
	Car_State_e pre;
} Car_State;


typedef enum Car_Mode_//----------------------------------------选择速度模式(比赛时速度等级不同)
{
	High2,
	High1,
	Safe,
	Low1,
	Low2,
	SelfDef,				//自定义速度
	CheckCCD,				//调试(前瞻)模式
	CheckSL,				//调试起跑线模式
	CheckRamp				//调试坡道模式
} Car_Mode;

typedef struct CCD_Info_//--------------------------------CCD数据
{
	uint8 PixelOri[2][128];       // CCD原始值
	uint8 Pixel[128];             // CCD滤波后值
	uint8 PixelBinary[128];       // CCD二值化值
	uint8  CCD_PhotoValue[16];    // CCD二维压缩图像存储值

	uint8 AD_MAX[4];              //AD最大值
	uint8 AD_MIN[4];              //AD最小值

	int16 CCD_PhotoCenter;        //图像的中心点
	int16 CCD_ObstacleShift;      //路障的时候图像偏移点数
	int16 CCD_CrossShift;       //十字时偏离的点数
	int16 Cross_state;            //过十字的状态
	int16 Cross_Shift_Counter;

	int16  LeftLine[Line_SIZE];   //左边界队列
	int16  CentralLine[Line_SIZE];  //中线队列
	int16  RightLine[Line_SIZE];    //右边界队列
	int16  LineError[Line_SIZE];		//偏差队列
	int16  LineError_D[Line_SIZE];	//偏差D队列
	int16  RoadWidth[10];				//路宽队列
	//int16 LeftLossLinePixel;      //记录丢左边线时左边的点
	//int16 RightLossLinePixel;     //记录丢右边线时右边的点

	uint8 LeftLossLineFlag;       //左边丢线标志
	uint8 RightLossLineFlag;      //右边丢线标志

	int16  RoadWidthOfStraight;   //直道的路宽

	uint8  CCD_Ready_Num;       //CCD数据有效次数

	uint8 AddLine_Flag;       //补线标记
	uint8 LossLine_Flag;        //CCD丢线标志
	uint8 Cross_Flag;         //十字道标志
	uint8 RoadInvalid_Flag;     //左边赛道无效标记，防止窜道
	uint8 ID;

} CCD_Info;

typedef struct Gyro_Info_//------------------------------------------------陀螺仪
{
	int16 GyroscopeZero;						//记录陀螺仪-加速度计的零点电压AD值
	float Gyroscope_Fifo[GYRO_LENGTH];		//存储陀螺仪-加速度计电压AD值
	float Gyro_Sum;
	int16 counter;   //记录队列尾
	int16 RampThresholdValue;    //上下坡的阈值
	uint8 RampUpDown;		//记录检测到陀螺仪电压突变的次数
	uint8 Ramp_Over_0_1st;
	uint8 Ramp_Less_0;
	uint8 Ramp_Over_0_2nd;
	uint32 Need_Delay_Counter;
} Gyro_Info;

typedef struct Speed_Info_//-------------------------------------------------速度
{
	int16 Straight_Speed;					//直道速度
	int16 Cur_Speed;				 		//弯道速度
	int16 Snake_Speed;					//小S速度
	int16 Obstacle_Speed;					//路障速度
	int16 RampUp_Speed;					//上坡道速度
	int16 RampDown_Speed;					//下坡道速度

	int16 SpeedAdd_3;						//3档的直道最高速度增加值
	float SpeedMode3Add;					//3档速度增加值
	int16 SpeedMode3Acc_Counter;			//使用2档，但使用3档速度档时的条件有效距离(cm)
	uint8 CurSpeedAcc_Flag;				//出弯道加速标记
	float CurSpeedAcc;						//弯道加速值

	int16 Speed_Now;						//当前速度
	int16 TargetSpeed[2];					//目标速度
	int16 SpeedRAcc;						//加速度值

	uint8 SpeedMode;						//速度模式选择
	uint8 LastSpeedMode;					//上一次的速度模式

	int8  Speed_Direction;				//速度方向
	int16 EncoderData;					//编码器寄存器的值
	int16 SpeedFifo[SPEED_FIFO_LENGTH];	//速度队列
	int16 SpeedError;						//速度偏差
	int16 LastSpeedError;					//上一次的速度偏差

	int32 DistanceTo1CmCount;				//1cm脉冲计数
	uint8 DistanceOf1Cm_Flag;				// 1cm到了标记
	int16 DistanceOfCross_Counter;		//十字道1cm距离计数
	int16 DistanceOfRampUp[2];			//上坡距离
	int16 DistanceOfRampDown;				//下坡距离
	int16 DistanceOfRampUp_Counter;		//上坡道1cm距离计数
	int16 DistanceOfObstacle_Counter;		//路障1cm距离计数
	int16 DistanceOfSpeedMode3_Counter;	//3档高速1cm距离计数
	int16 DistanceOfSpeedMode3_Max;		//使用3档的最大高速距离

	uint8 SpeedCalculate_Enable;			//计算速度使能

} Speed_Info;

typedef struct Parameter_Info_//------------------------------------------一些参数
{
	float StartEndLine_Fifo[10][2];		//起跑线队列,10行2列，第一列记录红外管标号，第二列记录采集时间

	float AD_MultK_f;
	float CCD1_AD_TargetValue;			//CCD电压放大的目标值
	int16 CCD1_Binary_MAX;			//CCD阈值上限
	int16 CCD1_Binary_MIN;			//CCD阈值下限

	int16 Mode_HighSpeedDistance;		//高速距离

	float	Time;						//行驶时间(秒)
	float   GetStartEndLineTime;		//起跑线检测倒计时，超过该时间才检测起跑线
	float	GetRampTime;				//开始检测坡道的时间
	float   GetObstacleTime;			//开始检测路障的时间
	float	DebugTime;					//调试时间(秒)
	float	LoseLineTime;				//丢线停车时间
	int32 RoadDistance;				//行驶距离(厘米)
	int16 StopSpeed;					//停车前一刻速度

	uint8 CCD_SampleOK_Flag;  		//CCD采样完成标志
	uint8 StartEndLine_Flag; 			//检测到起跑线标志

	uint8 LeftOrRightObstacle_Flag;	//路障标记(左边路障/右边路障)

	int32 OLED_NoAction_Counter;		//按键没反应计数
	uint8 OLED_NoAction_Flag;			//按键没有反应标志
	uint8 RampReady_Distance;			//预判坡道超过该距离还未判断到坡道则清除预判标记，防止预判错误时长时间减速
	uint8 RampReady_FLag;				//坡道预判标记
	uint8 LongStraight_Flag;

	uint8 SD_Data_name_Change;  //SD卡存储信息

} Parameter_Info;


typedef struct Flash_Info_//------------------------------------------------Flash操作
{
	float   Flash_Array_1[100];
	float   Flash_Array_2[100];
	float   Flash_Array_3[100];

} Flash_Info;


typedef struct           //OLED选择菜单
{
	uint8  enter_exit;
	int16 choice_flag;
	uint8  enter_exit_temp;
	uint8  Clear;
	uint8  Ready_Go;
	uint8  Tun_Res;
} menu;


extern Pidsuite PidServo;
extern Pidsuite PidSpeedLeft;
extern Pidsuite PidSpeedRight;


//新版
extern Parameter_Info  Parameter_info;
extern Car_State  	Car_state;
extern Car_Mode    Car_mode;
extern menu Menu;


extern CCD_Info CCD1_info;
extern CCD_Info CCD2_info;


extern Speed_Info Speed_info;
extern Gyro_Info Gyro_info;
extern Flash_Info Flash_info;




//函数声明
extern void myData_Init();   //数据信息初始化



typedef struct {
	float x;
	float y;
	float z;
} Gyro_Data;

typedef struct {
	float x;
	float y;
	float z;
} Acc_Data;

typedef struct {
	float gyro;
	float acc;
	float result;
} Q_Angle;



extern Gyro_Data Gyro_data;
extern Acc_Data  Acc_data;
extern Q_Angle Q_angle;



#endif

/*-----------------------------end of myStruct.h----------------------------------*/


