#include <Servo.h>
#include <math.h>

#define PI 3.14159

Servo servo2,servo3,servo4,servo5,servo6,servo7,servo8;

int pos2_init = 70;
int pos3_init = 110;
int pos4_init = 77;
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

  
  servo2.write(pos2_init);
  servo3.write(pos3_init);
  servo4.write(pos4_init);
  servo5.write(pos5_init);
  servo6.write(pos6_init);
  servo7.write(pos7_init);
  servo8.write(pos8_init);

  
  servo7.write(180);
  
  servo5.write(180);
}

void loop() {
  servo3.write(0);

}
