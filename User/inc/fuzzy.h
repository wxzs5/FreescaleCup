#ifndef  __FUZZY_H
#define  __FUZZY_H


#define 	NB		 0
#define 	NM		 1
#define 	NS		 2
#define 	ZO		 3
#define 	PS		 4
#define 	PM		 5
#define 	PB		 6

#define 	RNB		 -52
#define 	RNM		 -30
#define 	RNS		 -15
#define 	RZO		  0
#define 	RPS		        15
#define 	RPM		  30
#define 	RPB		        52

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
	float outSpeed;
	float outD;
	float ks;
	float kp;
	float kd;
	uint8 id;
} Fuzzysuite;

extern Fuzzysuite ServoFuzzy;
extern float FRP[7][7];
extern float FRD[7][7];
extern float FR_Speed[7][7];

void Fuzzy_Init();
void Fuzzy_Cal(Fuzzysuite *Fuzzy, float error, float ec);

#endif
