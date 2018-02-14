#include <Servo.h>
#include <math.h>

Servo servo2,servo3,servo4,servo5,servo6,servo7,servo8;

int cap(int a){
  a = min(180,a);
  a = max(a,0);
  return a;
}

int counter = 0;
int frequency = 4;
float lag = PI/2;
int amplitude = 0;
int amplitude_h = 35;

int pos2_init = 70;
int pos3_init = 110;
int pos4_init = 115;
int pos5_init = 121;
int pos6_init = 120;
int pos7_init = 78;
int pos8_init = 80;

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
  servo7.attach(7);
  servo8.attach(8);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Caterpillar - Sin Wave
  
  int pos2_val = pos2_init + floor(amplitude_h*cos(frequency*counter*PI/180));
  //pos2_val = cap(pos2_val);
  servo2.write(pos2_val); //
  //Serial.println(pos2_val);

  servo3.write(pos3_init);

  int pos4_val = pos4_init - floor(amplitude_h*cos(frequency*counter*PI/180 - 1*lag)); 
  //pos4_val = cap(pos4_val);
  servo4.write(pos4_val); //
  //Serial.println(pos4_val);

  servo5.write(pos5_init);

  int pos6_val = pos6_init + floor(amplitude_h*cos(frequency*counter*PI/180 - 2*lag));
  //pos6_val = cap(pos6_val);
  servo6.write(pos6_val); //
  //Serial.println(pos6_val);

  servo7.write(pos7_init);

  int pos8_val = pos8_init - floor(amplitude_h*cos(frequency*counter*PI/180 - 3*lag));
  //pos8_val = cap(pos8_val);
  servo8.write(pos8_val); //
  //Serial.println(pos8_val);

  counter = (counter+10)%360;
  delay(100);
  
/*
  servo2.write(pos2_init + 50);
  servo4.write(pos4_init + 50);
  servo6.write(pos6_init + 0);
  servo8.write(pos8_init + 0);
  delay(500);

  
  servo2.write(pos2_init + 0);
  servo4.write(pos4_init + 50);
  servo6.write(pos6_init + 50);
  servo8.write(pos8_init + 0);
  delay(500);
  */
}
