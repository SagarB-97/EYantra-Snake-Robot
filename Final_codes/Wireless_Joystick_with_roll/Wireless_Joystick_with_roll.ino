/*
 * Team Id: SS#2364
 * Author List: Samarth Bonthala, Sagar Bharadwaj, Nagarakshith M S, Prajwal Bharadwaj
 * Filename: Wireless_Joystick.ino
 * Theme: eYRC 2017 Spotter Snake
 * Functions: setup(), printAndSend(const char str[]), loop()
 * Global Variables: A0_state, A1_state, A2_state, A3_state, stMarkTime, curTime, gtMarkTime, stButtonCount, gtButtonCount, address[6]
 * Libraries Included: SPI.h, nRF24L01.h, RF24.h
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// OFF_STATE, ON_STATE, ON_ANALOG, OFF_ANALOG are constants throughout the execution and are initialized with the values shown below. Global constants.
#define OFF_STATE 0
#define ON_STATE 1

#define ON_ANALOG 1000
#define OFF_ANALOG 100

// A0_state, A1_state, A2_state, A3_state: are intialized with the state values or thresholds to be compared with. Take on constant values
int A1_state = OFF_STATE;
int A2_state = OFF_STATE;
int A0_state = OFF_STATE;
int A3_state = OFF_STATE;
long int cscount=1;

// stMarkTime, curTime, gtMarkTime: Keeps track of time from the start/powerting of the arduino nano after the respective push button is pressed.Keeps counting until arduino is reset.
long stMarkTime=0, curTime=0, gtMarkTime=0;
// stButtonCount, gtButtonCount: Keeps a count of number of times the respective button 'st' or 'gt' is pressed to decide functionality. Takes on integer values
int stButtonCount = 0;
int gtButtonCount = 0;

RF24 radio(7, 8);
// address[6]: Assigns a particular/unique address to decide transmission link and avoid collisions in RF. Array of size 6 with initial index 0 to (length-1).
const byte address[6] = "00111";

/*
 * Function Name: setup
 * Input: NONE
 * Output: Executes the statements once and only once when the file is run
 * Logic: Initial setup of parameters based on functionality required, declaration of pins as input or output, etc
 * Example Call: setup()
 */
void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);//RED
  pinMode(3,OUTPUT);//BLUE
  pinMode(4,OUTPUT);//GREEN
  pinMode(5,OUTPUT);//WHITE
  pinMode(A2,INPUT);
  pinMode(A1,INPUT);
  pinMode(A0,INPUT);
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(5,HIGH);
  // Execute initial functions of the radio object 
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

/*
 * Function Name: printAndSend
 * Input: const char a[]
 * Output: Transmits using nrf24l01 module and prints to serial monitor
 * Logic: write attribute of radio object in RF24 library is called and also printed to the serial monitor
 * Example Call: printAndSend("cp")
 */
void printAndSend(const char str[]){
  radio.write(str, 3);
  Serial.println(str);
}

/*
 * Function Name: loop
 * Input: NONE
 * Output: Default arduino function which re-runs the statements within it indefinitely.
 * Logic: The operations that can be controlled from this function are:
 *        1. If joystick is moved towards north, the transmitter sends a 'f'.
 *        2. If joystick is moved towards south, the transmitter sends a 'b'.
 *        3. If joystick is moved towards east, the transmitter sends a 'r'.
 *        4. If joystick is moved towards west, the transmitter sends a 'l'.
 *        
 *        The push buttons offer the following functionality:
 *        1. Push button connected to A0 is responsible for Gait Transistion. Has three options options, Caterpillar("cp"), Sidewinding("sw") and rampClimber("rc")
 *        2. Push button connected to A1 is responsible for Head Turning(only one motor at a time). Has two options, turn first motor or turn third motor. "ht" is sent.
 *        3. Push button connected to A2 is responsible for Start/Stop. If pressed once or twice, START is enabled and if pressed more than twice, then it STOPS. "st" or "so" is sent.
 *        4. Push button connected to A3 is responsible for enabling/disabling Colour Sensor. "cs" is transmitted.
 * Example Call: loop()
 */
void loop() {
  curTime = millis();
  // Push Buttons
  // A0_val, A1_val, A2_val, A3_val: Read values from push buttons which are connected to push buttons. Takes values from 0 to 1023.
  int A2_val = analogRead(A2);
  int A1_val = analogRead(A1);
  int A0_val = analogRead(A0);
  int A3_val = analogRead(A3);

  // The signal should only be sent when the push button is released and not when it is pressed. Thus the following logic is used. It is self explanatory. 
  
  // For gait transition and start and stop signals, time interval of 0.5s and 3s respectively is taken to count the number of times a button is pushed.
  
  if(A0_state==OFF_STATE && A0_val>ON_ANALOG) A0_state = ON_STATE;
  if(A0_state==ON_STATE && A0_val<OFF_ANALOG){
    if(gtButtonCount==0) { gtMarkTime = millis(); }
    gtButtonCount++;
    A0_state=OFF_STATE;
  }

  if(A1_state==OFF_STATE && A1_val>ON_ANALOG) A1_state = ON_STATE;
  if(A1_state==ON_STATE && A1_val<OFF_ANALOG){
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(3,HIGH);    
    printAndSend("ht");
    A1_state=OFF_STATE;
  }

  if(A2_state==OFF_STATE && A2_val>ON_ANALOG) A2_state = ON_STATE;
  if(A2_state==ON_STATE && A2_val<OFF_ANALOG){
    if(stButtonCount==0) { stMarkTime = millis(); }
    stButtonCount++;
    A2_state=OFF_STATE;
  }

  if(curTime-stMarkTime >=700){
    if(stButtonCount && stButtonCount>=3){
      printAndSend("so");
    }
    else if(stButtonCount && stButtonCount<3){
      printAndSend("st");
    }
    stButtonCount = 0;
    stMarkTime = curTime;
  }

  if(curTime-gtMarkTime >=1000){
    if(gtButtonCount && gtButtonCount==2){
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(2,LOW);
      printAndSend("sw");
    }
    else if(gtButtonCount && gtButtonCount==1){
      digitalWrite(2,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(4,LOW);
      printAndSend("cp");
    }
    else if(gtButtonCount && gtButtonCount==3){
      digitalWrite(2,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(3,LOW);
      printAndSend("rc");
    }
    else if(gtButtonCount && gtButtonCount==4){
      digitalWrite(2,LOW);
      digitalWrite(4,LOW);
      digitalWrite(3,HIGH);
      printAndSend("ro");
    }
    gtButtonCount = 0;
    gtMarkTime = curTime;
  }

  if(A3_state==OFF_STATE && A3_val>ON_ANALOG) A3_state = ON_STATE;
  if(A3_state==ON_STATE && A3_val<OFF_ANALOG){
    printAndSend("cs");
    cscount++;
    if(cscount%2==0) digitalWrite(5,LOW);
    else digitalWrite(5,HIGH);
    A3_state=OFF_STATE;
    delay(100);
  }
  
  // Joystick
  // A6_val, A7_val: Read analog values from the joystick which is nothing but two way potentiometer. Gives values in range 0 to 1023 along both the axes.
  
  int A6_val = analogRead(A6); //y-axis
  int A7_val = analogRead(A7); //x-axis
  
  // Suitable thresholds are found to give effective and minimal human error during joystick operation.
  
  if(A6_val<200 && (A7_val>300 || A7_val<700))
    printAndSend("b");
  else if(A6_val >800 && (A7_val>300 || A7_val<700))
          printAndSend("f");

   if(A7_val<150 && (A6_val>300 || A6_val<700))
       printAndSend("r");
   else if(A7_val >800 && (A6_val>300 || A6_val<700))
          printAndSend("l");
  
}

