/*
 * Team Id: SS#2364
 * Author List: Sagar Bharadwaj, Nagarakshith M S, Samarth Bonthala, Prajwal Bharadwaj
 * Filename: Caterpillar.h
 * Theme: eYRC 2017 Spotter Snake
 * Functions: forwardReset(), forward(), backward(), right(), left(), turnReset()
 * Global Variables: forwardParams, turnParams
*/

#include "globalState.h"
// The structure ForwardParams has a variable named forwardParams with parameters as defined within the structure
struct ForwardParams{
  int counter;
  float frequency;
  float lag;
  int amplitude;
  int amplitude_h;
  
} forwardParams;

// The structure TurnParams has a variable named turnParams with parameters as defined within the structure
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

/*
 * Function Name: forwardReset
 * Input: NONE
 * Output: Reset
 * Logic: All parameters of forwardParams are set to default value.
 * Example Call: forwardReset()
 */
void forwardReset(){
  forwardParams.counter = 0;
  forwardParams.frequency = 4;
  forwardParams.lag = PI/2;
  forwardParams.amplitude = 0;
  forwardParams.amplitude_h = 50;
  
}

/*
 * Function Name: forward
 * Input: NONE
 * Output: Snake locomotes in forward direction
 * Logic: A sinusoid(here it is cosine) of certain frequency is employed to actuate the even servos with each servo having a delay defined by the lag parameter 
 *        and swing is defined by amplitude_h.
 *        Odd servos are initialized with the pos<odd_servo_no>__init values.
 *        Due to delay in changing of the angles, the snake moves forward as there is increasing delay as servo number increases.
 * Example Call: forward()
 */
void forward(){
  if(state!='f')            // The forward parameters are reset only when there is a state transition from some other state to 'f' state
    forwardReset();
  // pos2_val: Takes in values 
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

  forwardParams.counter = (forwardParams.counter+8)%360;
  delay(100);
}

/*
 * Function Name: backward
 * Input: NONE
 * Output: Snake locomotes in reverse direction
 * Logic: A sinusoid(here it is cosine) of certain frequency is employed to actuate the even servos with each servo having a delay defined by the lag parameter 
 *        and swing is defined by amplitude_h which is different from value set for forward locomotion. (Calibrated based on trial and error)
 *        Odd servos are initialized with the pos<odd_servo_no>__init values.
 *        Due to delay in changing of the angles, the snake moves backward as there is increasing delay with decrease in servo number.
 * Example Call: backward()
 */
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

/*
 * Function Name: turnReset
 * Input: NONE
 * Output: Reset
 * Logic: All parameters of turnParams structure is set to default value, mainly counter value set to 0. The paramters and equations used define a serpenoid curve
 * Example Call: turnReset()
 */
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

/*
 * Function Name: right
 * Input: NONE
 * Output: Snake rotates to the right with respect to present position
 * Logic: A sinusoid(here it is sine) of certain frequency is employed to actuate the even servos with each servo having a different delay defined by 
 *       'b' parameter, lag2 parameter whose effect is increasing with increasing in servo number and swing is defined by amplitude_h.
 *        Odd servos are fed with an angle which is the modulation of two sinusoids and the lag is controlled by 'gamma' parameter and effect of beta 
 *        parameter is increasing with increase in servo number.
 * Example Call: right()
 */
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
  
  // counter parameter always runs from 0 to 355.
  turnParams.counter = (turnParams.counter+1)%360;

  delay(10);
}

/*
 * Function Name: left
 * Input: NONE
 * Output: Snake locomotes towards the left with respect to present position
 * Logic: A sinusoid(here it is sine) of certain frequency is employed to actuate the even servos with each servo having a different delay defined by 
 *       'b' parameter, lag2 parameter whose effect is increasing with increasing in servo number and swing is defined by amplitude_h.
 *        Odd servos are fed with an angle which is the modulation of two sinusoids with amplitude defined by alpha parameter and the lag is controlled 
 *        by 'gamma' parameter and effect of beta is increasing with increase in servo number.
 *        parameter is increasing with increase in servo number.
 * Example Call: left()
 */
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
  
  // counter parameter always runs from 0 to 355.
  turnParams.counter = (turnParams.counter+1)%360;

  delay(10);
}
