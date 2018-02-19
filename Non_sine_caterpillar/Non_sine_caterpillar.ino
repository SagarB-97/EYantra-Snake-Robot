#include <Servo.h>
#include <math.h>

#define PI 3.14159

Servo servo2,servo3,servo4,servo5,servo6,servo7,servo8;

int counter = 0;

int frequency1 = 1;
int frequency2 = 1;

float lag1 = 240*PI/180;
float lag2 = 180*PI/180;

float b = 120*PI/180;
float amplitude_h = 15;
float amplitude = 80;
float ph = PI/2;

int pos2_init = 75;
int pos3_init = 110;
int pos4_init = 77;
int pos5_init = 115;
int pos6_init = 120;
int pos7_init = 77;
int pos8_init = 90;

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
    servo3.write(pos3_init)  ;
    servo5.write(pos5_init)  ;
    servo7.write(pos7_init) ;


  servo8.write(pos8_init+0)  ;
 servo6.write(pos6_init+0)  ;
  servo4.write(pos4_init+0)  ;
   servo2.write(pos2_init-75);    
 delay(1000);

 servo8.write(pos8_init+0);  
  servo6.write(pos6_init+50) ; 
  servo4.write(pos4_init+50)  ;
  servo2.write(pos2_init+30);
 delay(1000);     
 
  servo8.write(pos8_init-60);  
 servo6.write(pos6_init-60) ;
  delay(1000); 
  servo4.write(pos4_init-20)  ;
  servo2.write(pos2_init+0);
  delay(1000);
 
     servo8.write(pos8_init+0);  
     servo6.write(pos6_init+0) ; 
     servo4.write(pos4_init+0)  ;
     servo2.write(pos2_init+0);
     delay(1000);



  delay(10);
}
