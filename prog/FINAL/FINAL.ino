const int sensor = 2;    // switch input
const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4; 

const int motor3Pin = 5;    // H-bridge leg 1 (pin 2, 1A)
const int motor4Pin = 6; 

void setup() {
    
    pinMode(sensor, INPUT); 
 
   
    pinMode(motor1Pin, OUTPUT);
    pinMode(motor2Pin, OUTPUT);
    
    pinMode(motor3Pin, OUTPUT);
    pinMode(motor4Pin, OUTPUT);
    Serial.begin(9600);
    Serial1.begin(9600);
    
  }
  void loop() {
    
    if (digitalRead(sensor) == HIGH) {
      digitalWrite(motor1Pin, LOW);  
      digitalWrite(motor2Pin, HIGH); 
     digitalWrite(motor3Pin, HIGH);  
      digitalWrite(motor4Pin, LOW); 
    }
    
    else {
      digitalWrite(motor1Pin, HIGH);  
      digitalWrite(motor2Pin, LOW);   
  digitalWrite(motor3Pin, LOW);  
      digitalWrite(motor4Pin, HIGH); 
      Serial.println("boatxx crossed border"); 
       Serial1.write("boatxx crossed border"); 
      
  }
  }
