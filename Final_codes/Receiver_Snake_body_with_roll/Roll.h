#include "globalState.h"

int rollDone = 0;

void rollLeft(){
  if(state!='l') rollDone = 0;
  
  if(!rollDone){
    servo8.write(pos8_init - 50);
    delay(100);
    servo5.write(pos5_init  + 80);
    delay(100);
    servo7.write(pos7_init - 80);
    delay(100);
  }
}

void rollRight(){
  if(state!='r') rollDone = 0;
  
  if(!rollDone){
    servo8.write(pos8_init - 50);
    delay(100);
    servo5.write(pos5_init  - 80);
    delay(100);
    servo7.write(pos7_init + 80);
    delay(100);
  }
}

