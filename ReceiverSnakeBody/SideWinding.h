/*
 * Team Id: SS#2364
 * Author List: Sagar Bharadwaj, Nagarakshith M S, Samarth Bonthala, Prajwal Bharadwaj
 * Filename: SideWinding.h
 * Theme: eYRC 2017 Spotter Snake
 * Functions: sideWindingLeft(), sideWindingRight()
 * Global Variables: NONE
*/

#include "globalState.h"

// The structure SideWindingParams has a variable named sideWindingParams with parameters as defined within the structure. The paramters and equations used define a serpenoid curve
struct SideWindingParams{
  int counter;
  int frequency;
  float lag;
  int amplitude;
  int amplitude_h;
  float phase;
  
  // i - Normal Motion
  // n - neg' Motion
  char currentMotion; 

  int numberOfNormalCycles;
  int numberOfNegCycles;

  int maxNormalCycles_l;
  int maxNegCycles_l;

  int maxNormalCycles_r;
  int maxNegCycles_r;
} sideWindingParams;

/*
 * Function Name: sideWindingReset
 * Input: NONE
 * Output: Reset
 * Logic: All parameters of sideWindingParams structure is set to default value, mainly counter value set to 0.
 * Example Call: sideWindingReset()
 */
void sideWindingReset(){
  sideWindingParams.counter = 0;
  sideWindingParams.frequency = 4;
  sideWindingParams.lag = PI/2;
  sideWindingParams.amplitude = 0;
  sideWindingParams.amplitude_h = 40;
  sideWindingParams.phase = PI/2;
  sideWindingParams.currentMotion = 'i';
  
  sideWindingParams.numberOfNormalCycles = 0;
  sideWindingParams.numberOfNegCycles = 0;

  sideWindingParams.maxNormalCycles_l = 2;
  sideWindingParams.maxNegCycles_l = 1;

  
  sideWindingParams.maxNormalCycles_r = 4;
  sideWindingParams.maxNegCycles_r = 1;
}

/*
 * Function Name: sideWindingLeft
 * Input: NONE
 * Output: Snake locomotes to the left while exhibiting sidewinding gait
 * Logic: A sinusoid(here it is sine) of certain frequency is employed to actuate the even servos with each servo having a different delay defined by 
 *       'b' parameter, lag2 parameter whose effect is increasing with increasing in servo number and swing is defined by amplitude_h.
 *        Odd servos are fed with an angle which is the modulation of two sinusoids and the lag is controlled by 'gamma' parameter and effect of beta 
 *        parameter is increasing with increase in servo number.
 * Example Call: sideWindingLeft()
 */

void sideWindingNormalLeft() {
  
  int pos2_val = pos2_init + floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180-0*sideWindingParams.lag+sideWindingParams.phase));
  servo2.write(pos2_val);

  int pos3_val = pos3_init + floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180- 0*sideWindingParams.lag));
  servo3.write(pos3_val);

  int pos4_val = pos4_init - floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 1*sideWindingParams.lag + sideWindingParams.phase)); 
  servo4.write(pos4_val);

  int pos5_val = pos5_init - floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 1*sideWindingParams.lag)); 
  servo5.write(pos5_val);

  int pos6_val = pos6_init + floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 2*sideWindingParams.lag  + sideWindingParams.phase));
  servo6.write(pos6_val);

  int pos7_val = pos7_init + floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 2*sideWindingParams.lag));
  servo7.write(pos7_val);

  int pos8_val = pos8_init - floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 3*sideWindingParams.lag + sideWindingParams.phase));
  servo8.write(pos8_val);

  sideWindingParams.counter = (sideWindingParams.counter+10);
  
  if(sideWindingParams.counter == 70 || sideWindingParams.counter == 140 ||sideWindingParams.counter == 220 || sideWindingParams.counter == 290 || sideWindingParams.counter == 360) {
    sideWindingParams.numberOfNormalCycles++;
  }
  if(sideWindingParams.numberOfNormalCycles >= sideWindingParams.maxNormalCycles_l){
    sideWindingReset();
    sideWindingParams.currentMotion = 'n';
  }

  sideWindingParams.counter = sideWindingParams.counter % 360;
  
  delay(100);
}

void sideWindingNegLeft(){
  
  int pos2_val = pos2_init + floor((sideWindingParams.amplitude_h- 20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180-3*sideWindingParams.lag+sideWindingParams.phase));
  servo2.write(pos2_val);

  int pos3_val = pos3_init + floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180- 2*sideWindingParams.lag));
  servo3.write(pos3_val);

  int pos4_val = pos4_init - floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 2*sideWindingParams.lag + sideWindingParams.phase)); 
  servo4.write(pos4_val);

  int pos5_val = pos5_init - floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 1*sideWindingParams.lag)); 
  servo5.write(pos5_val);

  int pos6_val = pos6_init + floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 1*sideWindingParams.lag  + sideWindingParams.phase));
  servo6.write(pos6_val);

  int pos7_val = pos7_init + floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 0*sideWindingParams.lag));
  servo7.write(pos7_val);

  int pos8_val = pos8_init - floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 0*sideWindingParams.lag + sideWindingParams.phase));
  servo8.write(pos8_val);


  sideWindingParams.counter = (sideWindingParams.counter+10);
  
  if(sideWindingParams.counter == 70 || sideWindingParams.counter == 140 || sideWindingParams.counter == 220 || sideWindingParams.counter == 290 || sideWindingParams.counter == 360){
    sideWindingParams.numberOfNegCycles++;
  }
  if(sideWindingParams.numberOfNegCycles >= sideWindingParams.maxNegCycles_l){
    sideWindingReset();
    sideWindingParams.currentMotion = 'i';
  }

  sideWindingParams.counter = sideWindingParams.counter % 360;
  
  delay(100);
}

void sideWindingLeft(){
  if(state!='l') sideWindingReset();

  if(sideWindingParams.currentMotion == 'i') sideWindingNormalLeft();
  else if(sideWindingParams.currentMotion == 'n') sideWindingNegLeft();
}
/*
 * Function Name: sideWindingRight
 * Input: NONE
 * Output: Snake locomotes to the right while exhibiting sidewinding gait
 * Logic: A sinusoid(here it is sine) of certain frequency is employed to actuate the even servos with each servo having a different delay defined by 
 *       'b' parameter, lag2 parameter whose effect is increasing with increasing in servo number and swing is defined by amplitude_h.
 *        Odd servos are fed with an angle which is the modulation of two sinusoids and the lag is controlled by 'gamma' parameter and effect of beta 
 *        parameter is increasing with increase in servo number.
 * Example Call: sideWindingRight()
 */
void sideWindingNormalRight(){

  int pos2_val = pos2_init + floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180- 0*sideWindingParams.lag));
  servo2.write(pos2_val);

  int pos3_val = pos3_init + floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 + sideWindingParams.phase));
  servo3.write(pos3_val);

  int pos4_val = pos4_init - floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 1*sideWindingParams.lag)); 
  servo4.write(pos4_val);

  int pos5_val = pos5_init - floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 1*sideWindingParams.lag + sideWindingParams.phase)); 
  servo5.write(pos5_val);

  int pos6_val = pos6_init + floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 2*sideWindingParams.lag));
  servo6.write(pos6_val);

  int pos7_val = pos7_init + floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 2*sideWindingParams.lag + sideWindingParams.phase));
  servo7.write(pos7_val);

  int pos8_val = pos8_init - floor(sideWindingParams.amplitude_h*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 3*sideWindingParams.lag));
  servo8.write(pos8_val);

  sideWindingParams.counter = (sideWindingParams.counter+10);
  
  if(sideWindingParams.counter == 60 ||sideWindingParams.counter == 120 || sideWindingParams.counter == 180 ||sideWindingParams.counter == 240 || sideWindingParams.counter == 300 || sideWindingParams.counter == 360){
    sideWindingParams.numberOfNormalCycles++;
    
  }
  if(sideWindingParams.numberOfNormalCycles >= sideWindingParams.maxNormalCycles_r){
    sideWindingReset();
    sideWindingParams.currentMotion = 'n';
  }

  sideWindingParams.counter = sideWindingParams.counter % 360;
  
  delay(100);
}
void sideWindingNegRight(){
  
  int pos2_val = pos2_init + floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180- 3*sideWindingParams.lag));
  servo2.write(pos2_val);

  int pos3_val = pos3_init + floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 2*sideWindingParams.lag +sideWindingParams.phase));
  servo3.write(pos3_val);

  int pos4_val = pos4_init - floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 2*sideWindingParams.lag)); 
  servo4.write(pos4_val);

  int pos5_val = pos5_init - floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 1*sideWindingParams.lag + sideWindingParams.phase)); 
  servo5.write(pos5_val);

  int pos6_val = pos6_init + floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 1*sideWindingParams.lag));
  servo6.write(pos6_val);

  int pos7_val = pos7_init + floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 0*sideWindingParams.lag + sideWindingParams.phase));
  servo7.write(pos7_val);

  int pos8_val = pos8_init - floor((sideWindingParams.amplitude_h -20)*cos(sideWindingParams.frequency*sideWindingParams.counter*PI/180 - 0*sideWindingParams.lag));
  servo8.write(pos8_val);

  sideWindingParams.counter = (sideWindingParams.counter+10);
  
  if(sideWindingParams.counter == 70 || sideWindingParams.counter == 140 ||sideWindingParams.counter == 220 || sideWindingParams.counter == 290 || sideWindingParams.counter == 360){
    sideWindingParams.numberOfNegCycles++;
  }
  if(sideWindingParams.numberOfNegCycles >= sideWindingParams.maxNegCycles_r){
    sideWindingReset();
    sideWindingParams.currentMotion = 'i';
  }

  sideWindingParams.counter = sideWindingParams.counter % 360;
  
  delay(100);
}

void sideWindingRight() {
  if(state!='r') sideWindingReset();

  if(sideWindingParams.currentMotion == 'i') sideWindingNormalRight();
  else if(sideWindingParams.currentMotion == 'n') sideWindingNegRight();
}
