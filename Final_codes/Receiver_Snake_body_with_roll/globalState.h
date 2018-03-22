/*
 * Team Id: SS#2364
 * Author List: Sagar Bharadwaj, Nagarakshith M S, Samarth Bonthala, Prajwal Bharadwaj
 * Filename: globalState.h
 * Theme: eYRC 2017 Spotter Snake
 * Functions: NONE
 * Global Variables: NONE
*/

#ifndef GLOBALSTATE_H
#define GLOBALSTATE_H

//  The below variables are used to set the snake in equilibrium position which is in a straight line.
int pos2_init = 70;
int pos3_init = 110;
int pos4_init = 77;
int pos5_init = 95;
int pos6_init = 120;
int pos7_init = 50;
int pos8_init = 55 ;

//  state, gait[]: Holds initial state and when starting the run, the state and gait are default as these values
char state = 'i';
char gait[] = "cp";

// Multiple objects of Servo.h library are created, one each for each servo motor
Servo servo2,servo3,servo4,servo5,servo6,servo7,servo8;

#endif
