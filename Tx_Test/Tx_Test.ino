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
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void printAndSend(const char str[]){
  //radio.write(str, sizeof(str));
  Serial.println(str);
}

void loop() {
  // Push Buttons
  int A2_val = analogRead(A2);
  int A1_val = analogRead(A1);
  int A0_val = analogRead(A0);


  /*Serial.print("A1 = ");
  printAndSend(A1_val);*/
  
  if(A0_state==OFF_STATE && A0_val>ON_ANALOG) A0_state = ON_STATE;
  if(A0_state==ON_STATE && A0_val<OFF_ANALOG){
    printAndSend("st");
    A0_state=OFF_STATE;
  }

  if(A1_state==OFF_STATE && A1_val>ON_ANALOG) A1_state = ON_STATE;
  if(A1_state==ON_STATE && A1_val<OFF_ANALOG){
    printAndSend("cs");
    A1_state=OFF_STATE;
  }
  
  // Joystick
  int A5_val = analogRead(A5);  // y-axis
  int A6_val = analogRead(A6);  // x-axis
  int A7_val = analogRead(A7);
  
  int A6_scale_value = (int)(((float)A6_val)/(1023)*9);
  int A7_scale_value = (int)(((float)A7_val)/(1023)*9);
  
  if(A6_scale_value>=6 | A6_scale_value<=3){
    char str[3] = "f0";
    str[1] = A6_scale_value+'0';
    printAndSend(str);
  }

  if(A7_scale_value>=6 | A7_scale_value<=3){
    char str[3] = "l0";
    str[1] = A7_scale_value+'0';
    printAndSend(str);
  }
  
  
}

