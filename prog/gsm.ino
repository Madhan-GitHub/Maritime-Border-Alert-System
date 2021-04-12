


#include <String.h>

char data[256];

void setup()

{

Serial.begin(9600);

Serial.begin(15200); // the GPRS baud rate

delay(1000);

}

void loop()

{

if (Serial.available())

switch(Serial.read())

{

case 't':

SendTextMessage();

break;

case 'r':

ReceiveTextMessage();

break;

case 'd':

DialVoiceCall();

break;

case 'a':

AnswerVoiceCall();

break;

case 'g':

GPRS();

break;

}

if (Serial.available())

Serial.write(Serial.read());

}

void AnswerVoiceCall()

{

Serial.println("ATA");

}

void SendTextMessage()

{

Serial.print("AT+CMGF=1\r"); //Because we want to send the SMS in

delay(1000);

Serial.println("AT+CMGS=\"8940870303\"");

delay(1000);

Serial.write("Hello from Galileo?");

delay(1000);

Serial.println((char)26); //the ASCII code of the ctrl+z is 26 (0x1A)

delay(1000);

Serial.println();

}

void ReceiveTextMessage()

{

Serial.println("AT+CMGF=1"); //Because we want to receive the SMS

delay(1000);

Serial.println("AT+CPMS=\"SM\""); // read first SMS

delay(1000);

Serial.println("AT+CMGL=\"ALL\""); // show message

}

void DialVoiceCall()

{

Serial.println("ATD + 8940870303;");//dial the number

delay(100);

Serial.println();

}

void ShowSerialData()

{

while(Serial.available()!=0)

Serial.write(Serial.read());

}

void GPRS()

{

Serial.println("AT+CPIN?"); // Is SIM ready to use?

delay(1000);

ShowSerialData();

Serial.println("AT+CGREG?"); // Is device registered?


delay(1000);

ShowSerialData();

Serial.println("AT+COPS?"); // Does SIM info match network?

delay(1000);

ShowSerialData();

Serial.println("Check signal quality");

Serial.println("AT+CSQ"); // Check signal quality

delay(1000);

ShowSerialData();

Serial.println("AT+cgatt=1"); // GPRS attach// define a PDP context with IP connection, ID is 1

Serial.println("AT+CGDCONT=1,\"IP\",\"fast.t-mobile.com\"");

delay(1000);

ShowSerialData();

// list PDP contexts that are defined

Serial.println("at+cgdcont?");

delay(3000);

ShowSerialData();

// setup the session using the appropriate PDP context

Serial.println("AT+CGACT=1,1");

delay(1000);

ShowSerialData();

Serial.println("session is setup delay 5 seconds");

delay(5000);

// deactivate the PDP context

Serial.println("AT+CGACT=0,1");


delay(1000);

ShowSerialData();

// detach from GPRS newtork

Serial.println("AT+CGATT=0");

delay(1000);

}

