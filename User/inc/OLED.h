#ifndef _OLED_H_
#define _OLED_H_

#define 	OLED_DA   	PTC11
#define 	OLED_CK 	PTC10
#define 	OLED_DC	PTA24
#define 	OLED_RST	PTA19

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



#endif
