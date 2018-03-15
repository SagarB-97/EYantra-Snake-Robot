#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int number_of_samples = 100;


void clearInput() {
  while (Serial.read() != -1);
}

char getChar() {
  while (Serial.available() == 0)
    ;
  return(toupper(Serial.read()));
}

void caliberate() {
  int frequency_r,frequency_b,frequency_g;
  float sum_frequency_r = 0.0, sum_frequency_b = 0.0, sum_frequency_g = 0.0;

  int i;
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

  Serial.println("Blue Values : ");
  
  Serial.print("Average Red = ");
  Serial.println(avg_frequency_r);

  Serial.print("Average Green = ");
  Serial.println(avg_frequency_g);

  Serial.print("Average Blue = ");
  Serial.println(avg_frequency_b);
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
  caliberate();

  Serial.println("\n\nPlace Sensor on Blue-Max and press any key...");
  getChar();
  clearInput();
  caliberate();

  Serial.println("\n\nPlace Sensor on Red-Min and press any key...");
  getChar();
  clearInput();
  caliberate();

  Serial.println("\n\nPlace Sensor on Red-Max and press any key...");
  getChar();
  clearInput();
  caliberate();

  Serial.println("\n\nCaliberation complete...");
  getChar();
  clearInput();


  /*
  int frequency_r,frequency_b,frequency_g;
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  frequency_r = pulseIn(sensorOut, LOW);
  Serial.print(frequency_r);
  Serial.print("\t");
  delay(10);

  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  frequency_g = pulseIn(sensorOut, LOW);
  Serial.print(frequency_g);
  Serial.print("\t");
  delay(10);


  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  frequency_b = pulseIn(sensorOut, LOW);
  Serial.print(frequency_b);
  Serial.print("\n");
  delay(10);
  */
}
