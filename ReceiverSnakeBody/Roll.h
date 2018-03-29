#include "globalState.h"

int rollDone = 0;

void rollLeft(){
  if(state!='l') rollDone = 0;
  
  if(!rollDone){
    servo3.detach();
    servo2.detach();
    servo4.detach();
    servo6.detach();
    
    servo8.write(0);
    delay(50);
    servo5.write(180);
    delay(50);
    servo7.write(0);
    delay(50);
    
    servo3.attach(3);
    servo2.attach(2);
    servo4.attach(4);
    servo6.attach(6);
  }
}

void rollRight(){
  if(state!='r') rollDone = 0;
  
  if(!rollDone){
    servo3.detach();
    servo2.detach();
    servo4.detach();
    servo6.detach();
    
    servo8.write(0);
    delay(50);
    servo5.write(0);
    delay(50);
    servo7.write(180);
    delay(50);

    servo3.attach(3);
    servo2.attach(2);
    servo4.attach(4);
    servo6.attach(6);
    
  }
}

