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

long stMarkTime=0, curTime=0, gtMarkTime=0;
int stButtonCount = 0;
int gtButtonCount = 0;

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
  curTime = millis();
  // Push Buttons
  int A2_val = analogRead(A2);
  int A1_val = analogRead(A1);
  int A0_val = analogRead(A0);
  int A3_val = analogRead(A3);


  /*Serial.print("A1 = ");
  printAndSend(A1_val);*/
  
  if(A0_state==OFF_STATE && A0_val>ON_ANALOG) A0_state = ON_STATE;
  if(A0_state==ON_STATE && A0_val<OFF_ANALOG){
    if(gtButtonCount==0) { gtMarkTime = millis(); }
    gtButtonCount++;
    A0_state=OFF_STATE;
  }

  if(A1_state==OFF_STATE && A1_val>ON_ANALOG) A1_state = ON_STATE;
  if(A1_state==ON_STATE && A1_val<OFF_ANALOG){
    printAndSend("ht");
    A1_state=OFF_STATE;
  }

  if(A2_state==OFF_STATE && A2_val>ON_ANALOG) A2_state = ON_STATE;
  if(A2_state==ON_STATE && A2_val<OFF_ANALOG){
    if(stButtonCount==0) { stMarkTime = millis(); }
    stButtonCount++;
    A2_state=OFF_STATE;
  }

  if(curTime-stMarkTime >=3000){
    if(stButtonCount && stButtonCount>=3){
      printAndSend("so");
    }
    else if(stButtonCount && stButtonCount<3){
      printAndSend("st");
    }
    stButtonCount = 0;
    stMarkTime = curTime;
  }

  if(curTime-gtMarkTime >=500){
    if(gtButtonCount && gtButtonCount>=2){
      printAndSend("sw");
    }
    else if(gtButtonCount && gtButtonCount==1){
      printAndSend("cp");
    }
    gtButtonCount = 0;
    gtMarkTime = curTime;
  }

  if(A3_state==OFF_STATE && A3_val>ON_ANALOG) A3_state = ON_STATE;
  if(A3_state==ON_STATE && A3_val<OFF_ANALOG){
    printAndSend("cs");
    A3_state=OFF_STATE;
    delay(100);
  }
  
  // Joystick
  int A6_val = analogRead(A6); //y-axis
  int A7_val = analogRead(A7); //x-axis

  if(A6_val<200 && (A7_val>300 || A7_val<700))
    printAndSend("b");
  else if(A6_val >800 && (A7_val>300 || A7_val<700))
          printAndSend("f");

   if(A7_val<150 && (A6_val>300 || A6_val<700))
       printAndSend("r");
   else if(A7_val >800 && (A6_val>300 || A6_val<700))
          printAndSend("l");
  
}

