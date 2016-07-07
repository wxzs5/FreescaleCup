#include"include.h"


#define MAP(b,c,d)  ((b)=(((Menu->Tun_Res)-(40.0))/(100.0)*((c)-(d))+(d)))


uint8 OLED_GRAM[8][128];
uint8  ASCII_code[101][6] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // (0)
	{0x00, 0x00, 0x00, 0x4F, 0x00, 0x00}, //!(1)
	{0x00, 0x00, 0x07, 0x00, 0x07, 0x00}, //"(2)
	{0x00, 0x14, 0x7F, 0x14, 0x7F, 0x14}, //#(3)
	{0x00, 0x24, 0x2A, 0x7F, 0x2A, 0x12}, //$(4)
	{0x00, 0x23, 0x13, 0x08, 0x64, 0x62}, //%(5)
	{0x00, 0x36, 0x49, 0x55, 0x22, 0x50}, //&(6)
	{0x00, 0x00, 0x05, 0x03, 0x00, 0x00}, //'(7)
	{0x00, 0x00, 0x1C, 0x22, 0x41, 0x00}, //((8)
	{0x00, 0x00, 0x41, 0x22, 0x1C, 0x00}, //)(9)
	{0x00, 0x14, 0x08, 0x3E, 0x08, 0x14}, //*(10)
	{0x00, 0x08, 0x08, 0x3E, 0x08, 0x08}, //+(11)
	{0x00, 0x00, 0x50, 0x30, 0x00, 0x00}, //,(12)
	{0x00, 0x08, 0x08, 0x08, 0x08, 0x08}, //-(13)
	{0x00, 0x00, 0x60, 0x60, 0x00, 0x00}, //.(14)
	{0x00, 0x20, 0x10, 0x08, 0x04, 0x02}, ///(15)
	{0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E}, //0(16)
	{0x00, 0x00, 0x42, 0x7F, 0x40, 0x00}, //1(17)
	{0x00, 0x42, 0x61, 0x51, 0x49, 0x46}, //2(18)
	{0x00, 0x21, 0x41, 0x45, 0x4B, 0x31}, //3(19)
	{0x00, 0x18, 0x14, 0x12, 0x7F, 0x10}, //4(20)
	{0x00, 0x27, 0x45, 0x45, 0x45, 0x39}, //5(21)
	{0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30}, //6(22)
	{0x00, 0x01, 0x71, 0x09, 0x05, 0x03}, //7(23)
	{0x00, 0x36, 0x49, 0x49, 0x49, 0x36}, //8(24)
	{0x00, 0x06, 0x49, 0x49, 0x29, 0x1E}, //9(25)
	{0x00, 0x00, 0x36, 0x36, 0x00, 0x00}, //:(26)
	{0x00, 0x00, 0x56, 0x36, 0x00, 0x00}, //;(27)
	{0x00, 0x08, 0x14, 0x22, 0x41, 0x00}, //<(28)
	{0x00, 0x14, 0x14, 0x14, 0x14, 0x14}, //=(29)
	{0x00, 0x00, 0x41, 0x22, 0x14, 0x08}, //>(30)
	{0x00, 0x02, 0x01, 0x51, 0x09, 0x06}, //?(31)
	{0x00, 0x32, 0x49, 0x79, 0x41, 0x3E}, //@(32)
	{0x00, 0x7E, 0x11, 0x11, 0x11, 0x7E}, //A(33)
	{0x00, 0x7F, 0x49, 0x49, 0x49, 0x3E}, //B(34)
	{0x00, 0x3E, 0x41, 0x41, 0x41, 0x22}, //C(35)
	{0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C}, //D(36)
	{0x00, 0x7F, 0x49, 0x49, 0x49, 0x41}, //E(37)
	{0x00, 0x7F, 0x09, 0x09, 0x09, 0x01}, //F(38)
	{0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A}, //G(39)
	{0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F}, //H(40)
	{0x00, 0x00, 0x41, 0x7F, 0x41, 0x00}, //I(41)
	{0x00, 0x20, 0x40, 0x41, 0x3F, 0x01}, //J(42)
	{0x00, 0x7F, 0x08, 0x14, 0x22, 0x41}, //K(43)
	{0x00, 0x7F, 0x40, 0x40, 0x40, 0x40}, //L(44)
	{0x00, 0x7F, 0x02, 0x04, 0x02, 0x7F}, //M(45)
	{0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F}, //N(46)
	{0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E}, //O(47)
	{0x00, 0x7F, 0x09, 0x09, 0x09, 0x06}, //P(48)
	{0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E}, //Q(49)
	{0x00, 0x7F, 0x09, 0x19, 0x29, 0x46}, //R(50)
	{0x00, 0x46, 0x49, 0x49, 0x49, 0x31}, //S(51)
	{0x00, 0x01, 0x01, 0x7F, 0x01, 0x01}, //T(52)
	{0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F}, //U(53)
	{0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F}, //V(54)
	{0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F}, //W(55)
	{0x00, 0x63, 0x14, 0x08, 0x14, 0x63}, //X(56)
	{0x00, 0x03, 0x04, 0x78, 0x04, 0x03}, //Y(57)
	{0x00, 0x61, 0x51, 0x49, 0x45, 0x43}, //Z(58)
	{0x00, 0x00, 0x7F, 0x41, 0x41, 0x00}, //[(59)
	{0x00, 0x15, 0x16, 0x7C, 0x16, 0x15}, //\(60)
	{0x00, 0x00, 0x41, 0x41, 0x7F, 0x00}, //](61)
	{0x00, 0x04, 0x02, 0x01, 0x02, 0x04}, //^(62)
	{0x00, 0x40, 0x40, 0x40, 0x40, 0x40}, //_(63)
	{0x00, 0x00, 0x01, 0x02, 0x04, 0x00}, //`(64)
	{0x00, 0x20, 0x54, 0x54, 0x54, 0x78}, //a(65)
	{0x00, 0x7F, 0x48, 0x44, 0x44, 0x38}, //b(66)
	{0x00, 0x38, 0x44, 0x44, 0x44, 0x20}, //c(67)
	{0x00, 0x38, 0x44, 0x44, 0x48, 0x7F}, //d(68)
	{0x00, 0x38, 0x54, 0x54, 0x54, 0x18}, //e(69)
	{0x00, 0x08, 0x7E, 0x09, 0x01, 0x02}, //f(70)
	{0x00, 0x0C, 0x52, 0x52, 0x52, 0x3E}, //g(71)
	{0x00, 0x7F, 0x08, 0x04, 0x04, 0x78}, //h(72)
	{0x00, 0x00, 0x44, 0x7D, 0x40, 0x00}, //i(73)
	{0x00, 0x20, 0x40, 0x44, 0x3D, 0x00}, //j(74)
	{0x00, 0x7F, 0x10, 0x28, 0x44, 0x00}, //k(75)
	{0x00, 0x00, 0x41, 0x7F, 0x40, 0x00}, //l(76)
	{0x00, 0x7E, 0x02, 0x0C, 0x02, 0x7C}, //m(77)
	{0x00, 0x7E, 0x04, 0x02, 0x02, 0x7C}, //n(78)
	{0x00, 0x38, 0x44, 0x44, 0x44, 0x38}, //o(79)
	{0x00, 0x7C, 0x14, 0x14, 0x14, 0x08}, //p(80)
	{0x00, 0x08, 0x14, 0x14, 0x18, 0x7C}, //q(81)
	{0x00, 0x7C, 0x08, 0x04, 0x04, 0x08}, //r(82)
	{0x00, 0x48, 0x54, 0x54, 0x54, 0x20}, //s(83)
	{0x00, 0x04, 0x3F, 0x44, 0x40, 0x20}, //t(84)
	{0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C}, //u(85)
	{0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C}, //v(86)
	{0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C}, //w(87)
	{0x00, 0x44, 0x28, 0x10, 0x28, 0x44}, //x(88)
	{0x00, 0x0C, 0x50, 0x50, 0x50, 0x3C}, //y(89)
	{0x00, 0x44, 0x64, 0x54, 0x4C, 0x44}, //z(90)
	{0x00, 0x00, 0x08, 0x36, 0x41, 0x00}, //{(91)
	{0x00, 0x00, 0x00, 0x7F, 0x00, 0x00}, //|(92)
	{0x00, 0x00, 0x41, 0x36, 0x08, 0x00}, //}(93)
	{0x00, 0x08, 0x04, 0x08, 0x10, 0x08}, //~(94)
	{0x00, 0x08, 0x08, 0x2A, 0x1C, 0x08}, //?(127)
	{0x00, 0x08, 0x1C, 0x2A, 0x08, 0x08}, //?(128)
	{0x00, 0x04, 0x02, 0x7F, 0x02, 0x04}, //?(129)
	{0x00, 0x10, 0x20, 0x7F, 0x20, 0x10}, //?(130)
	{0x00, 0x1C, 0x2A, 0x32, 0x2A, 0x1C}, //??(131)
	{0x00, 0x1C, 0x22, 0x44, 0x22, 0x1C} //??(132)
};

uint16 ADC_value[128] = {
	/*
				0x1FF0,0x1FF0,0x1FF0,0x1FF0,0x1FF0,
				0x1FF0,0x1FF0,0x1FF0,0x1FF0,0x1FF0,
				0x1FF0,0x1FF0,0x1FF0,0x1FF0,0x1FF0,
				0x1FF0,0x1FF0,0x1FF0,0x1FF0,0x1FF0,	//20

				0x2FF0,0x2FF0,0x2FF0,0x2FF0,0x2FF0,
				0x2FF0,0x2FF0,0x2FF0,0x2FF0,0x2FF0,
				0x2FF0,0x2FF0,0x2FF0,0x2FF0,0x2FF0,
				0x2FF0,0x2FF0,0x2FF0,0x2FF0,0x2FF0,	//40

				0x4FF0,0x4FF0,0x4FF0,0x4FF0,0x4FF0,
				0x4FF0,0x4FF0,0x4FF0,0x4FF0,0x4FF0,
				0x6FF0,0x6FF0,0x6FF0,0x6FF0,0x6FF0,
				0x6FF0,0x6FF0,0x6FF0,0x6FF0,0x6FF0,	//60

				0x6FF0,0x6FF0,0x6FF0,0x6FF0,0x6FF0,
				0x7FF0,0x7FF0,0x7FF0,0x7FF0,0x7FF0,
				0x7FF0,0x7FF0,0x7FF0,0x7FF0,0x7FF0,
				0x7FF0,0x7FF0,0x7FF0,0x7FF0,0x7FF0,	//80

				0x5FF0,0x5FF0,0xAFF0,0xAFF0,0xAFF0,
				0x4FF0,0x4FF0,0x4FF0,0x4FF0,0x4FF0,
				0x1FF0,0x1FF0,0x7FF0,0x2FF0,0x2FF0,
				0x1FF0,0x1FF0,0x1FF0,0x1FF0,0x1FF0,	//100

				0x6FF0,0x6FF0,0x6FF0,0x6FF0,0x6FF0,
				0x7FF0,0x7FF0,0x7FF0,0x7FF0,0x7FF0,
				0x7FF0,0x7FF0,0x7FF0,0x7FF0,0x7FF0,
				0x7FF0,0x7FF0,0x7FF0,0x7FF0,0x7FF0,	//120

				0xFFF0,0xFFF0,0xFFF0,0xFFF0,0xFFF0,
				0xFFF0,0xFFF0,0xFFF0,
		*/

	0x0F00, 0x5F00, 0xBF00, 0x9F00, 0x7F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,

	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,

	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x7F00, 0x5F00, 0x5F00,

	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,

	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,

	0x0F00, 0x0F00, 0x0F00, 0x0F00, 0x0F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,

	0x5F00, 0x5F00, 0x5F00, 0x5F00, 0x5F00,
	0x7F00, 0x0F00, 0xFF00,
};

/********************************************************

   LCD1608字符

*********************************************************/

uint8  asc2_1608[1520] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00,
	0x00, 0x48, 0x6C, 0x24, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0x7F, 0x12, 0x12, 0x12, 0x7F, 0x12, 0x12, 0x12, 0x00, 0x00,
	0x00, 0x00, 0x08, 0x1C, 0x2A, 0x2A, 0x0A, 0x0C, 0x18, 0x28, 0x28, 0x2A, 0x2A, 0x1C, 0x08, 0x08,
	0x00, 0x00, 0x00, 0x22, 0x25, 0x15, 0x15, 0x15, 0x2A, 0x58, 0x54, 0x54, 0x54, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0C, 0x12, 0x12, 0x12, 0x0A, 0x76, 0x25, 0x29, 0x11, 0x91, 0x6E, 0x00, 0x00,
	0x00, 0x06, 0x06, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x40, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0x40, 0x00,
	0x00, 0x02, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x6B, 0x1C, 0x1C, 0x6B, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x7F, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x04, 0x03,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x00,
	0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x0E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x20, 0x20, 0x10, 0x08, 0x04, 0x42, 0x7E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x20, 0x18, 0x20, 0x40, 0x40, 0x42, 0x22, 0x1C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x20, 0x30, 0x28, 0x24, 0x24, 0x22, 0x22, 0x7E, 0x20, 0x20, 0x78, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7E, 0x02, 0x02, 0x02, 0x1A, 0x26, 0x40, 0x40, 0x42, 0x22, 0x1C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x38, 0x24, 0x02, 0x02, 0x1A, 0x26, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7E, 0x22, 0x22, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x24, 0x18, 0x24, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x18, 0x24, 0x42, 0x42, 0x42, 0x64, 0x58, 0x40, 0x40, 0x24, 0x1C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x04,
	0x00, 0x00, 0x00, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x46, 0x40, 0x20, 0x10, 0x10, 0x00, 0x18, 0x18, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1C, 0x22, 0x5A, 0x55, 0x55, 0x55, 0x55, 0x2D, 0x42, 0x22, 0x1C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x08, 0x18, 0x14, 0x14, 0x24, 0x3C, 0x22, 0x42, 0x42, 0xE7, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0x22, 0x22, 0x22, 0x1E, 0x22, 0x42, 0x42, 0x42, 0x22, 0x1F, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x01, 0x01, 0x01, 0x01, 0x01, 0x42, 0x22, 0x1C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1F, 0x22, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x22, 0x1F, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3F, 0x42, 0x12, 0x12, 0x1E, 0x12, 0x12, 0x02, 0x42, 0x42, 0x3F, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3F, 0x42, 0x12, 0x12, 0x1E, 0x12, 0x12, 0x02, 0x02, 0x02, 0x07, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3C, 0x22, 0x22, 0x01, 0x01, 0x01, 0x71, 0x21, 0x22, 0x22, 0x1C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xE7, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x42, 0x42, 0xE7, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x11, 0x0F,
	0x00, 0x00, 0x00, 0x77, 0x22, 0x12, 0x0A, 0x0E, 0x0A, 0x12, 0x12, 0x22, 0x22, 0x77, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x42, 0x7F, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x77, 0x36, 0x36, 0x36, 0x36, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x6B, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xE3, 0x46, 0x46, 0x4A, 0x4A, 0x52, 0x52, 0x52, 0x62, 0x62, 0x47, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1C, 0x22, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x22, 0x1C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3F, 0x42, 0x42, 0x42, 0x42, 0x3E, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1C, 0x22, 0x41, 0x41, 0x41, 0x41, 0x41, 0x4D, 0x53, 0x32, 0x1C, 0x60, 0x00,
	0x00, 0x00, 0x00, 0x3F, 0x42, 0x42, 0x42, 0x3E, 0x12, 0x12, 0x22, 0x22, 0x42, 0xC7, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7C, 0x42, 0x42, 0x02, 0x04, 0x18, 0x20, 0x40, 0x42, 0x42, 0x3E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7F, 0x49, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xE7, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xE7, 0x42, 0x42, 0x22, 0x24, 0x24, 0x14, 0x14, 0x18, 0x08, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x6B, 0x49, 0x49, 0x49, 0x49, 0x55, 0x55, 0x36, 0x22, 0x22, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xE7, 0x42, 0x24, 0x24, 0x18, 0x18, 0x18, 0x24, 0x24, 0x42, 0xE7, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x77, 0x22, 0x22, 0x14, 0x14, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7E, 0x21, 0x20, 0x10, 0x10, 0x08, 0x04, 0x04, 0x42, 0x42, 0x3F, 0x00, 0x00,
	0x00, 0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x78, 0x00,
	0x00, 0x00, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x20, 0x40, 0x40,
	0x00, 0x1E, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1E, 0x00,
	0x00, 0x38, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
	0x00, 0x06, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x78, 0x44, 0x42, 0x42, 0xFC, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x1A, 0x26, 0x42, 0x42, 0x42, 0x26, 0x1A, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x02, 0x02, 0x02, 0x44, 0x38, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x60, 0x40, 0x40, 0x40, 0x78, 0x44, 0x42, 0x42, 0x42, 0x64, 0xD8, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x7E, 0x02, 0x02, 0x42, 0x3C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xF0, 0x88, 0x08, 0x08, 0x7E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x22, 0x22, 0x1C, 0x02, 0x3C, 0x42, 0x42, 0x3C,
	0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x3A, 0x46, 0x42, 0x42, 0x42, 0x42, 0xE7, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x22, 0x1E,
	0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x72, 0x12, 0x0A, 0x16, 0x12, 0x22, 0x77, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x92, 0x92, 0x92, 0x92, 0x92, 0xB7, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3B, 0x46, 0x42, 0x42, 0x42, 0x42, 0xE7, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x26, 0x42, 0x42, 0x42, 0x22, 0x1E, 0x02, 0x07,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x44, 0x42, 0x42, 0x42, 0x44, 0x78, 0x40, 0xE0,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x4C, 0x04, 0x04, 0x04, 0x04, 0x1F, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x42, 0x02, 0x3C, 0x40, 0x42, 0x3E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x08, 0x08, 0x08, 0x30, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x42, 0x42, 0x42, 0x42, 0x62, 0xDC, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE7, 0x42, 0x24, 0x24, 0x14, 0x08, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x49, 0x49, 0x55, 0x55, 0x22, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x24, 0x18, 0x18, 0x18, 0x24, 0x6E, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE7, 0x42, 0x24, 0x24, 0x14, 0x18, 0x08, 0x08, 0x07,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x22, 0x10, 0x08, 0x08, 0x44, 0x7E, 0x00, 0x00,
	0x00, 0xC0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x10, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xC0, 0x00,
	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
	0x00, 0x06, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x00,
	0x0C, 0x32, 0xC2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_GPIO_Init
*  功能说明:  OLED引脚初始化函数
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/
void myOLED_GPIO_Init(void)
{
	// i2c_init(I2C1, 40000);
	gpio_init(PTC10, GPO, 0);
	gpio_init(PTC11, GPO, 0);
	gpio_init(PTA19, GPO, 0);
	gpio_init(PTA24, GPO, 0);
	gpio_init(PTA25, GPO, 0);
}

/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_Init
*  功能说明:  OLED初始化
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/

void myOLED_Init(void)
{
	myOLED_GPIO_Init();
	myOLED_REST();

	myOLED_Write_REG(0xAE);	//关闭显示

	myOLED_Write_REG(0xD5);	//时钟分频因子，振荡频率
	myOLED_Write_REG(0x80);	//[3:0]分频因子;[7:4]振荡频率

	myOLED_Write_REG(0xA8);	//驱动格数
	myOLED_Write_REG(0x3F);	//1/64

	myOLED_Write_REG(0xD3);	//显示偏移
	myOLED_Write_REG(0x02);	//0

	myOLED_Write_REG(0x40);	//显示开始行[5:0]行数

	myOLED_Write_REG(0x8D);	//电荷泵
	myOLED_Write_REG(0x14);	//bit2开启/关闭

	myOLED_Write_REG(0x20);	//内存地址模式
	myOLED_Write_REG(0x02);	//[1:0]00列模式;01行模式;10默认页地址模式

	myOLED_Write_REG(0xA1);	//段重定义,左右扫描

	myOLED_Write_REG(0xC0);	//COM扫描方向bit3:0普通模式;1重定义模式

	myOLED_Write_REG(0xDA);	//COM硬件引脚
	myOLED_Write_REG(0x10);	//[5:4]配置

	myOLED_Write_REG(0x81);	//对比度
	myOLED_Write_REG(0xEF);	//

	myOLED_Write_REG(0xD9);	//预充电周期
	myOLED_Write_REG(0xF1);	//[3:0]PHASE 1[7:4]PHASE 2

	myOLED_Write_REG(0xDB);	//VCOMH电压倍率
	myOLED_Write_REG(0x30);	//

	myOLED_Write_REG(0xA4);	//全局显示bit0:1开启，0关闭
	myOLED_Write_REG(0xA6);	//显示方式bit0:1反向，0正常

	myOLED_Write_REG(0xAF);	//开启显示

	myOLED_Clear();

}
/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_Write_REG
*  功能说明:  OLED写寄存器函数
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/
void myOLED_Write_REG(uint8 COM)
{
	uint8 i = 0;
	gpio_set(OLED_DC , 0);	//0:指令
	for (i = 0; i < 8; i++)
	{
		if (COM & 0x80)
			gpio_set(OLED_DA, 1);
		else
			gpio_set(OLED_DA, 0);

		gpio_set(OLED_CK, 0);
		//		Delay_us(10);
		gpio_set(OLED_CK, 1);
		//		Delay_us(10);

		COM <<= 1;
	}
}
/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_Write_DAT
*  功能说明:  OLED写数据
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/
void myOLED_Write_DAT(uint8 DAT)
{
	uint8 i = 0;
	gpio_set(OLED_DC , 1);		//1数据
	for (i = 0; i < 8; i++)
	{
		if (DAT & 0x01)		//本来应该是高位在前，但是显示出来时倒立的，所以选择低位在前
			gpio_set(OLED_DA, 1);
		else
			gpio_set(OLED_DA, 0);

		gpio_set(OLED_CK, 0);
		//		Delay_us(10);
		gpio_set(OLED_CK, 1);
		//		Delay_us(10);

		DAT >>= 1;			//低位在前
	}
}
/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_REST
*  功能说明:  OLED复位
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/
void myOLED_REST(void)
{
	gpio_set(OLED_RST, 0);
	DELAY_MS(50);
	gpio_set(OLED_RST, 1);
}
/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_Clear
*  功能说明:  OLED清屏
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/
void myOLED_Clear(void)
{
	uint8 H = 0, L = 0;
	for (H = 0; H < 8; H++)
		for (L = 0; L < 128; L++)
			OLED_GRAM[H][L] = 0x00;
	myOLED_RefreshGRAM();
}
/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_RefreshGRAM
*  功能说明: 清屏
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/
void myOLED_RefreshGRAM(void)
{
	uint8 i = 0, n = 0;
	for (i = 0; i < 8; i++)
	{
		myOLED_Write_REG(0xB0 + i);	//
		myOLED_Write_REG(0x02);	  //
		myOLED_Write_REG(0x10);	  //
		for (n = 0; n < 128; n++)
			myOLED_Write_DAT(OLED_GRAM[i][n]);//
	}
}
/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_String
*  功能说明:  OLED显示字符串
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/
void myOLED_String(uint8 x, uint8 y, const char *P)
{
	uint8 i = 0;
	myOLED_Set_XY(x, y); //
	for (i = 0; i < strlen(P); i++)
	{
		myOLED_Char(P[i] - 32); //
	}

}
/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_Char
*  功能说明:  OLED显示字符
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/
void myOLED_Char(uint8 ch)
{
	uint8 Lie = 0;//没个字符有6列
	//字符在ASCII表中的位置

	for (Lie = 0; Lie < 6; Lie++) //分6列打印
	{
		myOLED_Write_DAT(ASCII_code[ch][Lie]);
	}
}
/*************************************************************************
*				我要过六级
*  函数名称:
*  功能说明:
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:  在XY位置画点X：0~7(页方式);Y:0~128(列方式)
*********************************************************/
void myOLED_XY_point(uint8 x, uint8 y, uint8 ch)
{
	myOLED_Set_XY( x, y);//
	myOLED_Write_DAT(ch);//
}
/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_Set_XY
*  功能说明:  OLED设置页码
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/
void myOLED_Set_XY(uint8 x, uint8 y)
{
	myOLED_Write_REG(0xB0 + x); //
	myOLED_Write_REG(((y & 0xF0) >> 4) | 0x10); //
	myOLED_Write_REG((y & 0x0F) | 0x01); //
}
/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_Dec
*  功能说明:  OLED显示5位数据
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:
*************************************************************************/
void myOLED_Dec(uint8 x, uint8 y, uint16 DEC)
{
	uint8 x5 = 0, x4 = 0, x3 = 0, x2 = 0, x1 = 0, row = 0;

	x5 = DEC / 10000 + 16; //
	x4 = DEC % 10000 / 1000 + 16; //
	x3 = DEC % 1000 / 100 + 16; //
	x2 = DEC % 100 / 10 + 16; //
	x1 = DEC % 10 + 16; //
	myOLED_Set_XY( x, y);//
	for (row = 0; row < 6; row++)
		myOLED_Write_DAT(ASCII_code[x5][row]);
	for (row = 0; row < 6; row++)
		myOLED_Write_DAT(ASCII_code[x4][row]);
	for (row = 0; row < 6; row++)
		myOLED_Write_DAT(ASCII_code[x3][row]);
	for (row = 0; row < 6; row++)
		myOLED_Write_DAT(ASCII_code[x2][row]);
	for (row = 0; row < 6; row++)
		myOLED_Write_DAT(ASCII_code[x1][row]);
}

/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_Dec
*  功能说明:  OLED显示5位数据
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:显示负数不能大于5位
*************************************************************************/
void myOLED_Dec4(uint8 x, uint8 y, int16 DEC)
{
	uint8 x5 = 0, x4 = 0, x3 = 0, x2 = 0, x1 = 0, row = 0;
	uint8 i = 0;

	if ( DEC < 0)
	{
		DEC = 0 - DEC;
		i = 1;
	}
	x5 = DEC / 10000 + 16; //
	x4 = DEC % 10000 / 1000 + 16; //
	x3 = DEC % 1000 / 100 + 16; //
	x2 = DEC % 100 / 10 + 16; //
	x1 = DEC % 10 + 16; //
	myOLED_Set_XY( x, y);//
	if (i == 0)
	{
		for (row = 0; row < 6; row++)
			myOLED_Write_DAT(ASCII_code[x5][row]);
	}
	else
	{
		myOLED_Char( 13 );       //"-"
	}
	for (row = 0; row < 6; row++)
		myOLED_Write_DAT(ASCII_code[x4][row]);
	for (row = 0; row < 6; row++)
		myOLED_Write_DAT(ASCII_code[x3][row]);
	for (row = 0; row < 6; row++)
		myOLED_Write_DAT(ASCII_code[x2][row]);
	for (row = 0; row < 6; row++)
		myOLED_Write_DAT(ASCII_code[x1][row]);
}

/*************************************************************************
*				我要过六级
*  函数名称:  myOLED_ADC_value
*  功能说明:  显示ADC的值
*  参数说明:
*
*  函数返回:
*  修改时间:2016-06-22
*  备注:  	显示ADC的值
		ADC的值为16位数据，分为8段，分别显示在0~7页
		128个数据刚好显示完，每一列只打印0x18，形成画线
*********************************************************/
void myOLED_ADC_value(uint16 * value)
{
	uint8 n = 0, PA = 0;
	uint16 temp = 0;
	myOLED_Set_XY(0, 0);
	for (n = 0; n < 128; n++)
	{
		temp = *(value + n); //

		if (temp > 0x00 && temp < 0x01F4)
			PA = 0;
		else if ((temp >= 0x01F5) && (temp <= 0x03F8))
			PA = 1;
		else if ((temp >= 0x03F9) && (temp <= 0x05DC))
			PA = 2;
		else if ((temp >= 0x05DD) && (temp <= 0x07D0))
			PA = 3;
		else if ((temp >= 0x07D1) && (temp <= 0x09C4))
			PA = 4;
		else if ((temp >= 0x09C5) && (temp <= 0x0BB8))
			PA = 5;
		else if ((temp >= 0x0BB9) && (temp <= 0x0DAC))
			PA = 6;
		else if ((temp >= 0x0DAD) && (temp <= 0x1004))
			PA = 7;

		myOLED_XY_point( PA, n, 0x18); //

	}
	myOLED_Clear();
}
/***********************************************************/


/*************************************************************************
*                             我要过六级
*  函数名称:myOLED_Decimals
*  功能说明:显示小数  格式 _._ _ _
*  参数说明:
*
*  函数返回:
*  修改时间:
*  备		 注:
*************************************************************************/
void myOLED_Decimals(uint8 x, uint8 y, float als)
{
	uint16 temp0 = 0, temS_P = 0, temS_I = 0 , temS_D = 0;
	uint16 temS_P6 = 0;

	if ( als < 0)
	{
		temS_P6 = (uint16)(-als * 100);
		temp0 = (uint16)(temS_P6 / 1000);
		temS_P = (uint16)(temS_P6 % 1000 / 100);
		temS_I = (uint16)(temS_P6 % 100 / 10);
		temS_D = (uint16)(temS_P6 % 10 / 1);


		myOLED_Set_XY( x, y);
		myOLED_Char( 13 );       //"-"
		myOLED_Char( temp0 + 16 );
		myOLED_Char( temS_P + 16 );
		myOLED_Char( 14 );
		myOLED_Char(temS_I + 16);
		myOLED_Char(temS_D + 16 );
	}
	else
	{
		temS_P6 = (uint16)(als * 100);
		temp0 = (uint16)(temS_P6 / 1000);
		temS_P = (uint16)(temS_P6 % 1000 / 100);
		temS_I = (uint16)(temS_P6 % 100 / 10);
		temS_D = (uint16)(temS_P6 % 10 / 1);


		myOLED_Set_XY( x, y);

		myOLED_Char( temp0 + 16 );
		myOLED_Char( temS_P + 16 );
		myOLED_Char( 14 );
		myOLED_Char(temS_I + 16);
		myOLED_Char(temS_D + 16 );
	}

}
/*************************************************************************
*                             我要过六级
*  函数名称:myOLED_
*  功能说明:
*  参数说明:
*
*  函数返回:
*  修改时间:
*  备		 注:
*************************************************************************/
void myOLED_CCDwave(CCD_Info * CCD1_info, CCD_Info * CCD2_info)
{

	uint8 i = 0, PA1 = 0, PA2 = 0;

	myOLED_Set_XY( 0, 0);

	for ( i = 0; i < 128; i++)
	{
		PA1 = CCD1_info->PixelBinary[i];
		PA2 = CCD2_info->PixelBinary[i];

		if (PA1 == 1)
		{
			myOLED_XY_point( 1, i, 0x02);
		}
		else
		{
			myOLED_XY_point( 1, i, 0x40);
		}
		if (PA2 == 1)
		{
			myOLED_XY_point( 2, i, 0x02);
		}
		else
		{
			myOLED_XY_point( 2, i, 0x40);
		}

	}

	// myOLED_XY_point( 1, CCD1_info->CentralLine[0], 7);
	// myOLED_XY_point( 2, CCD2_info->CentralLine[0], 7);

}







































/*************************************************************************
*                             我要过六级
*  函数名称:lcd_menu_display_init
*  功能说明: 显示菜单
*  参数说明:
*
*  函数返回:
*  修改时间:2016-7-1
*  备		 注:
*************************************************************************/
uint8 lcd_menu_display_init(menu * Menu)
{

	Menu->Ready_Go =  1;

	switch (Menu->choice_flag / 100)
	{
	case 0: if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}
		myOLED_String(4, 20, "Pass Cet6!!!!");
		break;
	case 1:   //Sudu1
	{
		if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "Binay"); myOLED_String(6, 50, "Zhi"); myOLED_Dec(6, 87, zhi);
		myOLED_String(4, 10, "SuDu1"); myOLED_String(5, 50, "Wan"); myOLED_Dec(5, 87, wan);
		myOLED_String(2, 10, "SuDu2"); myOLED_String(4, 50, "X-S"); myOLED_Dec(4, 87, x_s);
		// myOLED_String(3, 50, "Up"); myOLED_Dec(3, 87, Up);
		//myOLED_String(2, 50, "Dn"); myOLED_Dec(2, 87, Dn);
		// myOLED_String(1, 50, "LuZ"); myOLED_Dec(1, 87, LuZ);
		myOLED_String(3, 50, "SFlg"); myOLED_Dec(3, 87, stop_flag);
		myOLED_String(2, 50, "TunM"); myOLED_Dec(2, 87, Tune_Mode);
		myOLED_String(1, 50, "Diff"); myOLED_Decimals(1, 87, PidSpeedLeft.kd);
		switch (Menu->choice_flag % 100 / 10)
		{
		case 1:  //第二层	直道	速度
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(6, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(zhi, 450, 250);
				break;
			}
			break;
		case 2: //第二层	弯道	速度
			myOLED_String(5, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(5, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(wan, 400, 200);
				break;
			}
			break;
		case 3:  ////第二层	小S 速度
			myOLED_String(4, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(4, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(x_s, 400, 200);
				break;
			}
			break;
		case 4:  ////第二层
			myOLED_String(3, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(3, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				// MAP(Up, 400, 200);
				MAP(stop_flag, 1, 0);
				break;
			}
			break;
		case 5:  ////第二层	//小S最大变化率
			myOLED_String(2, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(2, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(Tune_Mode, 5, 1);
				break;
			}
			break;
		case 6:  ////第二层	//期望速度
			myOLED_String(1, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(1, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				// MAP(LuZ, 400, 200);
				MAP(PidSpeedLeft.kd , 1, -1);
				break;
			}
		default:
			break;
		}
	}
	break;  //end of sudu1
	case 2:   //Sudu2
	{
		if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "SuDu1"); myOLED_String(6, 50, "SExp"); myOLED_Dec(6, 87, (uint16)Speed_Expect);
		myOLED_String(4, 10, "SuDu2"); myOLED_String(5, 50, "Add3"); myOLED_Dec(5, 87, Add3);
		myOLED_String(2, 10, "Duoji");	myOLED_String(4, 50, "E_K"); myOLED_Dec(4, 87, E_K);
		myOLED_String(3, 50, "P"); myOLED_Decimals(3, 87, PidServo.kp);
		myOLED_String(2, 50, "I"); myOLED_Decimals(2, 87, PidServo.ki);
		myOLED_String(1, 50, "D"); myOLED_Decimals(1, 87, PidServo.kd);

		switch (Menu->choice_flag % 100 / 10)
		{
		case 1: //第二层	速度
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(6, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(Speed_Expect, 480, 280);
				break;
			}
			break;
		case 2: //第二层	Add3
			myOLED_String(5, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(5, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(Add3, 500, 300);
				break;
			}
			break;
		case 3:  ////第二层	E_K
			myOLED_String(4, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(4, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				// MAP(E_K, 450, 250);
				MAP(Chfile, 9, 0);
				break;
			}
			break;
		case 4:  ////第二层	P
			myOLED_String(3, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(3, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(PidServo.kp, 30, -10);
				break;
			}
			break;
		case 5:  ////第二层	P
			myOLED_String(2, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(2, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(PidServo.ki, 30, -10);
				break;
			}
			break;
		case 6:  ////第二层	D
			myOLED_String(1, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(1, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(PidServo.kd, 1, -1);
				break;
			}
			break;
		default:
			break;
		}
	}
	break;//end of sudu2
	case 3:  //Duoji
	{
		if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "Shudu2"); myOLED_String(6, 50, "S_P"); myOLED_Decimals(6, 87, S_P);
		myOLED_String(2, 10, "Duoji"); myOLED_String(5, 50, "S_I"); myOLED_Decimals(5, 87, S_I);
		myOLED_String(4, 10, "--V--"); myOLED_String(4, 50, "S_D"); myOLED_Decimals(4, 87, S_D);
		myOLED_String(3, 50, "S_PI"); myOLED_Decimals(3, 87, S_PI);
		myOLED_String(2, 50, "S_II"); myOLED_Decimals(2, 87, S_II);
		myOLED_String(1, 50, "S_DI"); myOLED_Decimals(1, 87, S_DI);

		switch (Menu->choice_flag % 100 / 10)
		{
		case 1: //第二层	P
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(6, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(S_P, 30, -30);
				break;
			}
			break;
		case 2:  ////第二层	I
			myOLED_String(5, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(5, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(S_I, 30, -30);
				break;
			}
			break;
		case 3:  ////第二层	D
			myOLED_String(4, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(4, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(S_D, 30, -30);
				break;
			}
			break;
		case 4:
			myOLED_String(3, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(3, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(S_PI, 30, -30);
				break;
			}
			break;
		case 5://H2
			myOLED_String(2, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(2, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(S_II, 30, -30);
				break;
			}
			break;
		case 6://H3
			myOLED_String(1, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(1, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(S_D, 30, -30);
				break;
			}
			break;
		default:
			break;
		}
	}
	break;  // end of duoji
	case 4:   //--V--
	{
		if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "Duoji"); myOLED_String(6, 50, "VP"); myOLED_Decimals(6, 87, VP);
		myOLED_String(4, 10, "--V--"); myOLED_String(5, 50, "VI"); myOLED_Decimals(5, 87, VI);
		myOLED_String(2, 10, "Time"); myOLED_String(4, 50, "VD"); myOLED_Decimals(4, 87, VD);
		myOLED_String(3, 50, "VPI"); myOLED_Decimals(3, 87, VPI);
		myOLED_String(2, 50, "VII"); myOLED_Decimals(2, 87, VII);
		myOLED_String(1, 50, "VDI"); myOLED_Decimals(1, 87, VDI);

		switch (Menu->choice_flag % 100 / 10)
		{
		case 0:
			break;
		case 1:  //第二层	VP
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(4, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(VP, 30, -30);
				break;
			}
			break;
		case 2: //第二层	VI
			myOLED_String(5, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(5, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(VI, 30, -30);
				break;
			}
			break;
		case 3: //第二层	VD
			myOLED_String(4, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(4, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(VD, 30, -30);
				break;
			}
			break;
		case 4: //第二层	VI
			myOLED_String(3, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(3, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(VPI, 30, -30);
				break;
			}
			break;
		case 5: //第二层	VI
			myOLED_String(2, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(2, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(VII, 30, -30);
				break;
			}
			break;
		case 6: //第二层	VI
			myOLED_String(1, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(1, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(VDI, 30, -30);
				break;
			}
			break;
		default:
			break;
		}
	}
	break; // end of --V--
	case 5:	  // Time
	{
		if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}

		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "--V--"); myOLED_String(6, 50, "D-T"); myOLED_Dec(6, 87, (uint16)D_T);
		myOLED_String(5, 50, "Po"); myOLED_Dec(5, 87, (uint16)Po_T);
		myOLED_String(4, 10, "Time"); /*myOLED_String(4, 50, "Ren"); myOLED_Dec(4, 87, (uint16)Ren_T);*/
		myOLED_String(2, 10, "juli"); myOLED_String(3, 50, "LuZ"); myOLED_Dec(3, 87, (uint16)LuZ_T);
		myOLED_String(2, 50, "S_T"); myOLED_Dec(2, 87, (uint16)S_T);

		switch (Menu->choice_flag % 100 / 10)
		{
		case 1:  //第二层	D_T
		{
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(6, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
				{
					D_T += 1;
					myOLED_String(6, 121, "+");

					Menu->add_sub = 0;
				}
				break;
				case 2:
				{
					if (D_T >= 1)
					{
						D_T -= 1;
					}
					myOLED_String(6, 121, "-");
					Menu->add_sub = 0;
				}
				break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 2:  //第二层	Po_T
		{
			myOLED_String(5, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(5, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
				{
					Po_T += 1;
					myOLED_String(5, 121, "+");

					Menu->add_sub = 0;
				}
				break;
				case 2:
				{
					if (Po_T >= 1)
					{
						Po_T -= 1;
					}

					myOLED_String(5, 121, "-");
					Menu->add_sub = 0;
				}
				break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 4:  //第二层	LuZ_T
		{
			myOLED_String(3, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(3, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
				{
					LuZ_T += 1;
					myOLED_String(3, 121, "+");

					Menu->add_sub = 0;
				}
				break;
				case 2:
				{
					if (LuZ_T >= 1)
					{
						LuZ_T -= 1;
					}

					myOLED_String(3, 121, "-");
					Menu->add_sub = 0;
				}
				break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 5:  //第二层	S_T
		{
			myOLED_String(2, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(2, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
				{
					S_T += 1;
					myOLED_String(2, 121, "+");

					Menu->add_sub = 0;
				}
				break;
				case 2:
				{
					if (S_T >= 1)
					{
						S_T -= 1;
					}

					myOLED_String(2, 121, "-");
					Menu->add_sub = 0;
				}
				break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}
	}
	break;// end of Time
	case 6:   // juli
	{
		if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}

		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "Time"); myOLED_String(6, 50, "jl_3"); myOLED_Dec(6, 87, jl_3);
		myOLED_String(4, 10, "juli"); /*myOLED_String(5, 50, "R-l"); myOLED_Dec(5, 87, R_l);*/
		myOLED_String(2, 10, "Other"); /*myOLED_String(4, 50, "R-L"); myOLED_Dec(4, 87, R_L);*/
		myOLED_String(3, 50, "Po_S1"); myOLED_Dec(3, 87, Po_S1);
		myOLED_String(2, 50, "Po_S2"); myOLED_Dec(2, 87, Po_S2);
		myOLED_String(1, 50, "Po_X"); myOLED_Dec(1, 87, Po_X);

		switch (Menu->choice_flag % 100 / 10)
		{
		case 1:  //第二层	jl-3
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(6, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (jl_3 < 1200)
					{
						jl_3 += 50;
					}
					myOLED_String(6, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (jl_3 >= 50)
					{
						jl_3 -= 50;
					}
					myOLED_String(6, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
				break;
			}
			break;
		// case 2: //第二层	L_2
		// 	myOLED_String(5, 40, "*");
		// 	switch (Menu->choice_flag % 10)
		// 	{
		// 	case 0:  // 第三层
		// 		break;
		// 	case 1:  //
		// 		myOLED_String(5, 77, "*");
		// 		switch (Menu->add_sub)
		// 		{
		// 		case 0:
		// 			break;
		// 		case 1:
		// 			if (R_l < 50)
		// 			{
		// 				R_l += 5;
		// 			}
		// 			myOLED_String(5, 121, "+");
		// 			Menu->add_sub = 0;
		// 			break;
		// 		case 2:
		// 			if (R_l >= 5)
		// 			{
		// 				R_l -= 5;
		// 			}
		// 			myOLED_String(5, 121, "-");
		// 			Menu->add_sub = 0;
		// 			break;
		// 		default:
		// 			break;
		// 		}
		// 		break;
		// 	}
		// 	break;
		// case 3: //R_L
		// 	myOLED_String(4, 40, "*");
		// 	switch (Menu->choice_flag % 10)
		// 	{
		// 	case 0:  // 第三层
		// 		break;
		// 	case 1:  //
		// 		myOLED_String(4, 77, "*");
		// 		switch (Menu->add_sub)
		// 		{
		// 		case 0:
		// 			break;
		// 		case 1:
		// 			if (R_L < 50)
		// 			{
		// 				R_L += 5;
		// 			}
		// 			myOLED_String(4, 121, "+");
		// 			Menu->add_sub = 0;
		// 			break;
		// 		case 2:
		// 			if (R_L >= 5)
		// 			{
		// 				R_L -= 5;
		// 			}
		// 			myOLED_String(4, 121, "-");
		// 			Menu->add_sub = 0;
		// 			break;
		// 		default:
		// 			break;
		// 		}
		// 		break;
		// 	}
		// 	break;
		case 4: //Po_S1
			myOLED_String(3, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(3, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (Po_S1 < 300)
					{
						Po_S1 += 5;
					}
					myOLED_String(3, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (Po_S1 >= 5)
					{
						Po_S1 -= 5;
					}
					myOLED_String(3, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
				break;
			}
			break;
		case 5: //Po_S2
			myOLED_String(2, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(2, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (Po_S2 < 300)
					{
						Po_S2 += 5;
					}
					myOLED_String(2, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (Po_S2 >= 5)
					{
						Po_S2 -= 5;
					}
					myOLED_String(2, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
				break;
			}
			break;
		case 6: //Po_X
			myOLED_String(1, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(1, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (Po_X < 300)
					{
						Po_X += 5;
					}
					myOLED_String(1, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (Po_X >= 5)
					{
						Po_X -= 5;
					}
					myOLED_String(1, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
				break;
			}
			break;
		default:
			break;
		}
	}
	break;
	case 7:	//Other
	{
		if (Menu->Clear)
		{
			myOLED_Clear();
			Menu->Clear = 0;
		}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "juli");	myOLED_String(6, 50, "R-tp"); myOLED_Dec(6, 87, R_tp);
		myOLED_String(4, 10, "Other"); myOLED_String(5, 50, "Ramp"); myOLED_Dec(5, 87, Ramp);
		myOLED_String(2, 10, "Go");	myOLED_String(4, 50, "Wu_x"); myOLED_Dec(4, 87, Wu_x);
		// myOLED_String(3, 50, "LSBR"); myOLED_Dec(3, 87, LSBR);
		myOLED_String(2, 50, "S_L"); myOLED_Dec(2, 87, S_L);
		myOLED_String(1, 50, "CCDL"); myOLED_Dec(1, 87, CCDL);
		switch (Menu->choice_flag % 100 / 10)
		{
		case 1: //第二层	R_tp
		{
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //R_tp
			{
				myOLED_String(6, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (R_tp < 2)
					{
						R_tp += 1;
					}
					myOLED_String(6, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (R_tp > 0)
					{
						R_tp -= 1;
					}
					myOLED_String(6, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 2:  //Ramp
		{
			myOLED_String(5, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //R_tp
			{
				myOLED_String(5, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (Ramp < 2000)
					{
						Ramp += 50;
					}
					myOLED_String(5, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (Ramp > 50)
					{
						Ramp -= 50;
					}
					myOLED_String(5, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 3:  //Wu_x
		{
			myOLED_String(4, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //R_tp
			{
				myOLED_String(4, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (Wu_x != TRUE)
					{
						Wu_x = TRUE;
					}
					myOLED_String(4, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (Wu_x != FALSE)
					{
						Wu_x = FALSE;
					}
					myOLED_String(4, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		// case 4:  //LSBR
		// {
		// 	myOLED_String(3, 40, "*");
		// 	switch (Menu->choice_flag % 10)
		// 	{
		// 	case 0:  // 第三层
		// 		break;
		// 	case 1:  //
		// 	{
		// 		myOLED_String(3, 77, "*");
		// 		switch (Menu->add_sub)
		// 		{
		// 		case 0:
		// 			break;
		// 		case 1:
		// 			if (0 == LSBR)
		// 			{
		// 				LSBR = 1;
		// 			}
		// 			myOLED_String(3, 121, "+");
		// 			Menu->add_sub = 0;
		// 			break;
		// 		case 2:
		// 			if (1 == LSBR)
		// 			{
		// 				LSBR = 0;
		// 			}
		// 			myOLED_String(3, 121, "-");
		// 			Menu->add_sub = 0;
		// 			break;
		// 		default:
		// 			break;
		// 		}
		// 	}
		// 	break;
		// 	default:
		// 		break;
		// 	}
		// }
		// break;
		case 5:  //S_L
		{
			myOLED_String(2, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(2, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (0 == S_L)
					{
						S_L = 1;
					}
					myOLED_String(2, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (1 == S_L)
					{
						S_L = 0;
					}
					myOLED_String(2, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 6:  //CCDL
		{
			myOLED_String(1, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(1, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (0 == CCDL)
					{
						CCDL = 1;
					}
					myOLED_String(1, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (1 == CCDL)
					{
						CCDL = 0;
					}
					myOLED_String(1, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}
	}
	break;
	case 8:  // Go
	{
		if (Menu->Clear)
		{
			myOLED_Clear();
			Menu->Clear = 0;
		}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "Other");
		myOLED_String(4, 10, "Go");
		myOLED_String(2, 10, "ChkCCD");
		myOLED_String(4, 50, "Ready--Go");
		switch (Menu->choice_flag % 100 / 10)
		{
		case 1:  //第二层
			myOLED_String(4, 40, "*");
			Menu->Ready_Go =  0;

			Car_mode = SelfDef;

			break;
		default:
			break;
		}
	}
	break;
	case 9:  // ChkCCD
	{
		if (Menu->Clear)
		{
			myOLED_Clear();
			Menu->Clear = 0;
		}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "Go");
		myOLED_String(4, 10, "ChkCCD");
		myOLED_String(2, 10, "ChkSL");
		myOLED_String(4, 50, "CheckCCD");

		switch (Menu->choice_flag % 100 / 10)
		{
		case 1:  //第二层
		{
			myOLED_String(4, 40, "*");
			Menu->Ready_Go =  0;

			Car_mode = CheckCCD;

		}
		break;
		default:
			break;
		}
	}
	break;
	case 10:  //ChkSL
	{
		if (Menu->Clear)
		{
			myOLED_Clear();
			Menu->Clear = 0;
		}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "ChkCCD");
		myOLED_String(4, 10, "ChkSL");
		myOLED_String(2, 10, "ChkRp");
		myOLED_String(4, 50, "CheckSL");

		switch (Menu->choice_flag % 100 / 10)
		{
		case 1:  //第二层
			myOLED_String(4, 40, "*");
			Menu->Ready_Go =  0;

			Car_mode = CheckSL;

			break;
		default:
			break;
		}
	}
	break;
	case 11: //ChkRp
	{
		if (Menu->Clear)
		{
			myOLED_Clear();
			Menu->Clear = 0;
		}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "ChkSL");
		myOLED_String(4, 10, "ChkRp");
		myOLED_String(2, 10, "ShiZ");
		myOLED_String(4, 50, "CheckRp");

		switch (Menu->choice_flag % 100 / 10)
		{
		case 1:  //第二层
			myOLED_String(4, 40, "*");
			Menu->Ready_Go =  0;

			Car_mode = CheckRamp;

			break;
		default:
			break;
		}
	}
	break;
#ifdef RemRoad_Control_Enable
	case 12://ShiZ
	{
		if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "ChkRp"); myOLED_String(6, 50, "S_Z1"); myOLED_Dec(6, 87, S_Z1);
		myOLED_String(4, 10, "ShiZ"); myOLED_String(5, 50, " SQ1"); myOLED_Dec(5, 87, SQ1);
		myOLED_String(2, 10, "RenZ"); myOLED_String(4, 50, " SG1"); myOLED_Dec(4, 87, SG1);
		myOLED_String(3, 50, "S_Z2"); myOLED_Dec(3, 87, S_Z2);
		myOLED_String(2, 50, " SQ2"); myOLED_Dec(2, 87, SQ2);
		myOLED_String(1, 50, " SG2"); myOLED_Dec(1, 87, SG2);

		switch (Menu->choice_flag % 100 / 10)
		{

		case 1:  //S_Z1
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(6, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (S_Z1 < 16)
					{
						S_Z1 += 1;
					}
					myOLED_String(6, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:

					if (S_Z1 > 1)
					{
						S_Z1 -= 1;
					}

					myOLED_String(6, 121, "-");
					Menu->add_sub = 0;
					break;
				}
				break;
			}
			break;
		case 2: //SQ1
		{
			myOLED_String(5, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(5, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (SQ1 < 800)
					{
						SQ1 += 50;
					}
					myOLED_String(5, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (SQ1 >= 50)
					{
						SQ1 -= 50;
					}
					myOLED_String(5, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 3: //SG1
		{
			myOLED_String(4, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(4, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (SG1 < 800)
					{
						SG1 += 50;
					}

					myOLED_String(4, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (SG1 >= 50)
					{
						SG1 -= 50;
					}
					myOLED_String(4, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 4:  //S_Z2
			myOLED_String(3, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(3, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (S_Z2 < 16)
					{
						S_Z2 += 1;
					}
					myOLED_String(3, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:

					if (S_Z2 > 1)
					{
						S_Z2 -= 1;
					}

					myOLED_String(3, 121, "-");
					Menu->add_sub = 0;
					break;
				}
				break;
			}
			break;
		case 5:  //SQ2
			myOLED_String(2, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(2, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (SQ2 < 800)
					{
						SQ2 += 50;
					}
					myOLED_String(2, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:

					if (SQ2 >= 50)
					{
						SQ2 -= 50;
					}

					myOLED_String(2, 121, "-");
					Menu->add_sub = 0;
					break;
				}
				break;
			}
			break;
		case 6:  //SG2
			myOLED_String(1, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(1, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (SG2 < 800)
					{
						SG2 += 50;
					}
					myOLED_String(1, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:

					if (SG2 >= 50)
					{
						SG2 -= 50;
					}

					myOLED_String(1, 121, "-");
					Menu->add_sub = 0;
					break;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	break;
	case 13://Po_D
	{
		if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "RenZ"); myOLED_String(6, 50, "P_D1"); myOLED_Dec(6, 87, P_D1);
		myOLED_String(4, 10, "Po_D"); myOLED_String(5, 50, " PQ1"); myOLED_Dec(5, 87, PQ1);
		myOLED_String(2, 10, "TeShu"); myOLED_String(4, 50, " PG1"); myOLED_Dec(4, 87, PG1);
		myOLED_String(3, 50, "P_D2"); myOLED_Dec(3, 87, P_D2);
		myOLED_String(2, 50, " PQ2"); myOLED_Dec(2, 87, PQ2);
		myOLED_String(1, 50, " PG2"); myOLED_Dec(1, 87, PG2);

		switch (Menu->choice_flag % 100 / 10)
		{

		case 1:  //P_D1
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(6, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (P_D1 < 2)
					{
						P_D1 += 1;
					}
					myOLED_String(6, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:

					if (P_D1 > 1)
					{
						P_D1 -= 1;
					}

					myOLED_String(6, 121, "-");
					Menu->add_sub = 0;
					break;
				}
				break;
			}
			break;
		case 2: //PQ1
		{
			myOLED_String(5, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(5, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (PQ1 < 800)
					{
						PQ1 += 50;
					}
					myOLED_String(5, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (PQ1 >= 50)
					{
						PQ1 -= 50;
					}
					myOLED_String(5, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 3: //PG1
		{
			myOLED_String(4, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(4, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (PG1 < 800)
					{
						PG1 += 50;
					}

					myOLED_String(4, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (PG1 >= 50)
					{
						PG1 -= 50;
					}
					myOLED_String(4, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 4:  //P_D2
			myOLED_String(3, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(3, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (P_D2 < 2)
					{
						P_D2 += 1;
					}
					myOLED_String(3, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:

					if (P_D2 > 1)
					{
						P_D2 -= 1;
					}

					myOLED_String(3, 121, "-");
					Menu->add_sub = 0;
					break;
				}
				break;
			}
			break;
		case 5:  //PQ2
			myOLED_String(2, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(2, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (PQ2 < 800)
					{
						PQ2 += 50;
					}
					myOLED_String(2, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:

					if (PQ2 >= 50)
					{
						PQ2 -= 50;
					}

					myOLED_String(2, 121, "-");
					Menu->add_sub = 0;
					break;
				}
				break;
			}
			break;
		case 6:  //PG2
			myOLED_String(1, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(1, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (PG2 < 800)
					{
						PG2 += 50;
					}
					myOLED_String(1, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:

					if (PG2 >= 50)
					{
						PG2 -= 50;
					}

					myOLED_String(1, 121, "-");
					Menu->add_sub = 0;
					break;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	break;
	case 14://TeShu 特殊模块功能设定
	{
		if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "Po_D"); myOLED_String(6, 50, "Jiyi"); myOLED_Dec(6, 87, Jiyi);
		myOLED_String(4, 10, "TeShu");/* myOLED_String(5, 50, "F_C"); myOLED_Dec(5, 87, F_C);*/
		myOLED_String(2, 10, "Binay"); myOLED_String(4, 50, "C_J"); myOLED_Dec(4, 87, C_J);
		myOLED_String(3, 50, "P_Y"); myOLED_Dec(3, 87, P_Y);
		// myOLED_String(2, 50, "RNum"); myOLED_Dec(2, 87, RNum);

		switch (Menu->choice_flag % 100 / 10)
		{
		case 1: //Jiyi
		{
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(6, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (1 != Jiyi)
					{
						Jiyi = 1;
					}
					myOLED_String(6, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:

					if (0 != Jiyi)
					{
						Jiyi = 0;
					}

					myOLED_String(6, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}

		}
		break;
		// case 2: //F_C
		// {
		// 	myOLED_String(5, 40, "*");
		// 	switch (Menu->choice_flag % 10)
		// 	{
		// 	case 0:  // 第三层
		// 		break;
		// 	case 1:  //
		// 	{
		// 		myOLED_String(5, 77, "*");
		// 		switch (Menu->add_sub)
		// 		{
		// 		case 0:
		// 			break;
		// 		case 1:
		// 			if (F_C < 100)
		// 			{
		// 				F_C += 2;
		// 			}
		// 			myOLED_String(5, 121, "+");
		// 			Menu->add_sub = 0;
		// 			break;
		// 		case 2:
		// 			if (F_C >= 2)
		// 			{
		// 				F_C -= 2;
		// 			}
		// 			myOLED_String(5, 121, "-");
		// 			Menu->add_sub = 0;
		// 			break;
		// 		default:
		// 			break;
		// 		}
		// 	}
		// 	break;
		// 	default:
		// 		break;
		// 	}
		// }
		// break;
		case 3: //C_J
		{
			myOLED_String(4, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(4, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (1 != C_J)
					{
						C_J = 1;
					}
					myOLED_String(4, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (0 != C_J)
					{
						C_J = 0;
					}
					myOLED_String(4, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		case 4: //P_Y
		{
			myOLED_String(3, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
			{
				myOLED_String(3, 77, "*");
				switch (Menu->add_sub)
				{
				case 0:
					break;
				case 1:
					if (P_Y < 5)
					{
						P_Y += 1;
					}
					myOLED_String(3, 121, "+");
					Menu->add_sub = 0;
					break;
				case 2:
					if (P_Y >= 1)
					{
						P_Y -= 1;
					}
					myOLED_String(3, 121, "-");
					Menu->add_sub = 0;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
		// case 5: //RNum
		// {
		// 	myOLED_String(2, 40, "*");
		// 	switch (Menu->choice_flag % 10)
		// 	{
		// 	case 0:  // 第三层
		// 		break;
		// 	case 1:  //
		// 	{
		// 		myOLED_String(2, 77, "*");
		// 		switch (Menu->add_sub)
		// 		{
		// 		case 0:
		// 			break;
		// 		case 1:
		// 			if (RNum < 3)
		// 			{
		// 				RNum += 1;
		// 			}
		// 			myOLED_String(2, 121, "+");
		// 			Menu->add_sub = 0;
		// 			break;
		// 		case 2:
		// 			if (RNum > 1)
		// 			{
		// 				RNum -= 1;
		// 			}
		// 			myOLED_String(2, 121, "-");
		// 			Menu->add_sub = 0;
		// 			break;
		// 		default:
		// 			break;
		// 		}
		// 	}
		// 	break;
		// 	default:
		// 		break;
		// 	}
		// }
		// break;
		default:
			break;
		}
	}
	break;
#endif
	case 15://Binay  CCD二值化设定
	{
		if (Menu->Clear) { myOLED_Clear(); Menu->Clear = 0;}
		myOLED_String(4, 1, "*");
		myOLED_String(6, 10, "TeShu"); myOLED_String(6, 50, "B_T"); myOLED_Dec(6, 87, B_T);
		myOLED_String(4, 10, "Binay"); myOLED_String(5, 50, "b_m"); myOLED_Dec(5, 87, b_m);
		myOLED_String(2, 10, "Shudu1"); myOLED_String(4, 50, "B_M"); myOLED_Dec(4, 87, B_M);
		myOLED_String(3, 50, "Sght"); myOLED_Dec(3, 87, Sght);

		switch (Menu->choice_flag % 100 / 10)
		{
		case 1: //B_T
			myOLED_String(6, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(6, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(B_T, 450, 250);
				break;
			}
			break;
		case 2: //b_m
			myOLED_String(5, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(5, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(b_m, 450, 250);
				break;
			}
			break;
		case 3: //B_M
			myOLED_String(4, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(4, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(B_T, 450, 250);
				break;
			}
			break;
		case 4: //Sght
			myOLED_String(3, 40, "*");
			switch (Menu->choice_flag % 10)
			{
			case 0:  // 第三层
				break;
			case 1:  //
				myOLED_String(3, 77, "*");
				Menu->Tun_Res = adc_once(ADC1_DM1, ADC_8bit);
				MYRANGE(Menu->Tun_Res, 140, 40);
				MAP(Sght, 450, 250);
				break;
			}
			break;
		default:
			break;
		}
	}
	break;
	default :
	{
		Menu->choice_flag = 0;
	}
	break;
	}

	return Menu->Ready_Go;
}





