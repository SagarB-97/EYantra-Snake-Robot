/*
 * Team Id: SS#2364
 * Author List: Sagar Bharadwaj, Nagarakshith M S, Samarth Bonthala, Prajwal Bharadwaj
 * Filename: HeadTurn.h
 * Theme: eYRC 2017 Spotter Snake
 * Functions: cap(int a), headTurnReset(), headTurnLeft(), headTurnRight()
 * Global Variables: headTurnParams
*/

#include "globalState.h"
// degree7, degree5: Angles to which the servo motors should turn when actuated.
// motor: The motor number which is activated at a particular instant of time. 
struct HeadTurnParams {
  int degree7;
  int degree5;
  int motor;
  int numberOfInputs;
} headTurnParams;

/*
 * Function Name: cap
 * Input: An integer variable.
 * Output: An integer which is in [0,180]
 * Logic: Computes the minimum of the input variable and 180 and assigns the minimum value to the same variable.
 *        It then computes maximum of the updated variable and 0 and assigns the maximum value to same variable and returns it.
 * Example Call: cap(x)
 */
int cap(int a){
  a = min(a,180);
  a = max(a,0);
  return a;
}
/*
 * Function Name: headTurnReset
 * Input: NONE
 * Output: Sets all the parameters in the headTurnParams to default values. 'motor' is set to 7 and degree5 and degree7 set as 0.
 * Logic: Assigning initial values. Reset to initial condition
 * Example Call: headTurnReset()
 */
 
void headTurnReset(){
  headTurnParams.degree7 = 0;
  headTurnParams.degree5 = 0;
  headTurnParams.motor = 7;
  headTurnParams.numberOfInputs = 0;
}

/*
 * Function Name: headTurnLeft
 * Input: NONE
 * Output: Enables to turn the head of the snake about a given servo towards the left
 * Logic: As the joystick is moved towards the left, the angle of the motor activated for rotation gets modified and hence the snake turns to the left 
 *        to match that angle, angle to which it can rotate being a maximum of 180 degrees.
 * Example Call: headTurnLeft()
 */
void headTurnLeft(){
  headTurnParams.numberOfInputs++;
  if(headTurnParams.numberOfInputs >= 3){
    headTurnParams.numberOfInputs = 0;
    if(headTurnParams.motor==7) { headTurnParams.degree7=min(headTurnParams.degree7+1,180-pos7_init); servo7.write(cap(pos7_init + headTurnParams.degree7)); }
    if(headTurnParams.motor==5) { headTurnParams.degree5=max(headTurnParams.degree5-1,-pos5_init); servo5.write(cap(pos5_init + headTurnParams.degree5)); }
  }
}

/*
 * Function Name: headTurnRight
 * Input: NONE
 * Output: Enables to turn the head of the snake about a given servo towards the right
 * Logic: As the joystick is moved towards the right, the angle of the motor activated for rotation gets modified and hence the snake turns to the right
 *        to match that angle, angle to which it can rotate being a maximum of 180 degrees.
 * Example Call: headTurnRight()
 */
void headTurnRight(){
  headTurnParams.numberOfInputs++;
  if(headTurnParams.numberOfInputs >= 3){
    headTurnParams.numberOfInputs = 0;
    if(headTurnParams.motor==7) { headTurnParams.degree7=max(headTurnParams.degree7-1,-pos7_init); servo7.write(cap(pos7_init + headTurnParams.degree7)); }
    if(headTurnParams.motor==5) { headTurnParams.degree5=min(headTurnParams.degree5 + 1,180-pos5_init); servo5.write(cap(pos5_init + headTurnParams.degree5)); }
  }
}
