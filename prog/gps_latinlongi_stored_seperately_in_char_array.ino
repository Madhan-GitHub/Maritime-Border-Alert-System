#include <string.h>
#include <ctype.h>

 int ledPin = 13;                  // LED test pin
 int rxPin = 0;                    // RX PIN 
 int txPin = 1;                    // TX TX
 int byteGPS=-1;
 char linea[300] = "";
 char comandoGPR[7] = "$GPRMC";
 int cont=0;
 int bien=0;
 int conta=0;
 int indices[13];

 void setup() {
   pinMode(ledPin, OUTPUT);       // Initialize LED pin
   pinMode(rxPin, INPUT);
   pinMode(txPin, OUTPUT);
   Serial.begin(4800);
   Serial1.begin(9600);
   for (int i=0;i<300;i++){       // Initialize a buffer for received data
     linea[i]=' ';
   }   
 }

 void loop() {
   char latidir,longidir;int l=0,m=0,b=4,c=4;char x[]="'";
   char lati[10]="";
   char longi[10]="";
   char latisnd[12]="";
   char longisnd[12]="";
   digitalWrite(ledPin, HIGH);
   byteGPS=Serial1.read();         // Read a byte of the serial port
   if (byteGPS == -1) {           // See if the port is empty yet
     delay(100); 
   } else {
     // note: there is a potential buffer overflow here!
     linea[conta]=byteGPS;        // If there is serial port data, it is put in the buffer
     conta++;                      
     //Serial.print(byteGPS, DEC); 
     if (byteGPS==13){            // If the received byte is = to 13, end of transmission
       // note: the actual end of transmission is <CR><LF> (i.e. 0x13 0x10)
       digitalWrite(ledPin, LOW); 
       cont=0;
       bien=0;
       // The following for loop starts at 1, because this code is clowny and the first byte is the <LF> (0x10) from the previous transmission.
       for (int i=1;i<7;i++){     // Verifies if the received command starts with $GPR
         if (linea[i]==comandoGPR[i-1]){
           bien++;
         }
       }
       if(bien==6){               // If yes, continue and process the data
         for (int i=0;i<300;i++){
           if (linea[i]==','){    // check for the position of the  "," separator
             // note: again, there is a potential buffer overflow here!
             indices[cont]=i;
             cont++;
           }
           if (linea[i]=='*'){    // ... and the "*"
             indices[12]=i;
             cont++;
           }
         }
        // Serial.println("");      // ... and write to the serial port
         //Serial.println("");
         //Serial.println("---------------");
         for (int i=0;i<12;i++){
          /* switch(i){
             case 0 :Serial.print("Time in UTC (HhMmSs): ");break;
             case 1 :Serial.print("Status (A=OK,V=KO): ");break;
             case 2 :Serial.print("Latitude: ");break;
             case 3 :Serial.print("Direction (N/S): ");break;
             case 4 :Serial.print("Longitude: ");break;
             case 5 :Serial.print("Direction (E/W): ");break;
             case 6 :Serial.print("Velocity in knots: ");break;
             case 7 :Serial.print("Heading in degrees: ");break;
             case 8 :Serial.print("Date UTC (DdMmAa): ");break;
             case 9 :Serial.print("Magnetic degrees: ");break;
             case 10 :Serial.print("(E/W): ");break;
             case 11 :Serial.print("Mode: ");break;
             case 12 :Serial.print("Checksum: ");break;
           }*/
           
           
           for (int j=indices[i];j<(indices[i+1]-1);j++){
             
           if(j>=21 && j<=29){
                // Serial.print(linea[j]); 
                 lati[l]=linea[j];
                 //Serial.print(lati[l]);
                 l++;
                 
           }
             if(j>=33 && j<=42){
                // Serial.print(linea[j]); 
                 longi[m]=linea[j];
                // Serial.print(longi[m]);
                 m++;
                 
           }
                        if(j>29 && j<=31){
                          latidir=linea[j+1];
                        }

                 if(j>42 && j<=44){
                          longidir=linea[j+1];
                        }

              
           }
          
           Serial.println("");
         }
             

         
        // Serial.println("---------------");
         //Converitng into proper latitude sendable to google
         if(latidir=='N'){
           latisnd[0]='+';}
           if(latidir=='S'){
             latisnd[0]='-';}
         latisnd[1]=lati[0];latisnd[2]=lati[1];latisnd[3]=' ';
        for (int k=2;k<11;k++){
       latisnd[b]=lati[k];b++;
          }latisnd[11]=x[0];
          Serial.print("Latitude : ");
          for(int f=0;f<12;f++){
            Serial.print(latisnd[f]);}
            Serial.println("");
            //Converitng into proper longitude sendable to google
            if(longidir=='E'){
           longisnd[0]='+';}
           if(longidir=='W'){
             longisnd[0]='-';}
         longisnd[1]=longi[1];longisnd[2]=longi[2];longisnd[3]=' ';
        for (int k=3;k<11;k++){
       longisnd[c]=longi[k];c++;
          }longisnd[11]=x[0];
          Serial.print("Longitude : ");
          for(int f=0;f<12;f++){
            Serial.print(longisnd[f]);}/*Serial.print(",");
                 if(longidir=='E'){
           Serial.print("+");}
         Serial.print(longi[1]);Serial.print(longi[2]);Serial.print(" ");
          for(int h=3;h<10;h++){
              Serial.print(longi[h]);
          }*/
          //Serial.print("'");
        }
       conta=0;                    // Reset the buffer
       for (int i=0;i<300;i++){    //  
         linea[i]=' ';  
//delay(2000);         
       }                 
     }
   }
 }

