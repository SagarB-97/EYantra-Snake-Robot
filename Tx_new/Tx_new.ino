#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define OFF_STATE 0
#define ON_STATE 1

#define ON_ANALOG 1000
#define OFF_ANALOG 100

int A1_state = OFF_STATE;
int A2_state = OFF_STATE;
int A0_state = OFF_STATE;
int A3_state = OFF_STATE;

RF24 radio(7, 8);
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(A2,INPUT);
  pinMode(A1,INPUT);
  pinMode(A0,INPUT);
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void printAndSend(const char str[]){
    radio.write(str, 3);
    Serial.println(str);
}

void loop() {
  // Push Buttons
  int A3_val = analogRead(A3);
  int A2_val = analogRead(A2);
  int A1_val = analogRead(A1);
  int A0_val = analogRead(A0);
  int A5_val = analogRead(A5);

  /*Serial.print("A1 = ");
  printAndSend(A1_val);*/
  
  if(A0_state==OFF_STATE && A0_val>ON_ANALOG) A0_state = ON_STATE;
  if(A0_state==ON_STATE && A0_val<OFF_ANALOG){
    printAndSend("gt");
    A0_state=OFF_STATE;
  }

  if(A1_state==OFF_STATE && A1_val>ON_ANALOG) A1_state = ON_STATE;
  if(A1_state==ON_STATE && A1_val<OFF_ANALOG){
    printAndSend("nm");
    A1_state=OFF_STATE;
  }

  if(A2_state==OFF_STATE && A2_val>ON_ANALOG) A2_state = ON_STATE;
  if(A2_state==ON_STATE && A2_val<OFF_ANALOG){
    printAndSend("st");
    A2_state=OFF_STATE;
  }

  if(A3_state==OFF_STATE && A3_val>ON_ANALOG) A3_state = ON_STATE;
  if(A3_state==ON_STATE && A3_val<OFF_ANALOG){
    printAndSend("cs");
    A3_state=OFF_STATE;
  }
  //Serial.println(A5_val);
  //if(A5_val == 0){
  //  printAndSend("cs");
  //  delay(150);
  //}
    
  // Joystick
 
  int A6_val = analogRead(A6); //y-axis
  int A7_val = analogRead(A7); //x-axis

   // Serial.println(A6_val);
   // Serial.println(A7_val);
  if(A6_val<400 && (A7_val>300 || A7_val<700))
    printAndSend("b");
  else if(A6_val >600 && (A7_val>300 || A7_val<700))
          printAndSend("f");

   if(A7_val<400 && (A6_val>300 || A6_val<700))
       printAndSend("r");
   else if(A7_val >600 && (A6_val>300 || A6_val<700))
          printAndSend("l");
  
          
  
}

