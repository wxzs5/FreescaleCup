#include "include.h"


Fuzzysuite ServoFuzzy;


//左上角和右下角抑制往错误的方向调整 所以d 应该很大
//左下角和右上角抑制超调，D应该适当大一点
// float FRD[7][7] = {
//   { 6,   5,   3,  -3,   2,   2,   2,},
//   { 5,   3,   6,  -2,   2,  -2,  -6,},
//   { 3,  -2,   2,  -1,  -2,  -2,  -6,},
//   { 5,   3,   1,   0,   1,   3,   5,},
//   { -6,  -6,  -6,  -1,  -6,  -6,   3,},
//   { 6,  -2,  -2,  -2,  -2,   3,   5,},
//   { 2,   2,   2,  -3,   3,   5,   6,}
// };


float FRD[7][7] = {
  {    4,     4,       3,      -2,      -2,      2.5,     3,},
  {    4,     3,       2,      -1,      -2,     -2,    -0.5,},
  {    3,     2,       3,       2,        0,     -2,     -3,},
  {    3,     3,       3,       3,        3,      3,       3,},
  {   -3,    -2,      0,       2,        3,      2,       3,},
  { -0.5,   -2,     -2,       -1,       2,      3,       4,},
  {    3,     2.5,   -2,       -2,       3,      4,       4,}
};


float FRP[7][7] = {
  { 4,     3.5,     3,       2,       0,     -2,    -3,},
  { 3.5,     3,     3,       1,       -1,    -3,    -3,},
  { 3,      2,      -1,     - 3,       -3,   -1,     -1,},
  { 0,     -2,      -3,     -3.5,     -3,   -2,      0,},
  { -1,   -1,     -3,      -3,       -1,     2,      3,},
  { -3,   -3,     -1,       1,        3,      3,     3.5,},
  { -3,   -2,      0,       2,        3,    3.5,      4,}
};



float FR_Speed[7][7] = {
  { -15,    0,    -30,     -10,     5,      0,     15,},
  { -10,   -5,     -10,     10,      5,     -2,    10,},
  {  0,   -2,   -10,     5,       5,    -2,    5,},
  {  5,    5,      5,     30,      5,     3,     5,},
  {  5,    5,      5,      5,    -10,   -2,    0,},
  {  10,  -2,    5,     10,       -10,      -5,   -10,},
  {  15,  0,     5,      -10,      -30,    0,    -15,}
};


void Fuzzy_Init()
{
  ServoFuzzy.errstart       = 0;
  ServoFuzzy.ecstart        = 0;
  ServoFuzzy.outP           = 0;
  ServoFuzzy.outSpeed       = 0;
  ServoFuzzy.outD           = 0;
  ServoFuzzy.ks               = 0;
  ServoFuzzy.kp              = 0;
  ServoFuzzy.kd              = 0;
  ServoFuzzy.id              = 0;
}

void Fuzzy_Cal(Fuzzysuite *Fuzzy, float error, float ec)
{
  if (error <= RNB)
  {
    Fuzzy->errstart = NB;
    Fuzzy->errMeShip[0] = 1;
    Fuzzy->errMeShip[1] = 0;
  }
  else if (error <= RNM)
  {
    Fuzzy->errstart = NB;
    Fuzzy->errMeShip[0] = (RNM - error) / ( (RNM) - (RNB) ) ;   // -34  - -51
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else if (error <= RNS)
  {
    Fuzzy->errstart = NM;
    Fuzzy->errMeShip[0] = (RNS - error) / ( (RNS) - (RNM) ); //-17 -   -34
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else if (error <= RZO)
  {
    Fuzzy->errstart = NS;
    Fuzzy->errMeShip[0] = (RZO - error) / ( (RZO) - (RNS) ); //0 - -17
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else if (error <= RPS)
  {
    Fuzzy->errstart = ZO;
    Fuzzy->errMeShip[0] = (RPS - error) / ( (RPS) - (RZO) ); //17 -0
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else if (error <= RPM)
  {
    Fuzzy->errstart = PS;
    Fuzzy->errMeShip[0] = (RPM - error) / ( (RPM) - (RPS) ); //34-17
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else if (error <= RPB)
  {
    Fuzzy->errstart = PM;
    Fuzzy->errMeShip[0] = (RPB - error) / ( (RPB) - (RPM) ); //51 - 34
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else
  {
    Fuzzy->errstart = PM;
    Fuzzy->errMeShip[0] = 0;
    Fuzzy->errMeShip[1] = 1;

  }
//ec's membership value
  if (ec < EC_RNB)
  {
    Fuzzy->ecstart = NB;
    Fuzzy->ecMeShip[0] = 1;
    Fuzzy->ecMeShip[1] = 0;
  }
  else if (ec <= EC_RNM)
  {
    Fuzzy->ecstart = NB;
    Fuzzy->ecMeShip[0] = (EC_RNM - ec) / ( (EC_RNM) - (EC_RNB) );
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else if (ec <= EC_RNS)
  {
    Fuzzy->ecstart = NM;
    Fuzzy->ecMeShip[0] = (EC_RNS - ec) / ( (EC_RNS) - (EC_RNM));
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else if (ec <= EC_RZO)
  {
    Fuzzy->ecstart = NS;
    Fuzzy->ecMeShip[0] = (EC_RZO - ec) / ( (EC_RZO) - (EC_RNS) );
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else if (ec <= EC_RPS)
  {
    Fuzzy->ecstart = ZO;
    Fuzzy->ecMeShip[0] = (EC_RPS - ec) / ( (EC_RPS) - (EC_RZO) );
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else if (ec <= EC_RPM)
  {
    Fuzzy->ecstart = PS;
    Fuzzy->ecMeShip[0] = (EC_RPM - ec) / ( (EC_RPM) - (EC_RPS) );
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else if (ec <= EC_RPB)
  {
    Fuzzy->ecstart = PM;
    Fuzzy->ecMeShip[0] = (EC_RPB - ec) / ( (EC_RPB) - (EC_RPM) );
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else
  {
    Fuzzy->ecstart = PM;
    Fuzzy->ecMeShip[0] = 0;
    Fuzzy->ecMeShip[1] = 1;
  }
  /*
    int8 num = FRP[Fuzzy->errstart][Fuzzy->ecstart];
    KP_Fuzzy[num] += Fuzzy->errMeShip[0] * Fuzzy->ecMeShip[0];

    num = FRP[Fuzzy->errstart][Fuzzy->ecstart+1];
    KP_Fuzzy[num] +=Fuzzy->errMeShip[0] * Fuzzy->ecMeShip[1];

    num = FRP[]
  */

  Fuzzy->outP = Fuzzy->kp * (Fuzzy->errMeShip[0] * Fuzzy->ecMeShip[0] * FRP[Fuzzy->errstart][Fuzzy->ecstart]
                             + Fuzzy->errMeShip[1] * Fuzzy->ecMeShip[1] * FRP[Fuzzy->errstart + 1][Fuzzy->ecstart + 1]
                             + Fuzzy->errMeShip[0] * Fuzzy->ecMeShip[1] * FRP[Fuzzy->errstart][Fuzzy->ecstart + 1]
                             + Fuzzy->errMeShip[1] * Fuzzy->ecMeShip[0] * FRP[Fuzzy->errstart + 1][Fuzzy->ecstart]
                            );
  Fuzzy->outD = Fuzzy->kd * (Fuzzy->errMeShip[0] * Fuzzy->ecMeShip[0] * FRD[Fuzzy->errstart][Fuzzy->ecstart]
                             + Fuzzy->errMeShip[1] * Fuzzy->ecMeShip[1] * FRD[Fuzzy->errstart + 1][Fuzzy->ecstart + 1]
                             + Fuzzy->errMeShip[0] * Fuzzy->ecMeShip[1] * FRD[Fuzzy->errstart][Fuzzy->ecstart + 1]
                             + Fuzzy->errMeShip[1] * Fuzzy->ecMeShip[0] * FRD[Fuzzy->errstart + 1][Fuzzy->ecstart]
                            );
  Fuzzy->outSpeed = Fuzzy->ks * (Fuzzy->errMeShip[0] * Fuzzy->ecMeShip[0] * FR_Speed[Fuzzy->errstart][Fuzzy->ecstart]
                                 + Fuzzy->errMeShip[1] * Fuzzy->ecMeShip[1] * FR_Speed[Fuzzy->errstart + 1][Fuzzy->ecstart + 1]
                                 + Fuzzy->errMeShip[0] * Fuzzy->ecMeShip[1] * FR_Speed[Fuzzy->errstart][Fuzzy->ecstart + 1]
                                 + Fuzzy->errMeShip[1] * Fuzzy->ecMeShip[0] * FR_Speed[Fuzzy->errstart + 1][Fuzzy->ecstart]
                                );
}



Fuzzysuite ServoFuzzy;



