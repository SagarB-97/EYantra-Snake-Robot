/*
 * Team Id: SS#2364
 * Author List: Sagar Bharadwaj, Nagarakshith M S, Samarth Bonthala, Prajwal Bharadwaj
 * Filename: RodentDetection.ino
 * Theme: eYRC 2017 Spotter Snake
*/

#include <Servo.h>
Servo myservo;  // create servo object to control a servo

#define BLUE_CONDITION (frequency_r >= 77 && frequency_r <= 113) && (frequency_b >= 75 && frequency_b <= 89) && (frequency_g >= 98 && frequency_g <= 125)
#define RED_CONDITION (frequency_r >= 85 && frequency_r <= 101) && (frequency_b >= 116 && frequency_b <= 139) && (frequency_g >= 135 && frequency_g <= 172)

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int pos1= 75;
int pos2= 120;
int flag=0;
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(12, OUTPUT);//BUZZER 
  pinMode(13, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(9,HIGH);//FOR RED LIGHT
  digitalWrite(10,HIGH);//FOR GREEN LIGHT
  myservo.attach(11);
  myservo.write(pos1);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(13,HIGH);//GREEN LED
  
  Serial.begin(9600);
}
char color_detector(){
  int frequency_r,frequency_b,frequency_g,r_th,b_th;
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
  frequency_g = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("G= ");//printing name
  //Serial.print(frequency);//printing RED color frequency
  //Serial.print("  ");
  delay(10);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency_b = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("B= ");//printing name
  //Serial.print(frequency_b);//printing RED color frequency
  //Serial.println("  ");
  delay(10);
  if(RED_CONDITION)
    out='r';
  else if(BLUE_CONDITION)
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
    //if(flag==0)
    //delay(1000);
}
void servo_clear(){
    myservo.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(1); 
}
void led_off(){
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
  }
void rod_buzzer(){
  
   digitalWrite(12,HIGH);
   //Serial.println("bzzzzz");
   delay(1000);
   digitalWrite(12,LOW);
   delay(500);
   digitalWrite(12,HIGH);
   delay(1000);
   digitalWrite(12,LOW);
   
}
void st_buzzer(){
   digitalWrite(12,HIGH);
   delay(2000);
   digitalWrite(12,LOW);
   delay(500);
   digitalWrite(12,HIGH);
   delay(2000);
   digitalWrite(12,LOW);
  }
void stp_buzzer(){
   digitalWrite(12,HIGH);
   delay(100);
   digitalWrite(12,LOW);
   delay(1000);
   digitalWrite(12,HIGH);
   delay(100);
   digitalWrite(12,LOW);
   delay(1000);
   digitalWrite(12,HIGH);
   delay(100);
   digitalWrite(12,LOW);
   delay(1000);
   digitalWrite(12,HIGH);
   delay(100);
   digitalWrite(12,LOW);
   delay(1000);
   digitalWrite(12,HIGH);
   delay(100);
   digitalWrite(12,LOW);
   delay(1000);
  }
void cs_on()
{
   digitalWrite(13,LOW);
   delay(500);
   digitalWrite(13,HIGH);
}
void cs_off()
{
   digitalWrite(13,LOW);
   delay(200);
   digitalWrite(13,HIGH);
   delay(200);
   digitalWrite(13,LOW);
   delay(200);
   digitalWrite(13,HIGH);
   delay(200);
   digitalWrite(13,LOW);
   delay(200);
   digitalWrite(13,HIGH);
}
  
void loop(){
  char o;
  static int flagcs;
  int flagst=0;
  int flagstp=0;
  if(Serial.available()){
  char x;
  x=Serial.read();
  if(x=='y'){
    st_buzzer();   
  }
  if(x=='z'){
    stp_buzzer();   
  }
  if(x=='x'){
    flagcs=!flagcs;
    if(flagcs==1){
      cs_on();
    }
    else if(flagcs==0){
      cs_off();
    }
  }
  }
  if(flagcs){
    int countr=0,countb=0;
    for(int i=0;i<11;i++){
     o=color_detector(); 
     if(o=='r'){
      countr++;
     }
     else if(o=='b'){
      countb++;
     }
    }
    
    //servo_clear();
    if(countr>=6){
       led_on('r');
      if(flag==0){
        servo();
        rod_buzzer();
        }
      flag=1;
      //Serial.println('r');
    }
    else if(countb>=6){
      led_on('b');
      if(flag==0){
        servo();
        rod_buzzer();
        }
      flag=1;
      //Serial.println('b');
    }
    else{ 
      flag=0;
      servo_clear();
      led_off();
      //Serial.println("o");
    }
  }
 else{
  flag=0;
  //Serial.println("out");
  servo_clear();
  led_off();
 }
}
  

