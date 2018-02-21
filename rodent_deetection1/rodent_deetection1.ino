/*     Arduino Color Sensing Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
// pin 9 for red light and 10 for blue light
#include <Servo.h>
Servo myservo;  // create servo object to control a servo

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int pos1= 20;
int pos2= 180;
int flag=0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  myservo.attach(11);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
char color_detector(){
  int frequency_r,frequency_b,frequency,r_th,b_th;
  r_th=100;
  b_th=100;
  char out;
    // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency_r = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("R= ");//printing name
  //Serial.print(frequency_r);//printing RED color frequency
  //Serial.print("  ");
  delay(10);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("G= ");//printing name
  //Serial.print(frequency);//printing RED color frequency
  //Serial.print("  ");
  delay(100);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency_b = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("B= ");//printing name
  //Serial.print(frequency_b);//printing RED color frequency
  //Serial.println("  ");
  delay(100);
  if(frequency>100 && frequency_b>70 && frequency_r<90 )
    out='r';
  else if(frequency>60 && frequency_b<60 && frequency<100)
    out='b';
  return out;
}
void led_on(char a){
  //char z;
  //z=a;
  if (a=='r'){
    digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
   
   }
  else if (a=='b'){
    digitalWrite(10,LOW);
    digitalWrite(9,HIGH);
    
}}
void servo(){
    myservo.write(pos2);// tell servo to go to position in variable 'pos'
    if(flag==0)
    delay(1000);
}
void servo_clear(){
    myservo.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(1); 
}
void led_off(){
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
  }
void buzzer(){
  if(flag==0){
   digitalWrite(12,HIGH);
   //Serial.println("bzzzzz");
   delay(1000);
   digitalWrite(12,LOW);
   delay(500);
   digitalWrite(12,HIGH);
   delay(1000);
   digitalWrite(12,LOW);
   }
}
void loop(){
  char o;
  o=color_detector();
  servo_clear();
  if((o=='r' || o=='b')){
  led_on(o);
  //buzzer();
  servo();
  buzzer();
  flag=1;
  Serial.println(o);
  }
  else //if(flag==1)
  { //Serial.println('a');
    flag=0;
   servo_clear();
  led_off();}
}
