#include <Servo.h>
#include <math.h>

#define PI 3.14159

Servo servo2,servo3,servo4,servo5,servo6,servo7,servo8;

int counter = 0;

float frequency1 = 1;
float frequency2 = 2;

float lag1 = 240*PI/180;
float lag2 = 180*PI/180;

float b = 120*PI/180;
float amplitude_h = 10;
float amplitude = 80;

int pos2_init = 70;
int pos3_init = 110;
int pos4_init = 115;
int pos5_init = 115;
int pos6_init = 120;
int pos7_init = 82;
int pos8_init = 80;

void setup() {
  
  Serial.begin(9600);
  
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
  servo7.attach(7);
  servo8.attach(8);
}

void loop() {
  int pos2_val = pos2_init + floor(-(amplitude_h*sin(frequency2*counter*PI/180 + b + 0*lag2)));
  servo2.write(pos2_val); 
  //Serial.print("pos2 = ");
  //Serial.println(pos2_val);
  
  int pos3_val = pos3_init + floor(amplitude*sin(frequency1*counter*PI/180 + 0*lag1));
  servo3.write(pos3_val); 
  Serial.print("pos3 = ");
  Serial.println(pos3_val);

  int pos4_val = pos4_init + floor(amplitude_h*sin(frequency2*counter*PI/180 + b + 1*lag2));
  servo4.write(pos4_val); 
  //Serial.print("pos4 = ");
  //Serial.println(pos4_val);

   int pos5_val = pos5_init + floor(-(amplitude*sin(frequency1*counter*PI/180 + 1*lag1)));
  servo5.write(pos5_val);
  Serial.print("pos5 = ");
  Serial.println(pos5_val);

  int pos6_val = pos6_init + floor(-(amplitude_h*sin(frequency2*counter*PI/180 + b + 2*lag2)));
  servo6.write(pos6_val); 
  //Serial.print("pos6 = ");
  //Serial.println(pos6_val);

   int pos7_val = pos7_init + floor(amplitude*sin(frequency1*counter*PI/180 + 2*lag2));
  servo7.write(pos7_val);
  Serial.print("pos7 = ");
  Serial.println(pos7_val);

  int pos8_val = pos8_init + floor(amplitude_h*sin(frequency2*counter*PI/180 + b + 3*lag2));
  servo8.write(pos8_val);
  //Serial.print("pos8 = ");
  //Serial.println(pos8_val);

  counter = (counter+1)%360;

  delay(10);
}
