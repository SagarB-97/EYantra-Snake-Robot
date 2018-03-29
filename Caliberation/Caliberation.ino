/*
 * Team Id: SS#2364
 * Author List: Sagar Bharadwaj, Nagarakshith M S, Samarth Bonthala, Prajwal Bharadwaj
 * Filename: Caliberation.ino
 * Purpose : Automatic caliberation of color sensor
*/

#include <stdio.h>

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int number_of_samples = 100;
int r_min,g_min,b_min,r_max,g_max,b_max;


void clearInput() {
  while (Serial.read() != -1);
}

char getChar() {
  while (Serial.available() == 0)
    ;
  return(toupper(Serial.read()));
}

/*
 * Function Name: caliberate
 * Input: out_r, out_g, out_b
 * Output: Writes into the pointer arguments the avearage color sensor values calculated across a large number of samples
 * Example Call: caliberate(&red_value, &g_value, &b_value)
 */
void caliberate(int *out_r, int *out_g, int *out_b) {
  int frequency_r,frequency_b,frequency_g;
  float sum_frequency_r = 0.0, sum_frequency_b = 0.0, sum_frequency_g = 0.0;

  int i;

  // Taking a large number of samples and then taking the mean to avoid noisy sensor values 
  for(i = 1;i<=number_of_samples;i++) {
    // Setting red filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    // Reading the output frequency
    frequency_r = pulseIn(sensorOut, LOW);
    sum_frequency_r += frequency_r;
    delay(10);
  
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    // Reading the output frequency
    frequency_g = pulseIn(sensorOut, LOW);
    sum_frequency_g += frequency_g;
    delay(10);
  
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    // Reading the output frequency
    frequency_b = pulseIn(sensorOut, LOW);
    sum_frequency_b += frequency_b;
    delay(10);
  }

  float avg_frequency_r = sum_frequency_r / number_of_samples;
  float avg_frequency_g = sum_frequency_g / number_of_samples;
  float avg_frequency_b = sum_frequency_b / number_of_samples;

  *out_r = (int)avg_frequency_r;
  *out_g = (int)avg_frequency_g;
  *out_b = (int)avg_frequency_b;

  Serial.println("Avg Values : ");
  
  Serial.print("Average Red = ");
  Serial.println(avg_frequency_r);

  Serial.print("Average Green = ");
  Serial.println(avg_frequency_g);

  Serial.print("Average Blue = ");
  Serial.println(avg_frequency_b);
}


/*
 * Function Name: printCondition
 * Input: NONE
 * Output: A String printed on the serial monitor that can be directly plugged into RodentDetection.ino file as BLUE_CONDITION and RED_CONDITION macro values
 * Example Call: printCondition()
 */
void printCondition() {
Serial.print("(frequency_r >= ");
  Serial.print(min(r_min,r_max) - 5);
  Serial.print(" && frequency_r <= ");
  Serial.print(max(r_min,r_max) + 5);
  Serial.print(") && ");
  
  Serial.print("(frequency_b >= ");
  Serial.print(min(b_min,b_max) - 5);
  Serial.print(" && frequency_b <= ");
  Serial.print(max(b_min,b_max) + 5);
  Serial.print(") && ");

  Serial.print("(frequency_g >= ");
  Serial.print(min(g_min,g_max) - 5);
  Serial.print(" && frequency_g <= ");
  Serial.print(max(g_min,g_max) + 5);
  Serial.println(")");

}


void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(sensorOut, INPUT);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(13,HIGH);

  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}


void loop() {

  Serial.println("Place Sensor on Blue-Min and press any key...");
  getChar();
  clearInput();
  caliberate(&r_min,&g_min,&b_min);

  Serial.println("\n\nPlace Sensor on Blue-Max and press any key...");
  getChar();
  clearInput();
  caliberate(&r_max,&g_max,&b_max);

  Serial.println("\nBlue Condition : ");
  printCondition();
  
  Serial.println("\n\nPlace Sensor on Red-Min and press any key...");
  getChar();
  clearInput();
  caliberate(&r_min,&g_min,&b_min);

  Serial.println("\n\nPlace Sensor on Red-Max and press any key...");
  getChar();
  clearInput();
  caliberate(&r_max,&g_max,&b_max);

  Serial.println("\nRed Condition : ");
  printCondition();

  Serial.println("\n\nCaliberation complete...");
  getChar();
  clearInput();
}
