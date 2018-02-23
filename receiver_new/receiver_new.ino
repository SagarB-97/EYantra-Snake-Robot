#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <math.h>

#include "Caterpillar.h"
#include "SideWinding.h"
#include "HeadTurn.h"

RF24 radio(9,10);


const byte address[6] = "00001";


void equilibrium(){
  servo2.write(pos2_init);
  servo3.write(pos3_init);
  servo4.write(pos4_init);
  servo5.write(pos5_init);
  servo6.write(pos6_init);
  servo7.write(pos7_init);
  servo8.write(pos8_init);
}

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
  servo7.attach(7);
  servo8.attach(8);

  equilibrium();
  headTurnParams.motor = 5;
}

void loop() {

  if (radio.available()) {
    char inp[5];
    radio.read(inp, sizeof(inp));
    //Serial.print("Received : ");
    //Serial.println(inp);
    
    if(strcmp(inp,"f")==0){
      if(strcmp(gait,"cp")==0) forward();
      state = 'f';
    }
    else if(strcmp(inp,"b")==0){
      if(strcmp(gait,"cp")==0) backward();
      state = 'b';
    }
    else if(strcmp(inp,"l")==0){
      if(strcmp(gait,"cp")==0) left();
      else if(strcmp(gait,"sw")==0) sideWindingLeft();
      else if(strcmp(gait,"ht")==0) headTurnLeft();
      state = 'l';
    }
    else if(strcmp(inp,"r")==0){
      if(strcmp(gait,"cp")==0) right();
      else if(strcmp(gait,"sw")==0) sideWindingRight();
      else if(strcmp(gait,"ht")==0) headTurnRight();
      state = 'r';
    }    

    
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
    else if(strcmp(inp,"ht")==0){
      if(strcmp(gait,"ht")==0) { 
        if(headTurnParams.motor==7) headTurnParams.motor = 5;
        else if(headTurnParams.motor==5) headTurnParams.motor = 7;
      }
      else { equilibrium(); headTurnReset(); }
      strcpy(gait,inp);
      state = 's';
    }

    
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

  else{
    if(strcmp(gait,"ht")!=0) equilibrium();
    state='s';
  }
}
