#include "include.h"

Fuzzysuite ServoFuzzy;

int8 FRP[7][7] = {{PB, PB, PM, PM, PS, ZO, ZO,},
  {PB, PB, PM, PS, PS, ZO, NS,},
  {PM, PM, PM, PS, ZO, NS, NS,},
  {PM, PM, PS, ZO, NS, NM, NM,},
  {PS, PS, ZO, NS, NS, NM, NM,},
  {PS, ZO, NS, NM, NM, NM, NB,},
  {ZO, ZO, NM, NM, NM, NB, NB,}
};

int8 FRD[7][7] = {{PS, NS, NB, NB, NB, NM, PS,},
  {PS, NS, NB, NM, NM, NS, ZO,},
  {ZO, NS, NM, NM, NS, NS, ZO,},
  {ZO, NS, NS, NS, NS, NS, ZO,},
  {ZO, ZO, ZO, ZO, ZO, ZO, ZO,},
  {PB, PS, PS, PS, PS, PS, PB,},
  {PB, PM, PM, PM, PS, PS, NB,}
};

void Fuzzy_Init()
{
  ServoFuzzy.errstart       = 0;
  ServoFuzzy.ecstart        = 0;
  ServoFuzzy.outP           = 0;
  ServoFuzzy.outI            = 0;
  ServoFuzzy.outD          = 0;
  ServoFuzzy.ki               = 0;
  ServoFuzzy.kp              = 0;
  ServoFuzzy.kd              = 0;
}


void Fuzzy_Cal(Fuzzysuite *Fuzzy, float error, float ec)
{
  if (error <= NM)
  {
    Fuzzy->errstart = NB;
    Fuzzy->errMeShip[0] = (RNM - error) / 24.0;
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else if (error <= NS)
  {
    Fuzzy->errstart = NM;
    Fuzzy->errMeShip[0] = (RNS - error) / 20.0;
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else if (error <= ZO)
  {
    Fuzzy->errstart = NS;
    Fuzzy->errMeShip[0] = (RZO - error) / 20.0;
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else if (error <= PS)
  {
    Fuzzy->errstart = ZO;
    Fuzzy->errMeShip[0] = (RPS - error) / 20.0;
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else if (error <= PM)
  {
    Fuzzy->errstart = PS;
    Fuzzy->errMeShip[0] = (RPM - error) / 20.0;
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
  else
  {
    Fuzzy->errstart = PM;
    Fuzzy->errMeShip[0] = (RPB - error) / 24.0;
    Fuzzy->errMeShip[1] = 1 - Fuzzy->errMeShip[0];
  }
//ec's membership value

  if (ec <= NM)
  {
    Fuzzy->ecstart = NB;
    Fuzzy->ecMeShip[0] = (RNM - ec) / 24.0;
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else if (ec <= NS)
  {
    Fuzzy->ecstart = NM;
    Fuzzy->ecMeShip[0] = (RNS - ec) / 20.0;
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else if (ec <= ZO)
  {
    Fuzzy->ecstart = NS;
    Fuzzy->ecMeShip[0] = (RZO - ec) / 20.0;
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else if (ec <= PS)
  {
    Fuzzy->ecstart = ZO;
    Fuzzy->ecMeShip[0] = (RPS - ec) / 20.0;
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else if (ec <= PM)
  {
    Fuzzy->ecstart = PS;
    Fuzzy->ecMeShip[0] = (RPM - ec) / 20.0;
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  else
  {
    Fuzzy->ecstart = PM;
    Fuzzy->ecMeShip[0] = (RPB - ec) / 24.0;
    Fuzzy->ecMeShip[1] = 1 - Fuzzy->ecMeShip[0];
  }
  Fuzzy->outP = Fuzzy->kp * ((Fuzzy->errMeShip[0] * FRP[Fuzzy->errstart][Fuzzy->ecstart] + Fuzzy->errMeShip[1] * FRP[Fuzzy->errstart + 1][Fuzzy->ecstart + 1]) - ZO);
  Fuzzy->outD = Fuzzy->kd * ((Fuzzy->errMeShip[0] * FRD[Fuzzy->errstart][Fuzzy->ecstart] + Fuzzy->errMeShip[1] * FRD[Fuzzy->errstart + 1][Fuzzy->ecstart + 1]) - ZO);
}

