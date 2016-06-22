#ifndef  __FUZZY_H
#define  __FUZZY_H


#define 	NB		 0
#define 	NM		 1
#define 	NS		 2
#define 	ZO		 3
#define 	PS		 4
#define 	PM		 5
#define 	PB		 6

#define 	RNB		 -64
#define 	RNM		 -40
#define 	RNS		 -20
#define 	RZO		    0
#define 	RPS		        20
#define 	RPM		  40
#define 	RPB		  64

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
