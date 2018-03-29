/*
 * Team Id: SS#2364
 * Author List: Sagar Bharadwaj, Nagarakshith M S, Samarth Bonthala, Prajwal Bharadwaj
 * Filename: ReceiverSnakeBody.ino
 * Theme: eYRC 2017 Spotter Snake
 * Functions: setup(), equilibrium(), loop()
 * Global Variables: address[6]
 * Libraries Included: SPI.h, nRF24L01.h, RF24.h, math.h, Servo.h
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <math.h>

#include "Caterpillar.h"
#include "SideWinding.h"
#include "HeadTurn.h"
#include "RampClimber.h"
#include "Roll.h"

RF24 radio(9,10);

// address[6]: Assigns a particular/unique address to decide transmission link and avoid collisions in RF. Array of size 6 with initial index 0 to (length-1).
const byte address[6] = "00111";

/*
 * Function Name: equilibrium
 * Input: NONE
 * Output: Sets the servos to the equilibrium position (snake becomes straight) defined by pos2_init, pos3_init,.....,pos8_init.
 * Logic: write attribute of servo object in Servo.h library will be executed with the initial angles of servos as inputs to the call.
 *        The values pos2_init, pos3_init,......, pos8_init are defined in globalState.h
 *        
 * Example Call: equilibrium()
 */
void equilibrium(){
  servo2.write(pos2_init);
  servo3.write(pos3_init);
  servo4.write(pos4_init);
  servo5.write(pos5_init);
  servo6.write(pos6_init);
  servo7.write(pos7_init);
  servo8.write(pos8_init);
}

/*
 * Function Name: setup
 * Input: NONE
 * Output: Executes the statements once and only once when the file is run
 * Logic: Initial setup of parameters based on functionality required, declaration of pins as input or output, initializing servos, etc
 * Example Call: setup()
 */
void setup() {
  // Serial.begin(9600) sets the baud rate as 9600 for serial communication. The baud at this point and serial monitor should match for efficient reception.
  Serial.begin(9600);
  // Execute initial functions of the radio object 
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  // Attach attribute is executed to set up the servos (Arduino Nano recognises servos connected to it through this execution)
  // Servo 2 is closest to the tail. Servo 8 is closest to the head. Servos 3,5,7 are in the same plane and are perpendicular to the Servos 2,4,6,8
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
  servo7.attach(7);
  servo8.attach(8);
  // Equilibrium function is called and headturn motor is set to number 5 initially.
  equilibrium();
  // One of the motors is rotated so that the snake fits in the start zone of the arena
  //servo5.write(pos5_init+50);
  // Parameter of the HeadTurn.h library is initialized as 5. (motor = 5)
  headTurnParams.motor = 5;
}

/*
 * Function Name: loop
 * Input: NONE
 * Output: Default arduino function which re-runs the statements within it indefinitely.
 * Logic:  By default the snake is in HeadTurn Mode. To go to Gait Mode, gt push button is pressed which takes it to different gait configurations based on number of button presses.
 *         When joystick is moved in a particular direction, the snake moves in that direction with the mode as selected.
 *         In HeadTurn mode, the snake head can turn to the left or right about a selected servo (number 5 or number 7) based on number of times button is pressed.
 *         A state machine is employed as once a particular mode is entered, it remains stable in that state until a state change is requested for.
 *         Default position of the snake robot is equilibrium position.
 *         
 * Example Call: loop()
 */
void loop() {
  // available function of radio object is called and it returns true if there is data in the buffer to be read
  if (radio.available()) {
    // inp[5]: Stores the characters received due to transmission from transmitter
    char inp[5];
    radio.read(inp, sizeof(inp));  //The transmitted data is read once the channel/medium is sensed for activity by previous command
   
    
    // Conditions for snake movement based on the push button activations and joystick control
    if(strcmp(inp,"f")==0){
      if(strcmp(gait,"cp")==0 || strcmp(gait,"sw")==0 || strcmp(gait,"rc")==0) forward(); //gait: A character array defined in globalState.h which is initially in caterpillar. Can take "cp", "sw" or "ht".
      state = 'f'; //state: A character variable defined in globalState.h which holds 'i' initially and is modified based on the state the snake is present in at a given instant of time.
    }
    else if(strcmp(inp,"b")==0){
      if(strcmp(gait,"cp")==0 || strcmp(gait,"sw")==0 || strcmp(gait,"rc")==0) backward();
      state = 'b';
    }
    else if(strcmp(inp,"l")==0){
      if(strcmp(gait,"cp")==0) left();
      else if(strcmp(gait,"sw")==0) sideWindingLeft();
      else if(strcmp(gait,"ht")==0) headTurnLeft();
      else if(strcmp(gait,"rc")==0) rampClimberLeft();
      else if(strcmp(gait,"ro")==0) rollLeft();
      state = 'l';
    }
    else if(strcmp(inp,"r")==0){
      if(strcmp(gait,"cp")==0) right();
      else if(strcmp(gait,"sw")==0) sideWindingRight();
      else if(strcmp(gait,"ht")==0) headTurnRight();
      else if(strcmp(gait,"rc")==0) rampClimberRight();
      else if(strcmp(gait,"ro")==0) rollRight();
      state = 'r';
    }    

    // During transition from one gait to another or from head turn mode to a gait, the snake comes back to equilibrium and the state and gait variables are modified accordingly.
    else if(strcmp(inp,"cp")==0){
      equilibrium();
      strcpy(gait,inp);
      state = 's';
    }
    else if(strcmp(inp,"sw")==0){
      equilibrium();
      strcpy(gait,inp);
      state = 's';
    }
    else if(strcmp(inp,"rc")==0){
      equilibrium();
      strcpy(gait,inp);
      state = 's';
    }
    else if(strcmp(inp,"ro")==0){
      equilibrium();
      strcpy(gait,inp);
      state = 's';
    }
    else if(strcmp(inp,"ht")==0){
      if(strcmp(gait,"ht")==0) { 
        if(headTurnParams.motor==7) headTurnParams.motor = 5;       // Based on number of button presses on ht button the servo about which the snake has to turn is decided
        else if(headTurnParams.motor==5) headTurnParams.motor = 7;  // The activated motor swaps between 7 and 5 on successive presses
      }
      else { equilibrium(); headTurnReset(); }
      strcpy(gait,inp);
      state = 's';
    }

    // These functionalities are programmed to be received by the 'Rodent detection' arduino
    else if(strcmp(inp,"cs")==0) {
      Serial.println('x');
    }
    else if(strcmp(inp,"st")==0) {
      Serial.println('y');
    }
    else if(strcmp(inp,"so")==0) {
      Serial.println('z');
    }
  }

  //  The snake is in equilibrium/straight position when the transmitter is idle
  else{
    if(strcmp(gait,"ht")!=0) equilibrium();
    state='s';
  }
}
