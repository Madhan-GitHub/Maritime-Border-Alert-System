/*
  SMART HOME - temp sensor - relay - BT
  fullDevice code by frugal labs tech solutions pvt ltd, bangalore
  
 Send serial 1 for switch on and 0 for switch off
 Reads analog data from the temperature sensor LM35 on pin 0, prints the result to the serial monitor 
 For Atmega 8 analogReference(INTERNAL) makes the analog voltage range from 0 to 2.56 V
 1 division of ADC = 2.56/1000 = 0.0025 V = 2.5 mV
 For LM35, 10 mV change is 1°C change, 10/2.5 = 4
 this changes for atmega 168 and 328 (uno or nano has 1.1; so by 10 accordingly.)
 
 This example code is in the public domain.
 */
int relay_pin = 12; //initialize relay_pin to 12
const int temp_gnd = A0;             // analog input pin 0 -- ground
const int temp_vcc = A2;              // analog input pin 2 -- voltage
int temp_out =A1;                      // analog input pin 1 -- data
int cloud_in;//initializing cloud input as integer
float tempC;//temperature variable
int temp_read;//analog temp_read



void setup()
{ 
  Serial.begin(9600);//I configured my HC-05 to communicate at 9600 baud rate and hence i am using 	
  pinMode(relay_pin,OUTPUT); //make pin 12 as OUTPUT 
  pinMode(temp_gnd, OUTPUT); // temp_gnd A0 as output
  pinMode(temp_vcc, OUTPUT);  //  temp_vcc A2 as output
  digitalWrite(temp_gnd, LOW); // temp_gnd A0 as LOW
  digitalWrite(temp_vcc, HIGH); // temp_vcc A0 as HIGH
  analogReference(INTERNAL);
} 

void loop()
{ 
  temperature();
  switch_control();
}

void temperature()
{
  temp_read = analogRead(temp_out);//read the analog pin
  tempC = temp_read/4;
  Serial.println(tempC);
  Serial1.print(tempC);//print temperature on serial port
  delay(20);
}

void switch_control()
{
  if (Serial.available()>0)
  {
    cloud_in = Serial.read();        // read next available byte
    if (cloud_in == '0')
    {
      Serial.println("0 received; switch is off.");Serial.println("0 received; switch is off.");
      digitalWrite(relay_pin, LOW);
    }
    else if (cloud_in == '1')
    {
      Serial.println("1 received; switch is on.");
       Serial1.write("1 received; switch is on.");
      digitalWrite(relay_pin, HIGH);
    }
    else 
    {
      digitalWrite(relay_pin, LOW);
      Serial.println("Enter 0 or 1 only.");
      Serial1.write("Enter 0 or 1 only.");
    }
   }
  delay(5);
}
