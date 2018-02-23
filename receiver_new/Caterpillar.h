#include "globalState.h"

struct ForwardParams{
  int counter;
  int frequency;
  float lag;
  int amplitude;
  int amplitude_h;
} forwardParams;

struct TurnParams{
  int counter;
  int frequency1;
  int frequency2;
  float lag1;
  float lag2;
  float a;
  float b;
  float c;
  float n;
  float beta;
  float alpha;
  float gamma;
  float amplitude_h;
} turnParams;

void forwardReset(){
  forwardParams.counter = 0;
  forwardParams.frequency = 4;
  forwardParams.lag = PI/2;
  forwardParams.amplitude = 0;
  forwardParams.amplitude_h = 40;
}
void forward(){
  if(state!='f')
    forwardReset();

  int pos2_val = pos2_init + floor(forwardParams.amplitude_h*cos(forwardParams.frequency*forwardParams.counter*PI/180));
  servo2.write(pos2_val);

  servo3.write(pos3_init);

  int pos4_val = pos4_init - floor(forwardParams.amplitude_h*cos(forwardParams.frequency*forwardParams.counter*PI/180 - 1*forwardParams.lag)); 
  servo4.write(pos4_val);

  servo5.write(pos5_init);

  int pos6_val = pos6_init + floor(forwardParams.amplitude_h*cos(forwardParams.frequency*forwardParams.counter*PI/180 - 2*forwardParams.lag));
  servo6.write(pos6_val);

  servo7.write(pos7_init);

  int pos8_val = pos8_init - floor(forwardParams.amplitude_h*cos(forwardParams.frequency*forwardParams.counter*PI/180 - 3*forwardParams.lag));
  servo8.write(pos8_val);

  forwardParams.counter = (forwardParams.counter+10)%360;
  delay(100);
}
void backward(){
  if(state!='b'){
    forwardReset();
    forwardParams.amplitude_h = 35;
  }

  int pos8_val = pos8_init + floor(forwardParams.amplitude_h*cos(forwardParams.frequency*forwardParams.counter*PI/180));
  servo8.write(pos8_val);

  servo3.write(pos3_init);

  int pos6_val = pos6_init - floor(forwardParams.amplitude_h*cos(forwardParams.frequency*forwardParams.counter*PI/180 - 1*forwardParams.lag)); 
  servo6.write(pos6_val);

  servo5.write(pos5_init);

  int pos4_val = pos4_init + floor(forwardParams.amplitude_h*cos(forwardParams.frequency*forwardParams.counter*PI/180 - 2*forwardParams.lag));
  servo4.write(pos4_val);

  servo7.write(pos7_init);

  int pos2_val = pos2_init - floor(forwardParams.amplitude_h*cos(forwardParams.frequency*forwardParams.counter*PI/180 - 3*forwardParams.lag));
  servo2.write(pos2_val);

  forwardParams.counter = (forwardParams.counter+10)%360;
  delay(100);
}

void turnReset(){
  turnParams.counter = 0;
  turnParams.frequency1 = 2;
  turnParams.frequency2 = 2;
  turnParams.a = 60;
  turnParams.b = 2*PI;
  turnParams.c = 0;
  turnParams.n = 3;
  turnParams.lag1 = 240*PI/180;
  turnParams.lag2 = 180*PI/180;
  turnParams.beta = turnParams.b/turnParams.n;
  turnParams.alpha = abs(turnParams.a*sin(turnParams.beta/2));
  turnParams.gamma = -turnParams.c/turnParams.n;
  turnParams.amplitude_h = 30;
}

void right(){
  if(state!='r') turnReset();
    
  int pos2_val = pos2_init + floor(-(turnParams.amplitude_h*sin(turnParams.frequency2*turnParams.counter*PI/180 + turnParams.b + 0*turnParams.lag2)));
  servo2.write(pos2_val);
  
  int pos3_val = pos3_init + floor(-turnParams.alpha*sin(turnParams.frequency1*turnParams.counter*PI/180 + 0*turnParams.beta)+turnParams.gamma);
  servo3.write(pos3_val); 

  int pos4_val = pos4_init + floor((turnParams.amplitude_h*sin(turnParams.frequency2*turnParams.counter*PI/180 + turnParams.b + 1*turnParams.lag2)));
  servo4.write(pos4_val);

   int pos5_val = pos5_init + floor(-(turnParams.alpha*sin(turnParams.frequency1*turnParams.counter*PI/180 + 1*turnParams.beta))+turnParams.gamma);
  servo5.write(pos5_val);

  int pos6_val = pos6_init + floor(-(turnParams.amplitude_h*sin(turnParams.frequency2*turnParams.counter*PI/180 + turnParams.b + 2*turnParams.lag2)));
  servo6.write(pos6_val);

   int pos7_val = pos7_init + floor(turnParams.alpha*sin(turnParams.frequency1*turnParams.counter*PI/180 + 2*turnParams.beta)+turnParams.gamma);
  servo7.write(pos7_val);

  int pos8_val = pos8_init + floor(turnParams.amplitude_h*sin(turnParams.frequency2*turnParams.counter*PI/180 + turnParams.b + 3*turnParams.lag2));
  servo8.write(pos8_val);

  turnParams.counter = (turnParams.counter+1)%360;

  delay(10);
}
void left(){
  if(state!='l') turnReset();
  
  int pos2_val = pos2_init + floor(-(turnParams.amplitude_h*sin(turnParams.frequency2*turnParams.counter*PI/180 + turnParams.b + 0*turnParams.lag2)));
  servo2.write(pos2_val);
  
  int pos3_val = pos3_init + floor(turnParams.alpha*sin(turnParams.frequency1*turnParams.counter*PI/180 + 0*turnParams.beta)+turnParams.gamma);
  servo3.write(pos3_val); 

  int pos4_val = pos4_init + floor((turnParams.amplitude_h*sin(turnParams.frequency2*turnParams.counter*PI/180 + turnParams.b + 1*turnParams.lag2)));
  servo4.write(pos4_val);

   int pos5_val = pos5_init + floor((turnParams.alpha*sin(turnParams.frequency1*turnParams.counter*PI/180 + 1*turnParams.beta))+turnParams.gamma);
  servo5.write(pos5_val);

  int pos6_val = pos6_init + floor(-(turnParams.amplitude_h*sin(turnParams.frequency2*turnParams.counter*PI/180 + turnParams.b + 2*turnParams.lag2)));
  servo6.write(pos6_val);

   int pos7_val = pos7_init + floor(-turnParams.alpha*sin(turnParams.frequency1*turnParams.counter*PI/180 + 2*turnParams.beta)+turnParams.gamma);
  servo7.write(pos7_val);

  int pos8_val = pos8_init + floor(turnParams.amplitude_h*sin(turnParams.frequency2*turnParams.counter*PI/180 + turnParams.b + 3*turnParams.lag2));
  servo8.write(pos8_val);

  turnParams.counter = (turnParams.counter+1)%360;

  delay(10);
}
