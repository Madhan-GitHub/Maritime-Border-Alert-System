const int sensor = 2;    // switch input
const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4; 

const int motor3Pin = 5;    // H-bridge leg 1 (pin 2, 1A)
const int motor4Pin = 6; 
const int B=7;
const int L=13;
void setup() {
    
    pinMode(sensor, INPUT); 
 
   
    pinMode(motor1Pin, OUTPUT);
    pinMode(motor2Pin, OUTPUT);
    
    pinMode(motor3Pin, OUTPUT);
    pinMode(motor4Pin, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(L, OUTPUT);
  }
  void loop() {
    
    if (digitalRead(sensor) == HIGH) {
      digitalWrite(B,HIGH);
      digitalWrite(L,HIGH);
      digitalWrite(motor1Pin, LOW);  
      digitalWrite(motor2Pin, HIGH); 
     digitalWrite(motor3Pin, HIGH);  
      digitalWrite(motor4Pin, LOW); 
    delay(1000);
  }
   else {
      digitalWrite(B,LOW);
      digitalWrite(L,LOW);
      digitalWrite(motor1Pin, HIGH);  
      digitalWrite(motor2Pin, LOW);   
  digitalWrite(motor3Pin, LOW);  
      digitalWrite(motor4Pin, HIGH);  
  delay(1000);  
  }
  }
    





