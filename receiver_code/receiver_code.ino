#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <math.h>

RF24 radio(9,10);

Servo servo2,servo3,servo4,servo5,servo6,servo7,servo8;

char state = 'i';
const byte address[6] = "00001";


int pos2_init = 70;
int pos3_init = 110;
int pos4_init = 77;
int pos5_init = 121;
int pos6_init = 120;
int pos7_init = 78;
int pos8_init = 80;


struct ForwardParams{
  int counter;
  int frequency;
  float lag;
  int amplitude;
  int amplitude_h;
} forwardParams;

struct TurnParams{
  int counter = 0;
  int frequency1 = 2;
  int frequency2 = 2;
  float lag1 = 240*PI/180;
  float lag2 = 180*PI/180;
  float a = 130;
  float b = 2*PI;
  float c = 0;
  float n = 3;
  float beta = b/n;
  float alpha = abs(a*sin(beta/2));
  float gamma = -c/n;
  float amplitude_h = 20;
} turnParams;


void forwardReset(){
  forwardParams.counter = 0;
  forwardParams.frequency = 4;
  forwardParams.lag = PI/2;
  forwardParams.amplitude = 0;
  forwardParams.amplitude_h = 35;
}
void forward(){
  if(state!='f')
    forwardReset();

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

  forwardParams.counter = (forwardParams.counter+10)%360;
  delay(100);
}
void backward(){
}

void leftReset(){
  turnParams.counter = 0;
  turnParams.frequency1 = 2;
  turnParams.frequency2 = 2;
  turnParams.lag1 = 240*PI/180;
  turnParams.lag2 = 180*PI/180;
  turnParams.a = 130;
  turnParams.b = 2*PI;
  turnParams.c = 10;
  turnParams.n = 3;
  turnParams.beta = turnParams.b/turnParams.n;
  turnParams.alpha = abs(turnParams.a*sin(turnParams.beta/2));
  turnParams.gamma = -turnParams.c/turnParams.n;
  turnParams.amplitude_h = 10;
}
void rightReset(){
  turnParams.counter = 0;
  turnParams.frequency1 = 2;
  turnParams.frequency2 = 2;
  turnParams.lag1 = 240*PI/180;
  turnParams.lag2 = 180*PI/180;
  turnParams.a = 130;
  turnParams.b = 2*PI;
  turnParams.c = -10;
  turnParams.n = 3;
  turnParams.beta = turnParams.b/turnParams.n;
  turnParams.alpha = abs(turnParams.a*sin(turnParams.beta/2));
  turnParams.gamma = -turnParams.c/turnParams.n;
  turnParams.amplitude_h = 10;
}

void turn(){
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

  turnParams.counter = (turnParams.counter+1)%360;

  delay(10);
}
void right(){
  if(state!='r') rightReset();
  turn();
}
void left(){
  if(state!='l') leftReset();
  turn();
}

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
}

void loop() {

  if (radio.available()) {
    char inp[5];
    radio.read(inp, sizeof(inp));
    Serial.print("Received : ");
    Serial.println(inp);
    
    if(strcmp(inp,"f")==0){
      forward();
      state = 'f';
    }
    else if(strcmp(inp,"b")==0){
      backward();
      state = 'b';
    }
    else if(strcmp(inp,"l")==0){
      left();
      state = 'l';
    }
    else if(strcmp(inp,"r")==0){
      right();
      state = 'r';
    }    
    else if(strcmp(inp,"gt")==0){
      equilibrium();
      state = 'g';
    }
  }

  else{
    equilibrium();
  }
}
