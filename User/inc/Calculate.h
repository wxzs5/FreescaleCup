#ifndef __Calculate_H__
#define __Calculate_H__

#define CCD_Dark_Current 0      //CCD暗电流

#define     ROAD_WIDETH_1_MAX   90      //CCD1 直道上占55个点  33-88 55
#define     ROAD_WIDETH_1_MIN   20

#define     ROAD_WIDETH_2_MAX   120     //CCD2 直道上占90个点  27-118 90
#define     ROAD_WIDETH_2_MIN   50

#define     CCD_Binary_MIN      180
#define     CCD_Binary_MAX      195

extern int16 Center_Board_Value;
void myCCD_DataInit(CCD_Info *CCD_info);

void myCCD_FilterAndBinarization(   CCD_Info *CCD1_info,
                                    CCD_Info *CCD2_info
                                );

void Filter_binary(CCD_Info *CCD1_info, CCD_Info *CCD2_info);

void myCCD_FilterAtFirst(CCD_Info *CCD1_info, CCD_Info *CCD2_info);

//起跑的时候获得道路偏差
void myCCD_GetBeginLineError(   CCD_Info *CCD1_info,
                                CCD_Info *CCD2_info,
                                Speed_Info *Speed_info
                            );
void myCCD_DataHandle(  CCD_Info *CCD1_info,
                        CCD_Info *CCD2_info,
                        Speed_Info *Speed_info
                     );

void myCCD_CCD1_GetLineError(CCD_Info *CCD1_info, Speed_Info *Speed_info);

void myCCD_CCD2_GetLineError(CCD_Info *CCD2_info);

uint8 myCCD_GetObstacle(CCD_Info *CCD1_info, CCD_Info *CCD2_info);


#endif
