#include"include.h"





void print_road(Car_State *state)
{
  if (Tune_Mode == 0)
  {
    if (state->now == In_Straight) printf("In_Straight->");
    else if (state->now == Into_Curva) printf("Into_Curva->");
    else if (state->now == In_Curva) printf("In_Curva->");
    else if (state->now == Into_Obstacle) printf("Into_Obstacle->");
    else if (state->now == In_Obstacle) printf("In_Obstacle->");
    else if (state->now == Out_Obstacle) printf("Out_Obstacle->");
    else if (state->now == Pre_Into_Obstacle) printf("Pre_Into_Obstacle->");
    else if (state->now == In_Crossing)printf("In_Crossing->");
  }
}
