#ifndef  __FUZZY_H
#define  __FUZZY_H


#define 	NB		 0
#define 	NM		 1
#define 	NS		 2
#define 	ZO		 3
#define 	PS		 4
#define 	PM		 5
#define 	PB		 6

#define 	RNB		 -51
#define 	RNM		 -34
#define 	RNS		 -17
#define 	RZO		  0
#define 	RPS		  17
#define 	RPM		  34
#define 	RPB		  51

#define 	EC_RNB		 -12
#define 	EC_RNM		 -8
#define 	EC_RNS		 -4
#define 	EC_RZO		  0
#define 	EC_RPS		        4
#define 	EC_RPM		  8
#define 	EC_RPB		        12

typedef struct
{
	float errMeShip[2];
	int8 errstart;
	float ecMeShip[2];
	int8 ecstart;
	float outP;
	float outI;
	float outD;
	float ki;
	float kp;
	float kd;
} Fuzzysuite;

extern Fuzzysuite ServoFuzzy;

void Fuzzy_Init();
void Fuzzy_Cal(Fuzzysuite *Fuzzy, float error, float ec);

#endif
