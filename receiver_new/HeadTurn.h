#include "globalState.h"

struct HeadTurnParams {
  int degree7;
  int degree5;
  int motor;
} headTurnParams;

int cap(int a){
  a = min(a,180);
  a = max(a,0);
  return a;
}
void headTurnReset(){
  headTurnParams.degree7 = 0;
  headTurnParams.degree5 = 0;
  headTurnParams.motor = 7;
}
void headTurnLeft(){
  if(headTurnParams.motor==7) { headTurnParams.degree7=min(headTurnParams.degree7+1,180-pos7_init); servo7.write(cap(pos7_init + headTurnParams.degree7)); }
  if(headTurnParams.motor==5) { headTurnParams.degree5=max(headTurnParams.degree5-1,-pos5_init); servo5.write(cap(pos5_init + headTurnParams.degree5)); }
}
void headTurnRight(){
  if(headTurnParams.motor==7) { headTurnParams.degree7=max(headTurnParams.degree7-1,-pos7_init); servo7.write(cap(pos7_init + headTurnParams.degree7)); }
  if(headTurnParams.motor==5) { headTurnParams.degree5=min(headTurnParams.degree5 + 1,180-pos5_init); servo5.write(cap(pos5_init + headTurnParams.degree5)); }
}
