#ifndef __Calculate_H__
#define __Calculate_H__


extern uint8 Left_Board_Value1 ;
extern uint8 Right_Board_Value1 ;
extern int8 Center_Board_Value1 ;

extern uint8 Left_Board_Value2 ;
extern uint8 Right_Board_Value2 ;
extern int8 Center_Board_Value2 ;

extern int8 Center_Board_Value ;

extern float L_bc;
extern float arc_ratio_left;
extern float arc_ratio_right;
extern float arc_ratio;

extern uint8 White_Ahead_Flag ;
extern uint8 Black_Ahead_Flag ;
extern uint8 Pixel_Lose_Left_Flag;
extern uint8 Pixel_Lose_Right_Flag ;
extern uint8 Pixel_Get_Left_Flag1;
extern uint8 Pixel_Get_Right_Flag1;
extern uint8 Pixel_Get_Left_Flag2;
extern uint8 Pixel_Get_Right_Flag2;

extern uint8 CCD1_flag;
extern uint8 CCD2_flag;

void CalculateIntegrationTime(void) ;
uint8 PixelAverage(uint8 len, uint8 *data) ;




uint8 get_min_max(uint8 *Pixel_BUFFER);
uint8 binary_conversion(uint8 *value_des, uint8 *value_scr);
void Filter_Pixel(uint8 *Pixel_des);
void CCD_Get_Line_1(uint8 *rightblackedge, uint8 *leftblackedge, int8 *centre_black);
void CCD_Get_Line_2(uint8 *rightblackedge, uint8 *leftblackedge, int8 *centre_black);
void middle_draw(void);
void give_image(uint8 *ImageData1, uint8 *ImageData2);






#endif
