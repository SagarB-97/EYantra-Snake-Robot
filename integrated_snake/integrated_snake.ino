#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <math.h>
#include <string.h>

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

Servo servo2,servo3,servo4,servo5,servo6,servo7,servo8;

int pos2_init = 70;
int pos3_init = 110;
int pos4_init = 77;
int pos5_init = 95;
int pos6_init = 120;
int pos7_init = 62;
int pos8_init = 80;

int flagc=0;
int flagcb=0;
int flaglt=0;
int flagrt=0;
int flagsd=0;

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

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
void caterpillar(){
  static  int counter,frequency,amplitude,amplitude_h;
  static float lag;
  if(flagc==0){
   counter = 0;
   frequency = 4;
   lag = PI/2;
   amplitude = 0;
   amplitude_h = 40;
   flagc=1;
  }
  int pos2_val = pos2_init + floor(amplitude_h*cos(frequency*counter*PI/180));
  servo2.write(pos2_val); 
  servo3.write(pos3_init);

  int pos4_val = pos4_init - floor(amplitude_h*cos(frequency*counter*PI/180 - 1*lag)); 
  servo4.write(pos4_val);
  servo5.write(pos5_init);

  int pos6_val = pos6_init + floor(amplitude_h*cos(frequency*counter*PI/180 - 2*lag));
  servo6.write(pos6_val); 
  servo7.write(pos7_init);

  int pos8_val = pos8_init - floor(amplitude_h*cos(frequency*counter*PI/180 - 3*lag));
  servo8.write(pos8_val); 
  counter = (counter+10)%360;
  delay(100);
}
void caterpillar_b(){
  static  int counter,frequency,amplitude,amplitude_h;
  static float lag;
  if(flagcb==0){
   counter = 0;
   frequency = 4;
   lag = PI/2;
   amplitude = 0;
   amplitude_h = 40;
   flagcb=1;
  }
  int pos8_val = pos8_init + floor(amplitude_h*cos(frequency*counter*PI/180));
  servo8.write(pos8_val); 
  servo3.write(pos3_init);

  int pos6_val = pos6_init - floor(amplitude_h*cos(frequency*counter*PI/180 - 1*lag)); 
  servo6.write(pos6_val);
  servo5.write(pos5_init);

  int pos4_val = pos4_init + floor(amplitude_h*cos(frequency*counter*PI/180 - 2*lag));
  servo4.write(pos4_val); 
  servo7.write(pos7_init);

  int pos2_val = pos2_init - floor(amplitude_h*cos(frequency*counter*PI/180 - 3*lag));
  servo2.write(pos2_val); 
  counter = (counter+10)%360;
  delay(100);
}
void lturning(){
  static int counter;
  static float frequency1,frequency2,lag1,lag2,a,b,c,n,amplitude_h,beta,alpha,gamma;
  if(flaglt==0){
    counter = 0;
    frequency1 = 2;
    frequency2 = 2;
    lag1 = 240*PI/180;
    lag2 = 180*PI/180;
    a=80;
    b =2*PI;
    c=0;
    n=3;
    beta = b/n;
    alpha = abs(a*sin(beta/2));
    gamma = -c/n;
    amplitude_h = 30;
    flaglt=1;
  }
  int pos2_val = pos2_init + floor(-(amplitude_h*sin(frequency2*counter*PI/180 + b + 0*lag2)));
  servo2.write(pos2_val); 

  int pos3_val = pos3_init + floor(alpha*sin(frequency1*counter*PI/180 + 0*beta)+gamma);
  servo3.write(pos3_val); 

  int pos4_val = pos4_init + floor((amplitude_h*sin(frequency2*counter*PI/180 + b + 1*lag2)));
  servo4.write(pos4_val); 

  int pos5_val = pos5_init + floor((alpha*sin(frequency1*counter*PI/180 + 1*beta))+gamma);
  servo5.write(pos5_val);
  
  int pos6_val = pos6_init + floor(-(amplitude_h*sin(frequency2*counter*PI/180 + b + 2*lag2)));
  servo6.write(pos6_val); 
  
  int pos7_val = pos7_init + floor(-alpha*sin(frequency1*counter*PI/180 + 2*beta)+gamma);
  servo7.write(pos7_val);
  
  int pos8_val = pos8_init + floor(amplitude_h*sin(frequency2*counter*PI/180 + b + 3*lag2));
  servo8.write(pos8_val);
  
  counter = (counter+1)%360;
  delay(10);
}
void rturning(){
  static int counter;
  static float frequency1,frequency2,lag1,lag2,a,b,c,n,amplitude_h,beta,alpha,gamma;
  if(flagrt==0){
    counter = 0;
    frequency1 = 2;
    frequency2 = 2;
    lag1 = 240*PI/180;
    lag2 = 180*PI/180;
    a=80;
    b =2*PI;
    c=0;
    n=3;
    beta = b/n;
    alpha = abs(a*sin(beta/2));
    gamma = -c/n;
    amplitude_h = 30;
    flagrt=1;
  }
  int pos2_val = pos2_init + floor(-(amplitude_h*sin(frequency2*counter*PI/180 + b + 0*lag2)));
  servo2.write(pos2_val); 

  int pos3_val = pos3_init + floor(-alpha*sin(frequency1*counter*PI/180 + 0*beta)+gamma);
  servo3.write(pos3_val); 

  int pos4_val = pos4_init + floor((amplitude_h*sin(frequency2*counter*PI/180 + b + 1*lag2)));
  servo4.write(pos4_val); 

  int pos5_val = pos5_init + floor(-(alpha*sin(frequency1*counter*PI/180 + 1*beta))+gamma);
  servo5.write(pos5_val);
  
  int pos6_val = pos6_init + floor(-(amplitude_h*sin(frequency2*counter*PI/180 + b + 2*lag2)));
  servo6.write(pos6_val); 
  
  int pos7_val = pos7_init + floor(alpha*sin(frequency1*counter*PI/180 + 2*beta)+gamma);
  servo7.write(pos7_val);
  
  int pos8_val = pos8_init + floor(amplitude_h*sin(frequency2*counter*PI/180 + b + 3*lag2));
  servo8.write(pos8_val);
  
  counter = (counter+1)%360;
  delay(10);
}

void sidewinding(){
  static int counter;
  static float frequency1,frequency2,lag1,lag2,b,amplitude_h,amplitude;
  if(flagsd==0){
    counter = 0;
    frequency1 = 2;
    frequency2 = 2;
    lag1 = 240*PI/180;
    lag2 = 180*PI/180;
    b = 120*PI/180;
    amplitude_h = 10;
    amplitude = 80;
    flagsd=1;
 }
  int pos2_val = pos2_init + floor(-(amplitude_h*sin(frequency2*counter*PI/180 + b + 0*lag2)));
  servo2.write(pos2_val); 
  Serial.println(pos2_val);
  
  
  int pos3_val = pos3_init + floor(amplitude*sin(frequency1*counter*PI/180 + 0*lag1));
  servo3.write(pos3_val); 
  

  int pos4_val = pos4_init + floor(amplitude_h*sin(frequency2*counter*PI/180 + b + 1*lag2));
  servo4.write(pos4_val); 
  

  int pos5_val = pos5_init + floor(-(amplitude*sin(frequency1*counter*PI/180 + 1*lag1)));
  servo5.write(pos5_val);
  
  int pos6_val = pos6_init + floor(-(amplitude_h*sin(frequency2*counter*PI/180 + b + 2*lag2)));
  servo6.write(pos6_val); 
  
  int pos7_val = pos7_init + floor(amplitude*sin(frequency1*counter*PI/180 + 2*lag2));
  servo7.write(pos7_val);
  
  int pos8_val = pos8_init + floor(amplitude_h*sin(frequency2*counter*PI/180 + b + 3*lag2));
  servo8.write(pos8_val);
  
  counter = (counter+1)%360;

  delay(20);
  //Serial.println("xxx");
}

void loop() {
  //char text[32]="";
  long int i, count=0;
  char a[2]={'g','t'};
  char b[2]={'n','m'};
  flagc=0;
  flagcb=0;
  flagrt=0;
  flaglt=0;
  
    if (radio.available()) {
    char text[5] = "";
    radio.read(text, sizeof(text));
      //Serial.println(text);
    if(text[0]==a[0] && text[1]==a[1]){
      //Serial.println(text);
      count+=1;
      for(i=0;i<50000;i++){
          if(radio.available()){
            radio.read(text,sizeof(text));
            if(text[0]==a[0] && text[1]==a[1])
              count+=1;
          }
      }
      Serial.println(count);
      //Serial.println("over");
  }
  }
  
  if(count==1){
    char text_1[5]="";
    while(1){
      if(radio.available()){
        radio.read(text_1,sizeof(text_1));  
        if(text_1[0]=='f')  
          {caterpillar();}
           //Serial.println('c');}
        else if(text_1[0]=='b')
          {caterpillar_b();}
        else if(text_1[0]=='l')
          {lturning();}
        else if(text_1[0]=='r')
          {rturning();}
        else if(text_1[0]==b[0] && text_1[1]==b[1])
           break;
       }
      else{
        equilibrium();
        flagc=0;
        flagcb=0;
        flagrt=0;
        flaglt=0; 
      }
    
    }
  }
//  if(count==2){
//    char text_2[5]="";
//    while(1){
//      if(radio.available()){
//        radio.read(text_2,sizeof(text_2));
//        if(text_2[0]=='l')  
//        { turning();
//          Serial.println('t');}
//        else if(text_2[0]==b[0] && text_2[1]==b[1])
//          break; 
//     }
//     else{
//        equilibrium();
//        flagt=0; 
//     }
//   }
// }
  if(count==2){
    char text_3[5]="";
    while(1){
      if(radio.available()){
        radio.read(text_3,sizeof(text_3));
        if(text_3[0]=='l')  
        { sidewinding();
          Serial.println('sd');}
        else if(text_3[0]==b[0] && text_3[1]==b[1])
          break; 
     }
     else{
        equilibrium();
        flagsd=0; 
     }
   }
  }
    count=0;        
  }     
      
    
  
  
  
  
  

