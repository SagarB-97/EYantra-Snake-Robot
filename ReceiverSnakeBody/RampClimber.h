#include "globalState.h"

struct RampClimberParams{
  int counter;
  int frequency;
  float lag;
  int amplitude;
  int amplitude_h;
  float phase;
} rampClimberParams;

void rampClimberReset(){
  rampClimberParams.counter = 0;
  rampClimberParams.frequency = 4;
  rampClimberParams.lag = PI/2;
  rampClimberParams.amplitude = 0;
  rampClimberParams.amplitude_h = 40;
  rampClimberParams.phase = PI/2;
}

void rampClimberLeft(){
  if(state!='l') rampClimberReset();
  
  int pos2_val = pos2_init + floor((rampClimberParams.amplitude_h- 20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180-3*rampClimberParams.lag+rampClimberParams.phase));
  servo2.write(pos2_val);

  int pos3_val = pos3_init + floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180- 2*rampClimberParams.lag));
  servo3.write(pos3_val);

  int pos4_val = pos4_init - floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 2*rampClimberParams.lag + rampClimberParams.phase)); 
  servo4.write(pos4_val);

  int pos5_val = pos5_init - floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 1*rampClimberParams.lag)); 
  servo5.write(pos5_val);

  int pos6_val = pos6_init + floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 1*rampClimberParams.lag  + rampClimberParams.phase));
  servo6.write(pos6_val);

  int pos7_val = pos7_init + floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 0*rampClimberParams.lag));
  servo7.write(pos7_val);

  int pos8_val = pos8_init - floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 0*rampClimberParams.lag + rampClimberParams.phase));
  servo8.write(pos8_val);

  rampClimberParams.counter = (rampClimberParams.counter+10) % 360;
  delay(100);
}

void rampClimberRight(){
  if(state!='r') rampClimberReset();
  
  int pos2_val = pos2_init + floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180- 3*rampClimberParams.lag));
  servo2.write(pos2_val);

  int pos3_val = pos3_init + floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 2*rampClimberParams.lag +rampClimberParams.phase));
  servo3.write(pos3_val);

  int pos4_val = pos4_init - floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 2*rampClimberParams.lag)); 
  servo4.write(pos4_val);

  int pos5_val = pos5_init - floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 1*rampClimberParams.lag + rampClimberParams.phase)); 
  servo5.write(pos5_val);

  int pos6_val = pos6_init + floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 1*rampClimberParams.lag));
  servo6.write(pos6_val);

  int pos7_val = pos7_init + floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 0*rampClimberParams.lag + rampClimberParams.phase));
  servo7.write(pos7_val);

  int pos8_val = pos8_init - floor((rampClimberParams.amplitude_h -20)*cos(rampClimberParams.frequency*rampClimberParams.counter*PI/180 - 0*rampClimberParams.lag));
  servo8.write(pos8_val);

  rampClimberParams.counter = (rampClimberParams.counter+10) % 360;
  
  delay(100);
}
